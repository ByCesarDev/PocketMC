#pragma once
#include "../../../world/level/tile/Mushroom.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_brown_mushroom(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:brown_mushroom"))
            .legacyId(39).descriptionId("mushroom")
            .destroyTime(0.0f).lightEmission(2)
            .soundType(Tile::SOUND_GRASS)
            .creativeCategory(ItemCategory::Decorations)
            .factory([](int id) { return (new Mushroom(id, 13 + 16))->init(); })
            .build()
    );
}
