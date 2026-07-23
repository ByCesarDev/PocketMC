#pragma once
#include "../../../world/level/tile/Sapling.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_sapling(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:sapling"))
            .legacyId(6).descriptionId("sapling")
            .destroyTime(0.0f)
            .soundType(Tile::SOUND_GRASS)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new Sapling(id, 15))->init(); })
            .build()
    );
}
