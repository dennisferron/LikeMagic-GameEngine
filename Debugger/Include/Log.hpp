#pragma once

#include "Thread.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <queue>

#include "boost/shared_ptr.hpp"

#ifdef _WIN32

#define TRIM_TO ""
#define LOG_DIR "log"
#define DIR_SEP "\\"

#else

#define TRIM_TO "/"
#define LOG_DIR "./log"
#define DIR_SEP "/"

#endif

/*!

	\def TRIM_TO Used to shorten _FILE_ macro length in output.
	\def LOG_DIR Used to decide where logs go. Affected by current working directory.
	\def DIR_SEP Used to build paths, and to trim path from exe name when making log file name.
*/

//! Switch to new log file when it gets too many lines. Not implemented yet.
#define MAX_LOG_LINES 100

//! Max number of pending log entires before it starts dropping them on the floor.
#define MAX_LOG_QUEUE 30000

//! Define in private: section to prevent accidental copies of your class.
#define NO_COPY(name) \
name& operator =(const name& other); \
name(const name& other);

namespace Iocaste
{
	namespace Debugger
	{

//! Runs a worker thread that writes log messages to a file and the screen.
class LogDaemon
{
private:
	pthread_t thread;
	pthread_mutex_t record_mutex;
	pthread_mutex_t file_mutex;

	std::queue< std::pair<bool, std::string>* > entries;
	std::pair<bool, std::string>* next_record();

	std::ofstream* log_file;

	static void* callback(void* obj);
	void run_loop();
	volatile bool stop;

	std::string base_name;
	void new_log_file();

	static std::string get_cwd();
public:
	LogDaemon();
	~LogDaemon();
	void stop_thread();
	void commit(bool do_print, const std::string& entry);
	void open_file(std::string base_name);
};

//! Dummy class used to make LOG(x) calls disappear when LOG_SILENT(x) is defined.
class DoesNotLog
{
private:
	static DoesNotLog dummy;

public:
	//! Dummy << operator which eats all logging and compiles down to nothing.
	/*!	Appending any number of objects (with <<) to a "DoesNotLog" object reduces down to
		a single inline "*this", which will in turn be optimized out by the compiler.
	*/
	template <typename T>
	inline DoesNotLog& operator <<(const T& any)
		{ return *this; }


	inline static DoesNotLog& write(const char* category, bool do_print, const char* source, int line)
		{ return dummy; }
};

//! Used by log macros to enable a setting.
class LogYes
{
public:
	inline static bool value() { return true; }
};

//! Used by log macros to disable a setting.
class LogNo
{
public:
	inline static bool value() { return false; }
};

//! Sends log messages to log file and cout.
class LogStream
{
private:

	boost::shared_ptr<std::stringstream> stream;

	bool do_print;
	bool needs_sep;
	bool is_copy;  // we actually only want to commit from the copy.

	void commit();

public:
	LogStream(bool do_print_);
	LogStream(LogStream const& copy_of);

	//! Commits a line to the log after the line of code ends.
	/*! 	Each call in a '<<' chain does not know if another '<<' follows it; so how do you know
		when the chain is done and it's time to end the line?  The trick is that we create a
		new temporary LogStream with each line of logging.  That LogStream object goes out
		of scope at the end of a line of code and is (we hope!) destructed before we move
		onto the next line of code, so that's when we commit a line of logging.
	*/
	~LogStream();

	template <typename T> void write(const T& any)
	{
		*stream << any;
	}

	void write_sep()
	{
		*stream << "\t";
	}

	template <typename T> LogStream& operator <<(const T& any)
	{
		if (needs_sep)
			write_sep();
		else
			needs_sep = true;

		write(any);

		return *this;
	}
};

// On Windows, pthread_t is a struct not an int, which means
// operator <() for stl map won't work on it.  This is a fix for that.
#ifdef _WIN32
	typedef unsigned int pthread_map_t;
#else
	typedef pthread_t pthread_map_t;
#endif


//! Static methods provides public interface to the log
class Log
{
private:
	NO_COPY(Log);

	static std::map<pthread_map_t, std::string> thread_names;

	static std::string trim_to;
	static std::string log_dir;

	static std::string trim(std::string original, std::string match);
	static std::string get_time(std::string format);

	static std::string get_filename(std::string base_name);
	static std::string get_logtime();
	static std::string get_thread();

	static int autonumber;

	friend class LogDaemon;
	friend class LogStream;

public:
	static LogStream write(const char* category, bool do_print, const char* source, int line);
	static void open_file(std::string base_name, std::string log_dir_path);
	static void set_trim_to(std::string trim_to_path);
	static void this_thread_is(std::string name);
	static void stop();
};

	} // namespace Debugger
} // namespace Iocaste

//! Write to log.
/*!	Creates a temporary LogStream object, logs the category, file, and line.
	Append messages to it using the << operator (works just like cout).
	The log entry will be commited when the temporary object goes out of
	scope (i.e., after the ; on the end of the line).
	\param A logging category previously defined.
*/
#define LOG(category) \
	LOG__##category::write(#category, PRINT__##category::value(),  __FILE__, __LINE__)

//! Turns logging on for a particular category.
#define LOG_ON(category) \
	typedef Iocaste::Debugger::Log LOG__##category;

//! Turns logging off for a particular category.
#define LOG_OFF(category) \
	typedef Iocaste::Debugger::DoesNotLog LOG__##category;

//! Turns printing on for a logging category.
#define PRINT_ON(category) \
	typedef Iocaste::Debugger::LogYes PRINT__##category;

//! Turns printing off for a logging category.
#define PRINT_OFF(category) \
	typedef Iocaste::Debugger::LogNo PRINT__##category;

// These define both at once.

//! Turn logging completely off for a category.
/*!
	Creates	a category if it doesn't exist,	or redefines
	its behavior in the local scope if it existed already.

	Uses typedefs to make a macro behave as if it has typedef scoping.

	Categories can be defined for entire files, namespaces,
	entire classes, or just within functions.  In a nested
	scope, you can redefine & change the logging behavior
	of a category created at a higher scope.  The only thing
	you cannot do is have two definitions in the same scope.

	The name of the category is automatically mangled, so you can use any
	word for a category; it need not be unique.  It will not clash with the names
	of your classes, methods, or variables.

	\param category The name of a logging category.  Not a string: no quote marks.
*/
#define LOG_NOTHING(category) \
	LOG_OFF(category); PRINT_OFF(category);


//! Turn logging to file on for a category, but do not print messages on the screen.
/*!
	Creates	a category if it doesn't exist,	or redefines
	its behavior in the local scope if it existed already.

	Uses typedefs to make a macro behave as if it has typedef scoping.

	Categories can be defined for entire files, namespaces,
	entire classes, or just within functions.  In a nested
	scope, you can redefine & change the logging behavior
	of a category created at a higher scope.  The only thing
	you cannot do is have two definitions in the same scope.

	The name of the category is automatically mangled, so you can use any
	word for a category; it need not be unique.  It will not clash with the names
	of your classes, methods, or variables.

	\param category The name of a logging category.  Not a string: no quote marks.
*/
#define LOG_QUIETLY(category) \
	LOG_ON(category); PRINT_OFF(category);

//! Turn logging to file on for a category, and simultaneously print messages to screen.
/*!
	Creates	a category if it doesn't exist,	or redefines
	its behavior in the local scope if it existed already.

	Uses typedefs to make a macro behave as if it has typedef scoping.

	Categories can be defined for entire files, namespaces,
	entire classes, or just within functions.  In a nested
	scope, you can redefine & change the logging behavior
	of a category created at a higher scope.  The only thing
	you cannot do is have two definitions in the same scope.

	The name of the category is automatically mangled, so you can use any
	word for a category; it need not be unique.  It will not clash with the names
	of your classes, methods, or variables.

	\param category The name of a logging category.  Not a string: no quote marks.
*/
#define LOG_VERBOSE(category) \
	LOG_ON(category); PRINT_ON(category);


// The default settings

// Define VERBOSE_DEBUG or QUIETLY_DEBUG *before*
// including Log.hpp if you want to change the default behavior.
#ifdef VERBOSE_DEBUG
LOG_VERBOSE(debug);
#elif defined(QUIETLY_DEBUG)
LOG_QUIETLY(debug);
#else
LOG_NOTHING(debug);
#endif

#ifdef VERBOSE_INFO
LOG_VERBOSE(info);
#else
LOG_QUIETLY(info);
#endif

LOG_VERBOSE(notify);
LOG_VERBOSE(warn);
LOG_VERBOSE(error);

#define VAR(x) #x << (x)
