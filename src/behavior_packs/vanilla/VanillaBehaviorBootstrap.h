#pragma once

#include "../../content/GameRegistry.h"

class VanillaBehaviorBootstrap {
public:
    static void registerContent(GameRegistry& registry);
private:
    static void registerBlocks(BlockRegistry& blocks);
    static void registerItems(ItemRegistry& items);
    static void registerEntities(EntityTypeRegistry& entities);
};
