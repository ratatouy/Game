#ifndef TRANSITION_HPP
#define TRANSITION_HPP


class Transition
{
private:
    const char* target_; /**< Name of the targeted Scene */


public:
    virtual bool CheckTransition() const;

};


#endif