#ifndef DEEPSLATE_TILE_H
#define DEEPSLATE_TILE_H

#include "Tile.h"
#include "../../../util/Random.h"
#include "../material/Material.h"

class DeepslateTile : public Tile {
public:
    int resourceId;
    int resCountMin;
    int resCountMax;
    int resAux;

    // Implementación inline para evitar errores de enlace (undefined reference)
    DeepslateTile(int id, int textureIndex) 
        : Tile(id, textureIndex, Material::stone) 
    {
        this->resourceId = id; // Por defecto se suelta a sí mismo
        this->resCountMin = 1;
        this->resCountMax = 1;
        this->resAux = 0;

        // El tiempo de destrucción es ligeramente mayor que el de la piedra normal (1.5f)
        this->setDestroyTime(2.0f);
        this->setExplodeable(6.0f);
        this->setSoundType(SOUND_STONE);
    }

    // Método para configurar el drop como un ore
    DeepslateTile* setResource(int id, int min = 1, int max = 1, int aux = 0) {
        this->resourceId = id;
        this->resCountMin = min;
        this->resCountMax = max;
        this->resAux = aux;
        return this;
    }

    virtual int getResource(int data, Random* random) override { return resourceId; }
    virtual int getResourceCount(Random* random) override { 
        if (resCountMin == resCountMax) return resCountMin;
        return resCountMin + random->nextInt(resCountMax - resCountMin + 1);
    }
    virtual int getSpawnResourcesAuxValue(int data) override { return resAux; }
};

#endif // DEEPSLATE_TILE_H