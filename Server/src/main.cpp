/*
** EPITECH PROJECT, 2023
** R-TYPE
** File description:
** main
*/

#include "../../GameEngine/include/entities.hpp"
#include "server.hpp"

#include <dlfcn.h>
#include <thread>


int main()
{
    void* libraryHandle = dlopen("GameEngine/libsamurai_ecs.so", RTLD_LAZY);

    if (!libraryHandle) {
        std::cerr << "Failed to load the shared library: " << dlerror() << std::endl;
        return 84;
    }
    try {
        Server server;

        typedef Registry* (*MyFunctionType)();
        auto factory = (MyFunctionType)dlsym(libraryHandle, "factory");
        if (!factory) {
            std::cerr << "Failed to find the symbol factory: " << dlerror() << std::endl;
        }

        Registry* registry;
        Entity entity;
        registry = factory();
        entity = registry->createEntity();
        registry->addComponent(entity, Position(std::make_pair(0, 0)));
        // registry->addComponent(entity, HealthPoint(100));
        // registry->addComponent(entity, Velocity());
        // registry->addComponent(entity, ID(0));
        //

        std::thread serverThread(&Server::startListening, &server);
        // std::thread serverThread2(&Server::startSending, &server);
        serverThread.join();
        // serverThread2.join();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    dlclose(libraryHandle);
    return 0;
}
