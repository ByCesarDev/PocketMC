#include "OreFeature.h"
#include "../Level.h"
#include "../tile/Tile.h"
#include "../../../util/Random.h"
#include <cmath>

bool OreFeature::place(Level* level, Random* random, int x, int y, int z) {
    float angle = random->nextFloat() * 3.1415927f;
    float s = (float)count / 8.0f;
    float x0 = (float)(x + 8) + sinf(angle) * s;
    float x1 = (float)(x + 8) - sinf(angle) * s;
    float z0 = (float)(z + 8) + cosf(angle) * s;
    float z1 = (float)(z + 8) - cosf(angle) * s;
    float y0 = (float)(y + random->nextInt(3) - 2);
    float y1 = (float)(y + random->nextInt(3) - 2);

    for (int i = 0; i <= count; ++i) {
        float f = (float)i / (float)count;
        float cx = x0 + (x1 - x0) * f;
        float cy = y0 + (y1 - y0) * f;
        float cz = z0 + (z1 - z0) * f;
        
        float size = (random->nextFloat() * (float)count / 16.0f);
        float radius = (sinf(f * 3.1415927f) + 1.0f) * size + 1.0f;
        float radiusSq = radius * radius;

        int xMin = (int)floorf(cx - radius);
        int yMin = (int)floorf(cy - radius);
        int zMin = (int)floorf(cz - radius);
        int xMax = (int)floorf(cx + radius);
        int yMax = (int)floorf(cy + radius);
        int zMax = (int)floorf(cz + radius);

        for (int ix = xMin; ix <= xMax; ++ix) {
            float dx = ((float)ix + 0.5f - cx) / radius;
            if (dx * dx < 1.0f) {
                for (int iy = yMin; iy <= yMax; ++iy) {
                    float dy = ((float)iy + 0.5f - cy) / radius;
                    if (dx * dx + dy * dy < 1.0f) {
                        for (int iz = zMin; iz <= zMax; ++iz) {
                            float dz = ((float)iz + 0.5f - cz) / radius;
                            if (dx * dx + dy * dy + dz * dz < 1.0f) {
                                
                                int currentTile = level->getTile(ix, iy, iz);
                                // Verificamos si el bloque es piedra o deepslate
                                if (currentTile == Tile::rock->id || currentTile == Tile::deepslate->id) {
                                    // Obtenemos el ID correcto (Normal o Deepslate)
                                    int finalId = Tile::getOreVariant(oreTileId, currentTile);
                                    level->setTile(ix, iy, iz, finalId);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}