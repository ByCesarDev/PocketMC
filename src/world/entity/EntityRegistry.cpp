#include "EntityRegistry.h"
#include "Entity.h"

void EntityTypeRegistry::registerEntity(const EntityDefinition& def) {
    entities.push_back(def);
    size_t index = entities.size() - 1;
    byId[def.id] = index;
    if (def.legacyId != -1) {
        byLegacyId[def.legacyId] = index;
    }
}

const EntityDefinition* EntityTypeRegistry::getEntity(const ResourceLocation& id) const {
    auto it = byId.find(id);
    if (it != byId.end()) {
        return &entities[it->second];
    }
    return nullptr;
}

const EntityDefinition* EntityTypeRegistry::getEntity(int legacyId) const {
    auto it = byLegacyId.find(legacyId);
    if (it != byLegacyId.end()) {
        return &entities[it->second];
    }
    return nullptr;
}
