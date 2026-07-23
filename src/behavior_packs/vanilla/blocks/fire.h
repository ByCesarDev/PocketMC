#pragma once
#include "../../../world/level/tile/FireTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_fire(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:fire"))
            .legacyId(51).descriptionId("fire")
            .destroyTime(0.0f).lightEmission(16)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new FireTile(id, 1 * 16 + 15))->init(); })
            .build()
    );
}
