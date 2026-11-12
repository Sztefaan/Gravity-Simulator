#include "include/App.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

int main()
{
    try
    {
        App app;
        app.run();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Application error: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
