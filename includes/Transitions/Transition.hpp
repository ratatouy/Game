#ifndef TRANSITION_HPP
#define TRANSITION_HPP


class Scene; // Forward declaration of Scene //


////////////////////////////////////////////////////////////
/// \brief Object to manage transitions between Scenes
///
/// A transition can be of any kind, it just needs a target Scene
/// and a way to check if it should be activated.
////////////////////////////////////////////////////////////
class Transition
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructs a Transition from a Scene and a target Scene
    ///
    /// \param scene Pointer to the attached Scene
    ///
    /// \param target Name of the targeted Scene
    ////////////////////////////////////////////////////////////
    Transition(Scene* scene, std::string target) : scene_(scene), target_(target) {}


    ////////////////////////////////////////////////////////////
    /// \brief Check if the transition should be activated
    ///
    /// \returns True if the Transition should be activated
    ////////////////////////////////////////////////////////////
    virtual bool checkTransition() const;


    ////////////////////////////////////////////////////////////
    /// \brief Check if the transition should be activated according to the player's TransformableComponent
    ///
    /// \param player_tr The player's TransformableComponents
    ///
    /// \returns True if the Transition should be activated
    ////////////////////////////////////////////////////////////
    virtual bool checkTransition(TransformableComponent* player_tr) const;


    ////////////////////////////////////////////////////////////    
    /// \brief Returns the name of the targeted Scene
    ///
    /// \returns Name of the targeted Scene
    ////////////////////////////////////////////////////////////
    const std::string& getTargetName() const { return target_; }


protected:
    Scene* scene_;       /// Pointer to the attached Scene
    std::string target_; /// Name of the targeted Scene 

};


#endif