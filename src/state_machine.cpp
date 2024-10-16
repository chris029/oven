#include "state_machine.hpp"
#include "operators.hpp"

StateMachine::StateMachine()
{
    current_state = &available_states.idle;
    current_state_label = "IDLE";
}

void StateMachine::SetupStateMachine()
{
    StateMachine::device_manager.SetupDevices();
}

void StateMachine::SetNextState(State &state)
{
    current_state->Exit(this);
    current_state = &state;
    current_state->Enter(this);
}

void StateMachine::SetPreviousState(State &state)
{
    previous_state = &state;
}

State *StateMachine::GetPreviousState()
{
    return previous_state;
}

void StateMachine::Run()
{
    if (!(this->current_state_label == "IDLE" || this->current_state_label == "TURN_OFF"))
    {
        if (this->events.short_button_pressed)
        {
            if (this->events.short_button_pressed_cnt >= 5)
            {
                this->events.short_button_pressed_cnt = 0;
            }
            this->events.short_button_pressed_cnt++;
            this->device_manager.display.DisplayNextState();
            this->events.short_button_pressed = false;
        }
    }
    // increment timer based on main timer - default: 100ms
    this->timer_ms += 100;
    // Delegate the task of determining the next state to the current state
    current_state->Execute(this);
}

void StateMachine::ClearAllEvents()
{
    this->events.heating_up_done = false;
    this->events.long_button_pressed = false;
    this->events.short_button_pressed = false;
}

void StateMachine::ClearTimer()
{
    this->timer_ms = 0;
}