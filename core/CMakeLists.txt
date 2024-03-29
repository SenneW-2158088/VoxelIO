add_library(model STATIC
        model/Game.h
        model/Game.cpp

        model/Entity.h
        model/Entity.cpp
        )

add_library(graphics STATIC
        graphics/Mesh.h
        graphics/Mesh.cpp

        graphics/Shader.h
        graphics/Shader.cpp
        )

add_library(gameplay STATIC
        gameplay/Command.h
        gameplay/Command.cpp
        gameplay/State.h
        gameplay/State.cpp
        )