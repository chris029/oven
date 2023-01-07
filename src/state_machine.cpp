#include "state_machine.hpp"

#include "operators.hpp"

StateMachine::StateMachine(AvailableStates *avStates)
{
    availableStates = avStates;
    currentState = &availableStates->idle;
}

void StateMachine::setState(State &newState)
{
    currentState->exit(this);
    currentState = &newState;
    currentState->enter(this);
}

void StateMachine::run()
{
    // Delegate the task of determining the next state to the current state!
    currentState->execute(this);
}
