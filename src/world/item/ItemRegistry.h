#pragma once

#include "ItemDefinition.h"
#include <unordered_map>
#include <vector>

class ItemRegistry {
public:
    void registerItem(const ItemDefinition& def);
    
    const ItemDefinition* getItem(const ResourceLocation& id) const;
    const ItemDefinition* getItem(int legacyId) const;

    // Converted items are registered here for runtime usage
    Item* getItemInstance(const ResourceLocation& id) const;
    Item* getItemInstance(int legacyId) const;

    const std::vector<ItemDefinition>& getAllItems() const { return items; }

private:
    std::vector<ItemDefinition> items;
    std::unordered_map<ResourceLocation, size_t> byId;
    std::unordered_map<int, size_t> byLegacyId;
    
    // Cache of instantiated Items for the engine
    std::unordered_map<int, Item*> instantiatedItems;
};
