#!/bin/bash

#===========================================================#
# Run this script from the root of the project ("sfml" dir) #
#===========================================================#

# This is a test build for the EventManager

echo "\\\\\\\\\\\\Event Test/////////"
echo "=====COMPILE====="

### Compiling files :
source_files="Test/event_test.cpp"
source_files+=" Source/Scenes/Scene.cpp"
source_files+=" Source/Events/EventHandler.cpp"
source_files+=" Source/Events/CustomEvents/HitEvent.cpp"
source_files+=" Source/Entity/Entity.cpp"
source_files+=" Source/Entity/Ennemies/Ennemy.cpp"
source_files+=" Source/Entity/Player/Player.cpp"


# -I./Headers is linking to the Headers folder
# -o Executables/main is putting the executable in the Executables folder
g++ -I./Headers ${source_files} -o Test/event_test


# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "BASH_BUILD : Compilation failed"
    exit 1
else
    echo "BASH_BUILD : Compilation Successful"
fi


echo "======RUN========"

./Test/event_test

echo "======END========"