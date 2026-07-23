#pragma once
#include "../../../world/level/tile/MelonTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_melon_block(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:melon_block"))
            .legacyId(103).descriptionId("melon")
            .destroyTime(1.0f)
            .soundType(Tile::SOUND_WOOD)
            .creativeCategory(ItemCategory::FoodArmor)
            .factory([](int id) { return (new MelonTile(id))->init(); })
            .build()
    );
}
