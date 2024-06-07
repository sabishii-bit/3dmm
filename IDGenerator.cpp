#include "IDGenerator.h"

std::unordered_set<std::string> IDGenerator::IDSet;

std::string IDGenerator::generateRandomID()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;

    while (true) 
    {
        uint64_t random_value = dis(gen);

        std::stringstream ss;
        ss << std::hex << std::setw(16) << std::setfill('0') << random_value;
        std::string id = ss.str();

        // Check if the ID is unique
        if (IDSet.find(id) == IDSet.end()) 
        {
            // ID is unique, add it to the set and return it
            IDSet.insert(id);
            return id;
        }
        // If the ID is not unique, loop again to generate a new one
    }
}
