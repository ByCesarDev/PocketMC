#pragma once
#include "EntityTile.h"
#include "../material/Material.h"

class Level;
class Player;
class TileEntity;

class ChestTile : public EntityTile {
public:
    static const int EVENT_SET_OPEN_COUNT = 1;

    ChestTile(int id) : EntityTile(id, 26, Material::wood) {
        // Configuramos propiedades fundamentales para bloques con TileEntity
        Tile::isEntityTile[id] = true;
        Tile::solid[id] = true;
        Tile::shouldTick[id] = true;
        Tile::sendTileData[id] = true;
        
        this->category = 2; // Estructuras/Madera
    }

    virtual bool isCubeShaped() override { return true; }
    virtual bool isSolidRender() override { return true; }
    virtual int getRenderShape() override { return 0; } // Renderizador de cubo estándar
    virtual int getTexture(int face, int data) override;

    virtual void onPlace(Level* level, int x, int y, int z) override;
    virtual void neighborChanged(Level* level, int x, int y, int z, int neighborTileId) override;
    virtual bool use(Level* level, int x, int y, int z, Player* player) override;
    virtual TileEntity* newTileEntity() override;

    void recalcLockDir(Level* level, int x, int y, int z);
};