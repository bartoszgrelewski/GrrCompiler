#include <string>
#include "data.hpp"
#include <iostream>

// virtual register
VaribleStorage::VaribleStorage()
{
    variables["-ACUMULATOR"] = std::make_pair(0, true);
    variables["-TMP"] = std::make_pair(1, true);
    variables["-TMP2"] = std::make_pair(2, true);
    variables["-TMP3"] = std::make_pair(3, true);
    variables["-TMP4"] = std::make_pair(4, true);
    variables["-TMP5"] = std::make_pair(5, true);
    variables["-TMP6"] = std::make_pair(6, true);
    variables["-TMP7"] = std::make_pair(7, true);
    variables["-TMP8"] = std::make_pair(8, true);
    variables["-TMP9"] = std::make_pair(9, true);
}

bool VaribleStorage::exists(std::string id) { return variables.find(id) != variables.end(); }

long long VaribleStorage::getAddress(std::string id) { return variables.find(id)->second.first; }

bool VaribleStorage::isInitialized(std::string id) { return variables.find(id)->second.second; }

bool VaribleStorage::createVariable(std::string id)
{
    if (variables.find(id) != variables.end())
        return false;
    variables[id] = std::make_pair(variables.size(), false);
    return true;
}

void VaribleStorage::initialize(std::string id) { variables[id].second = true; }

#ifdef DEBUG
void VaribleStorage::printVariables()
{
    std::cout << "\nVARIABLES\n";
    for (std::pair<std::string, std::pair<long long, bool>> variable : variables)
    {
        std::cout << "MEM[" << variable.second.first << "] = " << variable.first << "\n";
    }
}
#endif