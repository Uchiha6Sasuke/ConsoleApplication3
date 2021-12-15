#pragma once
#include "defs.h"
struct wrk
{
    wrk();
    virtual Text& Process(std::vector<std::string>& text) = 0;
    virtual ~wrk();
};