#include "Tile.h"
#include "../material/Material.h"

// Stub para AncientDebrisTile solo para satisfacer el linker
class AncientDebrisTile : public Tile {
public:
    AncientDebrisTile(int id) : Tile(id, 0, Material::stone) {
        // Constructor vacío - nunca se usa
    }
};

// Variable global para que el código compile
static AncientDebrisTile* _dummy_ancient_debris = nullptr;
