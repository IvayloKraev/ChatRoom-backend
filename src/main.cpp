#include <iostream>
#include <thread>
#include <chrono>

//#include <wsServer.hpp>
#include "dataWraper.hpp"

int main()
{
//    wsServer::init();
    std::cout << "Hello, World!" << std::endl;

    DataWraper<int> q;

    std::thread first = std::thread([&q](){
        while (true){
            q.push(7);
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
        }
    });

    std::thread second = std::thread([&q](){
        while (true){
            q.push(19);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    });

    std::thread third = std::thread([&q](){
        while (true){
            auto temp = q.pop();
            std::cout << temp << std::endl;
        }
    });

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}
