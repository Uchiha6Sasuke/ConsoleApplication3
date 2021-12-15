#pragma once
#include <string>
class lval
{
public:
    lval();
    virtual ~lval();
    virtual bool valid(std::string const& str) = 0;
};