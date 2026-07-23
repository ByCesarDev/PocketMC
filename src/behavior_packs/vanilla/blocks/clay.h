#pragma once
#include "../../../world/level/tile/ClayTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_clay(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:clay"))
            .legacyId(82).descriptionId("clay")
            .destroyTime(0.6f)
            .soundType(Tile::SOUND_GRAVEL)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new ClayTile(id, 16 * 4 + 8))->init(); })
            .build()
    );
}
