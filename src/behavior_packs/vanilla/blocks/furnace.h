#pragma once
#include "../../../world/level/tile/FurnaceTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_furnace(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:furnace"))
            .legacyId(61).descriptionId("furnace")
            .destroyTime(3.5f)
            .soundType(Tile::SOUND_STONE)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new FurnaceTile(id, false))->init(); })
            .build()
    );
}
