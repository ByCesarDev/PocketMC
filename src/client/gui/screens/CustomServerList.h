#ifndef POCKETMC_CUSTOMSERVERLIST_H
#define POCKETMC_CUSTOMSERVERLIST_H

#include <vector>
#include <string>
#include "../../../network/RakNetInstance.h"

class Minecraft;

class CustomServerList {
public:
    static std::vector<PingedCompatibleServer> servers;
    static void load(Minecraft* mc);
    static void save(Minecraft* mc);
};

#endif
