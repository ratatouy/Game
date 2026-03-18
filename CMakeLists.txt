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

## Set project source files
Set(SOURCE_FILES
    src/Components/EntitySpriteComponent.cpp

    src/Events/CustomEvents/HitEvent.cpp
    src/Events/EventHandler.cpp

    src/Entity/Player/Player.cpp
    src/Entity/Ennemies/Ennemy.cpp
    src/Entity/Projectiles/Projectile.cpp

    src/Loaders/sceneLoader.cpp

    # src/Transition/Transition.cpp

    src/Engine/PhysicsEngine.cpp
    src/Engine/RenderEngine.cpp

    src/Scenes/Scene.cpp

    src/Game.cpp

    src/logger.cpp
)


# if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
#     include(CTest)
# endif()

# if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
#     add_subdirectory(Test)
# endif()

## Setup renderTest
add_executable(renderTest ${SOURCE_FILES} Tests/RenderTest/renderTest.cpp)
target_compile_features(renderTest PRIVATE cxx_std_17)
target_include_directories(renderTest PRIVATE includes)
target_include_directories(renderTest PRIVATE extlibs)
target_link_libraries(renderTest PRIVATE sfml-graphics sfml-window sfml-system)
add_test(NAME renderTest COMMAND renderTest)
 
## Setup ParsingTest
add_executable(parsingTest ${SOURCE_FILES} Tests/ParsingTest/ParsingTest.cpp)
target_compile_features(parsingTest PRIVATE cxx_std_17)
target_include_directories(parsingTest PRIVATE includes)
target_include_directories(parsingTest PRIVATE extlibs)
target_link_libraries(parsingTest PRIVATE sfml-graphics sfml-window sfml-system)
add_test(NAME parsingTest COMMAND parsingTest)
 

## Set project executable output
add_executable(main ${SOURCE_FILES} src/main.cpp)
target_compile_features(main PRIVATE cxx_std_17)
target_include_directories(main PRIVATE includes)
target_include_directories(main PRIVATE extlibs)
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
