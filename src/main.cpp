#include <iostream>
#include <thread>
#include <chrono>

#include <wsServer.hpp>

[[noreturn]] int main()
{
    wsServer::init();
    std::cout << "Hello, World!" << std::endl;

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}
