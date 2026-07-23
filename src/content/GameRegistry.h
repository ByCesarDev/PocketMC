#pragma once

#include "../world/level/tile/BlockRegistry.h"
#include "../world/item/ItemRegistry.h"
#include "../world/entity/EntityRegistry.h"

class GameRegistry {
public:
    static GameRegistry& getInstance() {
        static GameRegistry instance;
        return instance;
    }

    BlockRegistry& getBlocks() { return blocks; }
    ItemRegistry& getItems() { return items; }
    EntityTypeRegistry& getEntities() { return entities; }

private:
    GameRegistry() = default;

    BlockRegistry blocks;
    ItemRegistry items;
    EntityTypeRegistry entities;
};
