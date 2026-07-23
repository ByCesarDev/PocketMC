#pragma once
#include "../../../world/level/tile/SnowTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_snow_block(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:snow"))
            .legacyId(80).descriptionId("snow")
            .destroyTime(0.2f)
            .soundType(Tile::SOUND_CLOTH)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new SnowTile(id, 16 * 4 + 2))->init(); })
            .build()
    );
}
