#ifndef TRANSITION_HPP
#define TRANSITION_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "string"
#include "SFML/Graphics.hpp"
#include "Components/BasicComponents/ColliderComponent.hpp"

#include "logger.hpp"

class Scene; // Forward declaration of Scene //


////////////////////////////////////////////////////////////
/// \brief Object to manage transitions between Scenes
///
/// It's an abstract class.
/// A transition can be of any kind, it just needs a target Scene
/// and a way to check if it should be activated.
////////////////////////////////////////////////////////////
class Transition
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructs a Transition from a Scene, a target Scene and a name
    ///
    /// \param scene Pointer to the attached Scene
    ///
    /// \param target Name of the targeted Scene
    ///
    /// \param name Name of the Transition
    ////////////////////////////////////////////////////////////
    Transition(Scene* scene, std::string target, std::string name) : scene_(scene), target_(target), name_(name) {}

    ////////////////////////////////////////////////////////////
    /// \brief Returns the name of the Transition
    ///
    /// \returns Name of the Transition
    ////////////////////////////////////////////////////////////
    std::string getName() {return name_;}

    ////////////////////////////////////////////////////////////
    /// \brief Check if the transition should be activated
    ///
    /// Override if needed
    ///
    /// \returns True if the Transition should be activated
    ////////////////////////////////////////////////////////////
    virtual bool checkTransition() const {return false;}

    ////////////////////////////////////////////////////////////    
    /// \brief Returns the name of the targeted Scene
    ///
    /// \returns Name of the targeted Scene
    ////////////////////////////////////////////////////////////
    const std::string& getTargetName() const { return target_; }


protected:
    ////////////////////////////////////////////////////////////
    /// Member Data
    ////////////////////////////////////////////////////////////
    Scene* scene_;         ///< Pointer to the attached Scene
    std::string target_;   ///< Name of the targeted Scene 
    std::string name_;     ///< Name of the Transition

};


#endif