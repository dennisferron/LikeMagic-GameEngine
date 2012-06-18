//#include "stdafx.h"

//! Turns off all screen output.  For experimental testing only.
//#define LOG_NO_PRINT

//! Turns off all file output.  For experimental testing only.
//#define LOG_NO_FILE

#include "Log.hpp"
#include "Thread.hpp"

#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

namespace Iocaste
{
	namespace Debugger
	{

//! A dummy instance must be defined so the write() function has something to return.
DoesNotLog DoesNotLog::dummy;

//! Creates the worker which logs to the screen and the file.
LogDaemon log_daemon;

string Log::trim_to = string(TRIM_TO);
string Log::log_dir = string(LOG_DIR);

map<pthread_map_t, string> Log::thread_names;
int Log::autonumber = 0;

LogDaemon::LogDaemon()
	: log_file(NULL), stop(false)
{
	pthread_mutex_init(&record_mutex, NULL);
	pthread_mutex_init(&file_mutex, NULL);

#ifndef LOG_DISABLE_ALL
	pthread_create(&thread, NULL, LogDaemon::callback, this);
#endif

}

LogDaemon::~LogDaemon()
{
	if (!stop)
		stop_thread();
}

void LogDaemon::stop_thread()
{
	stop = true;

#ifndef LOG_DISABLE_ALL
	pthread_join(thread, NULL);
#endif

	pthread_mutex_destroy(&record_mutex);
	pthread_mutex_destroy(&file_mutex);
}

string LogDaemon::get_cwd()
{
	char buf[300];

#ifdef _WIN32
	::GetCurrentDirectoryA(300, buf);
#else
	getcwd(buf, 300);
#endif

	return string(buf);
}

void LogDaemon::commit(bool do_print, const string& entry)
{
	// Don't log if there are too many in the buffer
	if (entries.size() < MAX_LOG_QUEUE)
	{
		pair<bool, string>* record = new pair<bool, string>(do_print, entry);

		pthread_mutex_lock(&record_mutex);
		entries.push(record);
		pthread_mutex_unlock(&record_mutex);
	}
}

pair<bool, string>* LogDaemon::next_record()
{
	pair<bool, string>* record;

	pthread_mutex_lock(&record_mutex);
	record = entries.front();
	entries.pop();
	pthread_mutex_unlock(&record_mutex);

	return record;
}

void* LogDaemon::callback(void* obj)
{
	static_cast<LogDaemon*>(obj)->run_loop();
	return NULL;
}

void LogDaemon::run_loop()
{
	// This is an or condition:  even if told to stop, don't stop until all entries are written.
	while (!stop || entries.size() > 0)
	{
		Thread::nice(100);

		if (entries.size() != 0)
		{

			pair<bool, string>* record = next_record();

#ifndef LOG_NO_PRINT
			// Do print
			if (record->first)
			{
				string s = record->second;
				// Convert tabs to spaces so log entries fit on the screen
				replace(s.begin(), s.end(), '\t', ' ');
				cout << s << flush;
			}
#endif

#ifndef LOG_NO_FILE
			// Do file
			if (log_file != NULL)
			{
				pthread_mutex_lock(&file_mutex);
				*log_file << record->second << flush;
				pthread_mutex_unlock(&file_mutex);
			}
#endif

			delete record;
		}

	}

        if (log_file)
            log_file->close();
}


void LogDaemon::open_file(string base_name_)
{
	base_name = Log::trim(base_name_, DIR_SEP);
	new_log_file();
}

void LogDaemon::new_log_file()
{
	pthread_mutex_lock(&file_mutex);

	struct stat buf;
	if (stat(Log::log_dir.c_str(), &buf) != 0)
	{
		cerr << "Log directory ``" << LOG_DIR << "'' does not exist; creating it now.\n";
#ifdef _WIN32
		::CreateDirectoryA(Log::log_dir.c_str(), NULL);
#else
		mkdir(Log::log_dir.c_str(), 0777);
#endif
	}

	cout << "Logging to directory: " << Log::log_dir << "\n";
	cout << "Current directory is:\n" << LogDaemon::get_cwd() << "\n";

	if (log_file != NULL)
	{
		*log_file << flush;
		delete log_file;
	}

	string name = Log::get_filename(base_name);

	ofstream* outfile = new ofstream(name.c_str());

	if (outfile->fail())
	{
		cerr << "Failed to open new log file: " << name << "\n";
		delete outfile;
	}
	else
	{
		log_file = outfile;
	}

	pthread_mutex_unlock(&file_mutex);
}



LogStream::LogStream(bool do_print_)
	: do_print(do_print_), needs_sep(false), stream(new stringstream()), is_copy(false)
{
}

LogStream::LogStream(LogStream const& copy_of)
: do_print(copy_of.do_print), needs_sep(copy_of.needs_sep), stream(copy_of.stream), is_copy(true)
{
}

LogStream::~LogStream()
{
	if (is_copy)
	{
		*stream << "\n";
		log_daemon.commit(do_print, stream->str());
	}
}

LogStream Log::write(const char* category, bool do_print, const char* file, int line)
{
	LogStream stream(do_print);

	stream << Log::autonumber++;
	stream << Log::get_logtime();
	stream << Log::get_thread();
	stream << category;
	stream << Log::trim(file, Log::trim_to);
	stream << line;

	return stream;
}

void Log::this_thread_is(string name)
{
	pthread_t id = pthread_self();
	thread_names[*((pthread_map_t *)(&id))] = name;
}

void Log::stop()
{
	log_daemon.stop_thread();
}

void Log::set_trim_to(std::string trim_to_path)
{
	Log::trim_to = trim_to_path;
}


string Log::get_thread()
{
	// Yet another stupid Windows problem:
	// On linux, pthread_t is an integer, pthread_map_t <=> pthread_t,
	// and this code resolves to id = pthread_self.  Unfortunately,
	// on Windows pthread_t is a struct that contains an int, not
	// an int itself, and we aren't allowed to inspect that int!!
	// In order to get something we can use in a map, on
	// Windows we cast the pthread to an integer type (on windows
	// pthread_map_t <=> unsigned int and pthread_map_t <=!=> pthread_t).
	pthread_t temp = pthread_self(); // can't take &func directly.
	pthread_map_t id = *((pthread_map_t*)&temp);

	stringstream name;

	if (Log::thread_names.find(id) == Log::thread_names.end())
		name << id;
	else
		name << Log::thread_names[id];

	return name.str();
}

string Log::get_time(string format)
{
	time_t rawtime;
	tm* timeinfo;
	char buf[40];

	time(&rawtime);

#ifdef _MSC_VER
	tm buffered_timeinfo;
	localtime_s(&buffered_timeinfo, &rawtime);
	timeinfo = &buffered_timeinfo;
#else
	// This might not actually be thread-safe on Linux, must investigate...
	timeinfo = localtime(&rawtime);
#endif

	strftime(buf,40,format.c_str(),timeinfo);

	return string(buf);
}

string Log::get_logtime()
{
	return get_time("%H:%M.%S");
}

string Log::get_filename(string base_name)
{
	return string(Log::log_dir) + string(DIR_SEP) + base_name + get_time(".%Y-%m-%d.%H-%M-%S") + ".log";
}

void Log::open_file(string base_name, string log_dir_path)
{
	Log::log_dir = log_dir_path;
	log_daemon.open_file(base_name);
}

string Log::trim(string original, string match)
{
	size_t start = original.rfind(match);
	size_t rest = start + match.size();

	if (start == string::npos)
	{
		start = 0;
		rest = 0;
	}

	return string(original, rest, original.size() - rest);
}

	} // namespace Debugger
} // namespace Iocaste
