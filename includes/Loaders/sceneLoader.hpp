#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Scenes/Scene.hpp"


////////////////////////////////////////////////////////////
/// \brief Loads and builds a scene from a json file and returns a pointer to it
///
/// Loads :
/// \li origin
/// \li size
///
/// Missing :
/// \li colliders
/// \li transitions
/// \li entities
///
/// \param name Name of the scene to load
///
/// \param filepath Path to the json file (default : "Data/GameData/sceneData.json")
///
/// \return Pointer to the loaded scene
///
/// \see Scene
////////////////////////////////////////////////////////////
Scene* LoadScene(std::string name, std::string filepath = "Data/GameData/sceneData.json");


#endif