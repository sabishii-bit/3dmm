#pragma once

#include <string>
#include <unordered_set>
#include <random>
#include <sstream>
#include <iomanip>

class IDGenerator
{
public:
    static std::string generateRandomID();

private:
    static std::unordered_set<std::string> IDSet;
};
