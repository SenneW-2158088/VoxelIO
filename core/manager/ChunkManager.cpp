#include "ChunkManager.h"
#include <memory>

// template<typename Key, typename Chunk>
// void LRUChunkCache<Key, Chunk>::put(const Key& key, std::shared_ptr<Chunk> chunk) {
//   auto it = cache.find(key);
//   if(it != cache.end()){
//     keys.erase(it->second.second);
//   }

//   else if (cache.size() >= capacity) {
//     const auto& lruKey = keys.back();
//     cache.erase(lruKey);
//     keys.pop_back();
//   }

//   keys.push_front(key);
//   cache[key] = {chunk, keys.begin()};
// }

// template<typename Key, typename Chunk>
// std::weak_ptr<Chunk> LRUChunkCache<Key, Chunk>::get(const Key& key){
//   auto it = cache.find(key);
//         if (it == cache.end()) {
//             // Chunk not found
//             return std::weak_ptr<Chunk>();
//         }

//         // Move this chunk to the front of the usage list
//         keys.erase(it->second.second);
//         keys.push_front(key);
//         it->second.second = keys.begin();

//         // Return a weak_ptr to the chunk
//         return std::weak_ptr<Chunk>(it->second.first);
// }
