#if !defined(DEMO_MODE) && !defined(APPLE_DEMO_PROMOTION)

#ifndef NET_MINECRAFT_WORLD_LEVEL_STORAGE__ExternalFileLevelStorage_H__
#define NET_MINECRAFT_WORLD_LEVEL_STORAGE__ExternalFileLevelStorage_H__

//package net.minecraft.world.level.storage;

#include <vector>
#include <list>
#include <unordered_map>
#include <string>

//#include "com/mojang/nbt/CompoundTag.h"
#include "LevelStorage.h"
#include "../chunk/storage/ChunkStorage.h"

class Player;
class Dimension;
class RegionFile;

// Region key for hash map
struct RegionKey {
    int x;
    int z;
    
    bool operator==(const RegionKey& other) const {
        return x == other.x && z == other.z;
    }
};

// Hash function for RegionKey
namespace std {
    template<>
    struct hash<RegionKey> {
        size_t operator()(const RegionKey& k) const {
            return ((size_t)(uint32_t)k.x << 32) | (uint32_t)k.z;
        }
    };
}

typedef struct UnsavedLevelChunk
{
	int				pos;
	RakNet::TimeMS	addedToList;
	LevelChunk*		chunk;
} UnsavedLevelChunk;

typedef std::list<UnsavedLevelChunk> UnsavedChunkList;

/*public*/
class ExternalFileLevelStorage:
		public LevelStorage,
		public ChunkStorage
		//public PlayerIO
{
public:
    ExternalFileLevelStorage(const std::string& levelId, const std::string& fullPath);
	virtual ~ExternalFileLevelStorage();

    LevelData* prepareLevel(Level* level);

	//throws LevelConflictException
    void checkSession() {}

    ChunkStorage* createChunkStorage(Dimension* dimension);

    void saveLevelData(LevelData& levelData, std::vector<Player*>* players);
    // PlayerIO getPlayerIO() { return this; }
	// CompoundTag loadPlayerDataTag(std::string playerName) { return NULL; }

    void closeAll() {}

	static bool readLevelData(const std::string& directory, LevelData& dest);
	static bool readPlayerData(const std::string& filename, LevelData& dest);
	static bool writeLevelData(const std::string& datFileName, LevelData& dest, const std::vector<Player*>* players);
	static void saveLevelData(const std::string& directory, LevelData& levelData, std::vector<Player*>* players);

    int savePendingUnsavedChunks(int maxCount);

	//
	// ChunkStorage methods
	//
	virtual LevelChunk* load(Level* level, int x, int z);
	void save(Level* level, LevelChunk* levelChunk);
	// @note, loadEntities and saveEntities dont use second parameter
	void loadEntities(Level* level, LevelChunk* levelChunk);
	void saveEntities(Level* level, LevelChunk* levelChunk);
	void saveGame(Level* level);
    void saveAll(Level* level, std::vector<LevelChunk*>& levelChunks);

	virtual void tick();
	virtual void flush() {}
private:
	void clearRegionCache();
	RegionFile* getRegionFile(int chunkX, int chunkZ);
	
	std::string levelId;
	std::string levelPath;
	LevelData* loadedLevelData;
	std::unordered_map<RegionKey, RegionFile*> regionFiles;
	RegionFile* netherRegionFile;
	int currentDimensionId;
	RegionFile* entitiesFile;

	Level* level;
	int tickCount;
	int loadedStorageVersion;
	UnsavedChunkList unsavedChunkList;
	int lastSavedEntitiesTick;
};

#endif /*NET_MINECRAFT_WORLD_LEVEL_STORAGE__ExternalFileLevelStorage_H__*/

#endif /*DEMO_MODE*/
