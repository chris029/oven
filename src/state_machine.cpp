#include "state_machine.hpp"

#include "operators.hpp"

StateMachine::StateMachine(AvailableStates *avStates)
{
    available_states = avStates;
    current_state = &available_states->idle;
}

void StateMachine::SetupStateMachine()
{
    StateMachine::device_manager.display.SetupDisplay();
}

void StateMachine::SetState(State &newState)
{
    current_state->Exit(this);
    current_state = &newState;
    current_state->Enter(this);
}

void StateMachine::Run()
{
    // Delegate the task of determining the next state to the current state!
    current_state->Execute(this);
}
