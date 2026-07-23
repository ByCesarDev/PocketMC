#pragma once
#include "../../../world/level/tile/BedTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"
#include "../../../world/item/ItemCategory.h"

inline void register_bed(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:bed"))
            .legacyId(26).descriptionId("bed")
            .destroyTime(0.2f)
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new BedTile(id))->init(); })
            .build()
    );
}
