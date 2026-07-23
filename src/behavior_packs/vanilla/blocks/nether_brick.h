#pragma once
#include "../../../world/level/tile/Tile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/level/material/Material.h"
#include "../../../world/item/ItemCategory.h"

inline void register_nether_brick(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:nether_brick"))
            .legacyId(112).descriptionId("netherBrick")
            .destroyTime(2.0f).explosionResistance(10)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new Tile(id, 0 + 14 * 16, Material::stone))->init(); })
            .build()
    );
}
