#pragma once
#include "lval.h"
class val :
        public lval
{
    val(val const& validator);
    val& operator=(val const& validator);
public:
    val();
    ~val();

    virtual bool valis(std::string const& str);
};