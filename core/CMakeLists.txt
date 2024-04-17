add_library(game STATIC
        game/Game.h
        game/Game.cpp
        )

add_library(model STATIC
        model/Entity.h
        model/Entity.cpp

        model/Player.h
        model/Player.cpp

        model/Camera.h
        model/Camera.cpp

        model/Voxel.h
        model/Voxel.cpp

        model/Triangle.h
        model/Triangle.cpp

        model/VoxelTerrain.h
        model/VoxelTerrain.cpp
        )

add_library(graphics STATIC
        graphics/Mesh.h
        graphics/Mesh.cpp

        graphics/Shader.h
        graphics/Shader.cpp

        graphics/Uniform.h
        graphics/Uniform.cpp

        graphics/Texture.h
        graphics/Texture.cpp

        graphics/Cubemap.h
        graphics/Cubemap.cpp
        )

add_library(gameplay STATIC
        gameplay/Command.h
        gameplay/Command.cpp

        gameplay/State.h
        gameplay/State.cpp

        gameplay/Collision.h
        gameplay/Collision.cpp

        gameplay/Noise.h
        gameplay/Noise.cpp

        gameplay/db_perlin.h
        gameplay/db_perlin.cpp

        gameplay/Chunk.h
        gameplay/Chunk.cpp

        gameplay/Terrain.hpp
        )

add_library(engine STATIC
        engine/GameEngine.h
        engine/GameEngine.cpp
        )

add_library(manager STATIC
        manager/AssetManager.h
        manager/AssetManager.cpp

        manager/InputManager.h
        manager/InputManager.cpp

        manager/WindowManager.h
        manager/WindowManager.cpp

        manager/CameraHandler.h
        manager/CameraHandler.cpp

        manager/ChunkManager.h
        manager/ChunkManager.cpp
        )

add_library(generator STATIC

        generator/Generator.hpp

        generator/ChunkGenerator.h
        generator/ChunkGenerator.cpp
)
