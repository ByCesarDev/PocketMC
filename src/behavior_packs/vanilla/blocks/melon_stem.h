#pragma once
#include "../../../world/level/tile/StemTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_melon_stem(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:melon_stem"))
            .legacyId(105).descriptionId("pumpkinStem")
            .destroyTime(0.0f)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::FoodArmor)
            .factory([](int id) { return (new StemTile(id, Tile::melon))->init(); })
            .build()
    );
}
