#ifndef BORDERTRANSITION_HPP
#define BORDERTRANSITION_HPP


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Transitions/Transition.hpp"
#include "Components/BasicComponents/TransformableComponent.hpp"



////////////////////////////////////////////////////////////
/// \brief Manages transitions from the border of a screen to a neighboring screen
///
/// This class is the base class for VerticalTransition and HorizontalTransition.
/// And is not intended to be used directly.
////////////////////////////////////////////////////////////
class BorderTransition : public Transition
{
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Constructs a BorderTransition from a Scene, a target Scene, a start position and an end position
        ///
        /// If start > end, start and end are swapped.
        ///
        /// \param scene Pointer to the attached Scene
        ///
        /// \param target Name of the targeted Scene
        ///
        /// \param start Position of left-most pixel of the transition if it's vertical
        ///              , top-most pixel if it's horizontal.
        ///
        /// \param end Position of the right-most pixel of the transition if it's vertical
        ///            , bottom-most if it's horizontals.
        ////////////////////////////////////////////////////////////
        BorderTransition(Scene* scene, std::string target, int start, int end)
            : Transition(scene, target)
        {
            if (start > end) std::swap(start, end);
            start_ = start;
            end_ = end;
        }



    protected:
        int start_;
        ///< position of left-most pixel of the transition if it's vertical
        ///, top-most if it's horizontal.

        int end_;
        ///< position of the right-most pixel of the transition if it's vertical
        ///, bottom-most if it's horizontal.
};




////////////////////////////////////////////////////////////
/// \brief Vertical Transition to a neighboring scene
///
/// A Vertical Transition is essentially a line caracterized by two points on the same x axis
/// That activates if the player is between or past those two points.
/// The Transition can either go up or go down.
/// Usually the transition is placed on the top or bottom border of the scene.
////////////////////////////////////////////////////////////
class VerticalTransition : public BorderTransition
{
public:
    VerticalTransition(Scene* scene, std::string target, int start, int end, bool down = true)
        : BorderTransition(scene, target, start, end), down_(down) {}


    ////////////////////////////////////////////////////////////
    /// \brief Checks if the player is within the activation zone of the transition
    ///
    /// \param player_tr The player's TransformableComponent
    ///
    /// \returns True if the Transition should be activated
    ////////////////////////////////////////////////////////////
    bool checkTransition(TransformableComponent* player_tr) const override;



private:
    bool down_; ///< Does the transition go down ?
};



////////////////////////////////////////////////////////////
/// \brief Horizontal Transition to a neighboring scene
///
/// A Horizontal Transition is essentially a line caracterized by two points on the same y axis
/// That activates if the player is between or past those two points.
/// The Transition can either go left or go right.
/// Usually the transition is placed on the left or right border of the scene.
////////////////////////////////////////////////////////////
class HorizontalTransition : public BorderTransition
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief Constructs a HorizontalTransition from a Scene, a target Scene
    ///         , a start position, an end position and a direction
    ///
    /// The start and end are the two opposite "points" of the transition.
    /// If start > end, start and end are swapped,
    /// right defaults to true.
    /// 
    /// \param scene Pointer to the attached Scene
    /// 
    /// \param target Name of the targeted Scene
    ///
    /// \param start Position of left-most pixel of the transition if it's vertical
    ///              , top-most pixel if it's horizontal.
    ///
    /// \param end Position of the right-most pixel of the transition if it's vertical
    ///            , bottom-most if it's horizontals.
    ///
    /// \param right Does the transition go right ? Defaults to true
    ////////////////////////////////////////////////////////////
    HorizontalTransition(Scene* scene, std::string target, int start, int end, bool right = true)
        : BorderTransition(scene, target, start, end), right_(right) {}



    ////////////////////////////////////////////////////////////
    /// \brief Check if the player is within or past the activation zone of the transition
    ///
    /// \param player_tr The player's TransformableComponent
    ///
    /// \returns True if the Transition should be activated
    ////////////////////////////////////////////////////////////
    bool checkTransition(TransformableComponent* player_tr) const override;



private:
    bool right_; ///< Does the transition go right ?

};


#endif