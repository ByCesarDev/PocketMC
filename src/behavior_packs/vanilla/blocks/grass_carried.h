#pragma once
#include "../../../world/level/tile/CarriedTile.h"
#include "../../../world/level/tile/BlockDefinition.h"
#include "../../../world/level/tile/BlockRegistry.h"

inline void register_grass_carried(BlockRegistry& blocks) {
    blocks.registerBlock(
        BlockDefinition::builder(ResourceLocation("minecraft:grass_carried"))
            .legacyId(253).descriptionId("grass")
            .creativeCategory(ItemCategory::Structures)
            .factory([](int id) { return (new CarriedTile(id, 3, 12*16 + 12))->init(); })
            .build()
    );
}
