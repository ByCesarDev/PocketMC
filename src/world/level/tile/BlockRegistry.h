#pragma once

#include "BlockDefinition.h"
#include <unordered_map>
#include <vector>

class BlockRegistry {
public:
    void registerBlock(const BlockDefinition& def);
    
    const BlockDefinition* getBlock(const ResourceLocation& id) const;
    const BlockDefinition* getBlock(int legacyId) const;

    // Converted tiles are registered here for runtime usage
    Tile* getTile(const ResourceLocation& id) const;
    Tile* getTile(int legacyId) const;

    const std::vector<BlockDefinition>& getAllBlocks() const { return blocks; }

private:
    std::vector<BlockDefinition> blocks;
    std::unordered_map<ResourceLocation, size_t> byId;
    std::unordered_map<int, size_t> byLegacyId;
    
    // Cache of instantiated Tiles for the engine
    std::unordered_map<int, Tile*> instantiatedTiles;
};
