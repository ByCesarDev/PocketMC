#pragma once
#include "../../../world/level/tile/FurnaceTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_lit_furnace(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:lit_furnace"))
            .legacyId(62).descriptionId("furnace")
            .destroyTime(3.5f).lightEmission(14)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new FurnaceTile(id, true))->init(); })
            .build()
    );
}
