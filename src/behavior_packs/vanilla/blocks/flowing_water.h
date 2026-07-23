#pragma once
#include "../../../world/level/tile/LiquidTileDynamic.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_flowing_water(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:flowing_water"))
            .legacyId(8).descriptionId("water")
            .destroyTime(100.0f).lightBlock(3)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new LiquidTileDynamic(id, Material::water))->init(); })
            .build()
    );
}
