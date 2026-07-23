#pragma once
#include "../../../world/level/tile/LiquidTileStatic.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_water(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:water"))
            .legacyId(9).descriptionId("water")
            .destroyTime(100.0f).lightBlock(3)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new LiquidTileStatic(id, Material::water))->init(); })
            .build()
    );
}
