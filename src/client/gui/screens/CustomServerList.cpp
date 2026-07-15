#include "CustomServerList.h"
#include "../../Minecraft.h"
#include "../../../util/StringUtils.h"
#include <fstream>
#include <iostream>

std::vector<PingedCompatibleServer> CustomServerList::servers;

void CustomServerList::load(Minecraft* mc) {
    servers.clear();
    std::string path = "servers.txt";
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        size_t sep = line.find('|');
        if (sep != std::string::npos) {
            std::string name = line.substr(0, sep);
            std::string ip = line.substr(sep + 1);
            PingedCompatibleServer server;
            server.name = name.c_str();
            server.address.FromString(ip.c_str(), ':', 0); // SystemAddress defaults to | but we might want : or |
            // Let's use | as portDelineator as default
            if (!server.address.FromString(ip.c_str(), '|', 0)) {
                 server.address.FromString(ip.c_str(), ':', 0);
            }
            server.isSpecial = false; // it's a custom server
            servers.push_back(server);
        }
    }
}

void CustomServerList::save(Minecraft* mc) {
    std::string path = "servers.txt";
    std::ofstream file(path);
    for (size_t i = 0; i < servers.size(); ++i) {
        file << servers[i].name.C_String() << "|" << servers[i].address.ToString(true, ':') << "\n";
    }
}
