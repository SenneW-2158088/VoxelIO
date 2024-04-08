#pragma once

#include "gameplay/Chunk.h"
#include "glm/fwd.hpp"
#include <cstddef>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <unordered_map>

class Test {
private:
  int id;

public:
  Test(int id) : id{id} { std::cout << "Allocated " << id << std::endl; };
  ~Test() { std::cout << "Deallocated " << id << std::endl; };
};

// A simple cache for loading chunks
template <typename Key, typename Chunk> class LRUChunkCache {
private:
  size_t capacity;
  std::list<Key> keys;
  std::unordered_map<
      Key, std::pair<std::shared_ptr<Chunk>, typename std::list<Key>::iterator>>
      cache;

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

class ChunkManager {
private:
  std::map<glm::vec2, unsigned int, std::owner_less<>> chunk_ref;

public:
  Chunk *load(glm::vec2 position);
};
