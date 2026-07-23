#pragma once
#include "../../../world/level/tile/TopSnowTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_snow_layer(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:snow_layer"))
            .legacyId(78).descriptionId("snow")
            .destroyTime(0.1f)
            .soundType(Tile::SOUND_CLOTH)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new TopSnowTile(id, 16 * 4 + 2))->init(); })
            .build()
    );
}
