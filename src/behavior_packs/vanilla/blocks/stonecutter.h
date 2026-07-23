#pragma once
#include "../../../world/level/tile/StonecutterTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_stonecutter(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:stonecutter"))
            .legacyId(245).descriptionId("stonecutter")
            .destroyTime(2.5f)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new StonecutterTile(id))->init(); })
            .build()
    );
}
