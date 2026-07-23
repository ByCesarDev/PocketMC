#pragma once
#include "../../../world/level/tile/TallGrass.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_tallgrass(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:tallgrass"))
            .legacyId(31).descriptionId("tallgrass")
            .destroyTime(0.0f)
            .soundType(Tile::SOUND_GRASS)
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new TallGrass(id, 2 * 16 + 7))->init(); })
            .build()
    );
}
