// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/ScriptUtil.hpp"

#include "boost/random/linear_congruential.hpp"
#include "boost/random/uniform_int.hpp"
#include "boost/random/uniform_real.hpp"
#include "boost/random/variate_generator.hpp"
#include "boost/math/special_functions/fpclassify.hpp"

#include <sstream>

using namespace std;
using namespace LM;

// Use to communicate with running scripts what path they are running under
// in order to properly load assets.  TODO:  Move all this to Iocaste (maybe).
string scriptPath = "";

string ScriptUtil::get_script_path()
{
    return scriptPath;
}

void ScriptUtil::set_script_path(string value)
{
    scriptPath = value;
}

bool ScriptUtil::is_nan(float f)
{
    return (boost::math::isnan)(f);
}

void ScriptUtil::print_float_array(float const* array, int width, int height)
{
    for (int w=0; w<width; ++w)
    {
        cout << "\t" << w;
    }

    for (int h=0; h<height; ++h)
    {
        cout << endl << h;
        for (int w=0; w<width; ++w)
        {
            cout << "\t" << array[h*width+w];
        }
    }
    cout << endl;
}

float ScriptUtil::get_float(float value)
{
    //cout << "get_float value = " << value << endl;
    return value;
}

void* ScriptUtil::get_void_ptr(void* value)
{
    return value;
}

float ScriptUtil::get_random_float(float min, float max)
{
    static boost::minstd_rand algorithm;
    static boost::uniform_real<float> range(0.0f, 1.0f);
    static boost::variate_generator<boost::minstd_rand&, boost::uniform_real<float> > generator(algorithm, range);
    float result = (max-min)*generator()+min;
    return result;
}

float* ScriptUtil::get_random_float_array(int width, int height, float min, float max)
{
    float* array = new float[width*height];

    for (int w=0; w < width; w++)
    {
        for (int h=0; h < height; h++)
        {
            array[h*width+w] = 0.1 * (float)h*w; //get_random_float(min, max);
        }
    }

    return array;
}

string ScriptUtil::ptr_addr_to_str(void const* p)
{
    stringstream ss;
    ss << p;
    return ss.str();
}

void* ScriptUtil::get_null_ptr()
{
    return NULL;
}

void* ScriptUtil::get_test_ptr(string hex_str)
{
    void* result = 0;
    std::stringstream ss;
    ss << std::hex << hex_str;
    ss >> result;
    return result;
}

bool ScriptUtil::get_true()
{
    return true;
}

bool ScriptUtil::get_false()
{
    return false;
}

double ScriptUtil::get_double(double value)
{
    return value;
}

int ScriptUtil::get_int(int value)
{
    return value;
}

string ScriptUtil::get_string(string const& value)
{
    return value;
}
