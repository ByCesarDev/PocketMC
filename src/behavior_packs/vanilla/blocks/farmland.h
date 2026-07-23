#pragma once
#include "../../../world/level/tile/FarmTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_farmland(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:farmland"))
            .legacyId(60).descriptionId("farmland")
            .destroyTime(0.6f)
            .soundType(Tile::SOUND_GRAVEL)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new FarmTile(id))->init(); })
            .build()
    );
}
