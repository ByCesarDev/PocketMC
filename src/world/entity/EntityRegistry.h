#pragma once

#include "EntityDefinition.h"
#include <unordered_map>
#include <vector>

class EntityTypeRegistry {
public:
    void registerEntity(const EntityDefinition& def);
    
    const EntityDefinition* getEntity(const ResourceLocation& id) const;
    const EntityDefinition* getEntity(int legacyId) const;

    const std::vector<EntityDefinition>& getAllEntities() const { return entities; }

private:
    std::vector<EntityDefinition> entities;
    std::unordered_map<ResourceLocation, size_t> byId;
    std::unordered_map<int, size_t> byLegacyId;
};
