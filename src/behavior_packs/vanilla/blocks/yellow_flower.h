#pragma once
#include "../../../world/level/tile/FlowerTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_yellow_flower(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:yellow_flower"))
            .legacyId(179).descriptionId("flower")
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new FlowerTile(id, 13 & ~Tile::TEXTURE_ALT_FLAG))->init(); })
            .build()
    );
}
