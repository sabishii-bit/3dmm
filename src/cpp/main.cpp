#include <iostream>
#include "WindowManager.h"

int main()
{
    try 
    {
        std::cout << "Starting up..." << std::endl;
        WindowManager& wm = WindowManager::getInstance();
    }
    catch (const std::system_error& e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }
    

    return 0;
}