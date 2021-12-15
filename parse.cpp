#include "wrkfl.h"
#include "parse.h"
#include "bd.h"
#include "bg.h"
#include "br.h"
#include "brep.h"
#include "bs.h"
#include "bw.h"
#include <map>


parse::parse(std::string const& fileName, std::string const& source, std::string const& dest)
        :FileWorker(fileName, std::ios_base::in)
{
}

auto parse::biv(Text &rawInstr, std::vector<wrk *> &blocks)
{
    auto t = rawInstr.begin();
    ++t;
    for (; t->find("csed") == std::string::npos; ++t) {
        size_t posEq = t->find("=");
        if (posEq == std::string::npos) {
            throw std::logic_error("Bad block description");
        }
        size_t bnum = std::stoi(it->substr(0, t->find(' ')));
        t->erase(0, t->find(' ') + 3);

        std::string bname = t->substr(0, t->find(' '));
        std::string param = t->substr(t->find(' ') + 1, t->length());;

        wrk* nw = nullptr;
        if (bname == "readfile") {
            nw = new BlockRead(param);
        }
        else if (bname == "writefile") {
            nw = new BlockWrite(param);
        }
        else if (bname == "grep") {
            nw = new BlockGrep(param);
        }
        else if (bname == "sort") {
            nw = new BlockSort();
        }
        else if (bname == "replace") {
            std::string param2 = param.substr(param.find(' ') + 1, param.length());
            param = param.substr(0, param.find(' '));
            nw = new BlockReplace(param, param2);
        }
        else if (bname == "dump") {
            nw = new BlockDump(param);
        }
        else {
            throw std::logic_error("Bad block name");
        }
        if (blocks.capacity() < bnum + 1) {
            blocks.resize(bnum + 2);
        }
        blocks[bnum] = nw;
    }
    return t;
}

std::list<IWorker*>& parse::Parse()
{
    Text rawInstr;
    Read(rawInstr);
    if (rawInstr[0].find("desc") == std::string::npos) {
        throw std::logic_error("Is no 'desc' there!");
    }

    std::list<wrk*>* instructions = new std::list<wrk*>;
    if (source_ != "") {
        instructions->push_back(new BlockRead(source_));
    }
    std::vector<wrk*> blocks;
    auto ssd = biv(rawInstr, blocks) + 1;
    for (auto t = ssd; t != rawInstr.end(); ++t) {
        while (t->find(' ') != std::string::npos) t->erase(t->find(' '), 1);
        while (t->find("->") != std::string::npos) {
            size_t n = stoi(t->substr(0, t->find("->")));
            t->erase(0, t->find("->") + 2);
            if (n > blocks.capacity()-1) {
                throw std::logic_error("This block does'n exist!");
            }
            instructions->push_back(blocks[n]);
        }
        size_t n = 0;
        try {
            n = stoi(t->substr(0, t->length()));
        }
        catch (const std::exception&) {
            std::cerr << "Wrong shame structure!" << std::endl;
        }
        instructions->push_back(blocks[n]);
    }
    if (dest_ != "") {
        instructions->push_back(new BlockWrite(dest_));
    }
    return *instructions;
}


Parser::~Parser()
{
}
parse::~parse()
{
}