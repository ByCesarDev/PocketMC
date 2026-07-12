#ifndef POCKETMC_MODS_MODREGISTRY_H__
#define POCKETMC_MODS_MODREGISTRY_H__

#include <string>
#include <vector>

class Tile;
class Item;

struct ModInfo {
    std::string id;
    std::string name;
    std::string version;
    std::string author;
    std::string description;
    std::string path;
    bool hasResourcePack;
    bool hasBeheviorPack;
    bool builtIn;

    ModInfo()
        : hasResourcePack(false),
          hasBeheviorPack(false),
          builtIn(false)
    {}
};

class ModRegistry {
public:
    static const int ExampleBlockId = 201;
    static const int ExampleItemId = 220;

    static void ensureFolders(const std::string& storageRoot);
    static std::vector<ModInfo> scanMods(const std::string& storageRoot);

    static void registerBuiltInTiles();
    static void registerBuiltInItems();

    static Tile* exampleBlock;
    static Item* exampleItem;

private:
    static std::string modsRoot(const std::string& storageRoot);
};

#endif
