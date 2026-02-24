#!/bin/bash

#===========================================================#
# Run this script from the root of the project ("sfml" dir) #
#===========================================================#

##############
# MAIN BUILD #
##############

echo "\\\\\\\\\\\\MAIN/////////"
echo "=====COMPILE====="

### Compiling files :
source_files="main.cpp"
source_files+=" Source/Engine/RenderEngine.cpp"

source_files+=" Source/Scenes/Scene.cpp"

source_files+=" Source/Events/EventHandler.cpp"
source_files+=" Source/Events/CustomEvents/HitEvent.cpp"

source_files+=" Source/Entity/Entity.cpp"
source_files+=" Source/Entity/Ennemies/Ennemy.cpp"
source_files+=" Source/Entity/Player/Player.cpp"
source_files+=" Source/Entity/Projectiles/Projectile.cpp"

source_files+=" Source/Components/EntitySpriteComponent.cpp"
source_files+=" Source/Components/TransformableComponent.cpp"


# -lsfml-graphics -lsfml-window -lsfml-system are linking to the SFML libraries #
# -I./Headers is linking to the Headers folder                                  #
# -o Executables/main is putting the executable in the Executables folder       #
g++  -I./Headers ${source_files} -lsfml-graphics -lsfml-window -lsfml-system -o main


# Check if compilation was successful #
if [ $? -ne 0 ]; then
    echo "BASH_BUILD : Compilation failed"
    # Exit if compilation failed #
    exit 1
else
    echo "BASH_BUILD : Compilation Successful"
fi

echo "======RUN========"

./main

echo "======END========"