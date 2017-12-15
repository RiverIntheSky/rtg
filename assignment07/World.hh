#pragma once

#include <map>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include "Chunk.hh"
#include "Material.hh"
#include "helper/Noise.hh"

struct RayHit
{
    bool hasHit = false;

    glm::vec3 hitPos;
    glm::ivec3 hitNormal;

    Block block;
    glm::ivec3 blockPos;
};

class World
{
public: // public members
    const int chunkSize = 32;

    /// list of active chunks
    std::unordered_map<glm::ivec3, SharedChunk> chunks;

    /// list of opaque materials
    std::vector<Material> materialsOpaque;
    /// list of translucent materials
    std::vector<Material> materialsTranslucent;

    FastNoise noiseGen;

public:
    /// initializes the world (materials, chunks, ...)
    void init();

    /// ensures that a chunk at a given position exists
    void ensureChunkAt(glm::ivec3 p);

    /// deletes all chunks
    void clearChunks();

private: // helper
    /// creates all materials
    void setUpMaterials();

    /// Adds an opaque material, automatically searches textures
    /// CAREFUL: return value only valid until next mat is added
    Material& addOpaqueMat(std::string const& name);
    /// Adds a translucent material, automatically searches textures
    /// CAREFUL: return value only valid until next mat is added
    Material& addTranslucentMat(std::string const& name);
    /// Try to find default textures by name
    void addDefaultTextures(Material& mat);

    /// Performs procedural generation of a chunk
    void generate(Chunk& c);

public: // accessor functions
    /// for a given world space position, returns the starting position of the associated chunk
    glm::ivec3 chunkPos(glm::ivec3 p) const
    {
        p.x -= ((p.x % chunkSize) + chunkSize) % chunkSize;
        p.y -= ((p.y % chunkSize) + chunkSize) % chunkSize;
        p.z -= ((p.z % chunkSize) + chunkSize) % chunkSize;
        return p;
    }

    /// Returns the chunk that contains the given position
    /// Returns nullptr if it doesn't exist
    Chunk* queryChunk(glm::ivec3 p) const;

    /// queries a block at a given position
    /// returns an air block if not found
    /// (does not allocate new chunks dynamically)
    Block const& queryBlock(glm::ivec3 p) const;
    /// queries a block at a given position
    /// returns a MUTABLE reference to the block
    /// allocates chunks dynamically
    Block& queryBlockMutable(glm::ivec3 p);

    /// Marks all blocks in a given radius as dirty
    void markDirty(glm::ivec3 p, int rad);

    /// Returns the material of that idx
    /// nullptr if that material does not exists (or is air)
    Material const* getMaterialFromIndex(int matIdx) const;
    /// Returns the material of that name
    /// It is an error if that material does not exist
    Material const* getMaterialFromName(std::string const& name) const;

    /// Casts a ray into the sceen and returns true if something was hit with max distance maxRange
    /// if getFurthestAirBlock is true, it returns the air block "in front" of that block
    RayHit rayCast(glm::vec3 pos, glm::vec3 dir, float maxRange = 100.0f) const;
};
