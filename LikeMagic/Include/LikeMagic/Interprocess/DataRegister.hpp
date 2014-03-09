#pragma once

#include "boost/interprocess/sync/interprocess_semaphore.hpp"

namespace LM {

template <typename T>
struct DataRegister
{
    boost::interprocess::interprocess_semaphore available_for_write;
    boost::interprocess::interprocess_semaphore writing_in_progress;
    bool has_data;
    T data;
    DataRegister() :
        available_for_write(1),
        writing_in_progress(1),
        has_data(false) {}
};

}
