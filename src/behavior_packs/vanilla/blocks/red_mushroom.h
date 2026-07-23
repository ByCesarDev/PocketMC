#pragma once
#include "../../../world/level/tile/Mushroom.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_red_mushroom(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:red_mushroom"))
            .legacyId(40).descriptionId("mushroom")
            .destroyTime(0.0f)
            .soundType(Tile::SOUND_GRASS)
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new Mushroom(id, 12 + 16))->init(); })
            .build()
    );
}
