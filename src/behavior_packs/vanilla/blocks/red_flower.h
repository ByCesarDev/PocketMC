#pragma once
#include "../../../world/level/tile/FlowerTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_red_flower(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:red_flower"))
            .legacyId(180).descriptionId("rose")
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new FlowerTile(id, 12 & ~Tile::TEXTURE_ALT_FLAG))->init(); })
            .build()
    );
}
