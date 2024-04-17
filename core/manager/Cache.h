#pragma once

// A simple cache for loading chunks
#include <functional>
#include <glm/glm.hpp>
#include <cstddef>
#include <list>
#include <memory>

struct Vec2Hash {
    std::size_t operator()(const glm::vec<2, float>& v) const {
        std::hash<float> hasher;
        std::size_t h1 = hasher(v.x);
        std::size_t h2 = hasher(v.y);
        return h1 ^ (h2 << 1); // Combine the hashes of x and y
    }
};

// Define a custom comparison function for glm::vec<2, float>
struct Vec2Equal {
    bool operator()(const glm::vec<2, float>& a, const glm::vec<2, float>& b) const {
        return a.x == b.x && a.y == b.y;
    }
};

template <typename Key, typename Chunk> class LRUChunkCache {
private:
  size_t capacity;
  std::list<Key> keys;
  std::unordered_map< Key, std::pair<std::shared_ptr<Chunk>, typename std::list<Key>::iterator>, Vec2Hash, Vec2Equal> cache;

public:
  LRUChunkCache(size_t capacity) : capacity{capacity} {}

  void put(const Key &key, std::shared_ptr<Chunk> chunk) {
    auto it = cache.find(key);
    if (it != cache.end()) {
      keys.erase(it->second.second);
    }

    else if (cache.size() >= capacity) {
      const auto &lruKey = keys.back();
      cache.erase(lruKey);
      keys.pop_back();
    }

    keys.push_front(key);
    cache[key] = {chunk, keys.begin()};
  }

  std::weak_ptr<Chunk> get(const Key &key) {
    auto it = cache.find(key);
    if (it == cache.end()) {
      // Chunk not found
      return std::weak_ptr<Chunk>();
    }

    // Move this chunk to the front of the usage list
    keys.erase(it->second.second);
    keys.push_front(key);
    it->second.second = keys.begin();

    // Return a weak_ptr to the chunk
    return std::weak_ptr<Chunk>(it->second.first);
  }
};
