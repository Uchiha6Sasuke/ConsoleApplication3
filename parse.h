#pragma once
#include "IParser.h"
#include "FileWorker.h"
#include <map>
class parse :
        public IParser, public FileWorker
{
    auto biv(Text &rawInstr, std::vector<wrk *> &blocks);
    std::string source_;
    std::string dest_;
public:
    parse(std::string const& fileName, std::string const& source = "", std::string const& dest = "");
    virtual std::list<wrk*>& Parse();
    ~parse();
};
