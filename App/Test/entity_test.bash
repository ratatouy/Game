#!/bin/bash

#==========================================================
# Run this script from the root of the project ("sfml" dir)
#==========================================================

# This is a test build for the EventManager

echo "\\\\\\\\\\\\Entity Test/////////"
echo "=====COMPILE====="


### Compiling files :
compiling_files="Test/entity_test.cpp"
compiling_files+=" Source/Entity/Entity.cpp"
compiling_files+=" Source/Components/EntitySpriteComponent.cpp"


# -lsfml-graphics -lsfml-window -lsfml-system are linking to the SFML libraries #
# -I./Headers is linking to the Headers folder                                  #
# -o Executables/main is putting the executable in the Executables folder       #
g++ -I./Headers ${compiling_files} -lsfml-graphics -lsfml-window -lsfml-system -o Test/entity_test


# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "BASH_BUILD : Compilation failed"
    exit 1
else
    echo "BASH_BUILD : Compilation Successful"
fi


echo "======RUN========"

./Test/entity_test

echo "======END========"