cmake_minimum_required(VERSION 3.22.1)
project(RatatouySFMLGame CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

set(SOURCE_FILES
    src/main.cpp
    src/Components/TransformableComponent.cpp
    src/Components/EntitySpriteComponent.cpp

    src/Events/CustomEvents/HitEvent.cpp
    src/Events/EventHandler.cpp

    src/Entity/Entity.cpp
    src/Entity/Player/Player.cpp
    src/Entity/Ennemies/Ennemy.cpp
    src/Entity/Projectiles/Projectile.cpp

    src/Engine/PhysicEngine.cpp
    src/Engine/RenderEngine.cpp

    src/Scenes/Scene.cpp
)

add_executable(main ${SOURCE_FILES})
target_compile_features(main PRIVATE cxx_std_17)
target_include_directories(main PRIVATE Headers)
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
