//
// Created by Ruicong Zhu on 31/1/23.
//

#ifndef BRPC_SHARED_ARENA_H
#define BRPC_SHARED_ARENA_H

#include <google/protobuf/arena.h>
#include <memory>


class SharedArena : public google::protobuf::Arena, public std::enable_shared_from_this<SharedArena> {
public:
    std::shared_ptr<SharedArena> get_ptr() {
        if (!_has_been_shared) {
            return nullptr;
        }
        return shared_from_this();
    }

//    // No public constructor, only a factory function,
//    [[nodiscard]] static std::shared_ptr<SharedArena> create(const google::protobuf::ArenaOptions& options) {
//        return std::shared_ptr<SharedArena>(new SharedArena(options));
//    }
    SharedArena(const google::protobuf::ArenaOptions& options) : google::protobuf::Arena(options) {};

    static std::shared_ptr<SharedArena> share(SharedArena* arena) {
        if (arena->_has_been_shared) {
            return arena->get_ptr();
        } else {
            arena->_has_been_shared = true;
            return std::shared_ptr<SharedArena>(arena);
        }
    }

private:
    SharedArena() = default;

    bool _has_been_shared = false;
};


#endif //BRPC_SHARED_ARENA_H
