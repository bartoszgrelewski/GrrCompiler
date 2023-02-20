#include "code.hpp"
#include <sstream>
#include <string>

std::string Code::getCode()
{
#ifdef DEBUG
    variables.printVariables();
    long long i = 0, j = 0;
#endif

    std::stringstream ss;
    for (auto instruction : assemblyCode)
    {
#ifdef DEBUG
        while (i == asmComments[j].first)
        {
            if (asmComments[j].second[0] == '\n')
            {
                ss << "\n[" << asmComments[j].second.substr(1) << "]\n";
            }
            else
            {
                ss << "[" << asmComments[j].second << "]\n";
            }
            j++;
        }
        ss << "[" << i << "]\t";
        ss << instruction;
        while (i == -asmComments[j].first)
        {
            ss << "\t[" << asmComments[j].second << "]";
            j++;
        }
        ss << '\n';
        i++;
#else
        ss << instruction + "\n";
#endif
    }

    return ss.str();
}

void Code::atomic(std::string s)
{
    assemblyCode.push_back(s);
}

void Code::atomic(std::string s, long long n)
{
    assemblyCode.push_back(s + " " + std::to_string(n));
}

void Code::get(long long n) { atomic("GET", n); }

void Code::put(long long n) { atomic("PUT", n); }

void Code::load(long long n) { atomic("LOAD", n); }

void Code::store(long long n) { atomic("STORE", n); }

void Code::loadi(long long n) { atomic("LOADI", n); }

void Code::storei(long long n) { atomic("STOREI", n); }

void Code::add(long long n) { atomic("ADD", n); }

void Code::addi(long long n) { atomic("ADDI", n); }

void Code::sub(long long n) { atomic("SUB", n); }

void Code::subi(long long n) { atomic("SUBI", n); }

void Code::set(long long n) { atomic("SET", n); }

void Code::half() { atomic("HALF"); }

void Code::jump(long long n) { atomic("JUMP", n); }

void Code::jpos(long long n) { atomic("JPOS", n); }

void Code::jzero(long long n) { atomic("JZERO", n); }

void Code::jumpi(long long n) { atomic("JUMPI", n); }

void Code::jump() { atomic("JUMP"); }

void Code::jpos() { atomic("JPOS"); }

void Code::jzero() { atomic("JZERO"); }

void Code::jumpi() { atomic("JUMPI"); }

void Code::halt() { atomic("HALT"); }