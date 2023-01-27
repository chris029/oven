#include "states.hpp"

#include "operators.hpp"


// =============== Idle ===============================

void Idle::Enter(StateMachine *sm)
{
    sm->ClearAllEvents();
    sm->ClearTimer();
}

void Idle::Execute(StateMachine *sm)
{
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.idle);
    if (sm->events.long_button_pressed)
    {
        sm->SetState(sm->available_states->start_up);
    }
}


// =============== Start up ===============================

StartUp::StartUp()
{
    this->sub_state = SubState::INITIAL_FILL_UP;
}

void StartUp::Enter(StateMachine *sm)
{
    sm->ClearAllEvents();
    sm->ClearTimer();
}

void StartUp::Execute(StateMachine *sm)
{
    // Serial << "State StartUp is running...\n";
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.start_up);

    switch (this->sub_state)
    {
    case SubState::INITIAL_FILL_UP:
        sm->device_manager.pellet_spiral.Start();
        if (sm->timer_ms > 11000)
        {
            // Serial << F("INITIAL_FILL_UP\n");
            sm->device_manager.pellet_spiral.Stop();
            sm->ClearTimer();
            sub_state = SubState::INITIAL_STALLING;
        }
        break;
    case SubState::INITIAL_STALLING:
        if (sm->timer_ms > 17000)
        {
            // Serial << F("INITIAL_STALLING\n");
            sm->device_manager.cartridge_heater.Start();
            sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_1610);
            sm->ClearTimer();
            sub_state = SubState::FILL_UP;
        }
        break;
    case SubState::FILL_UP:
        sm->device_manager.pellet_spiral.Start();
        if (sm->timer_ms > 1100)
        {
            // Serial << F("FILL_UP\n");
            sm->device_manager.pellet_spiral.Stop();
            sm->ClearTimer();
            sub_state = SubState::STALLING;
        }
        break;
    case SubState::STALLING:
        if (sm->timer_ms > 2900)
        {
            // Serial << F("STALLING\n");
            sm->ClearTimer();
            sub_state = SubState::FILL_UP;
        }
        break;
    }

    // if heat_up_done (timer cnt instead) -> set new state: program_1

    if (sm->events.short_button_pressed)
    {
        sm->SetState(sm->available_states->program_1);
    }
    
    if (sm->events.long_button_pressed)
    {
        sm->SetState(sm->available_states->turn_off)
    }
}


// =============== Program 1 ===============================

void ProgramOne::Enter(StateMachine *sm)
{
    sm->ClearAllEvents();
    sm->ClearTimer();
}

void ProgramOne::Execute(StateMachine *sm)
{
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_1);

    if (sm->events.short_button_pressed)
    {
        sm->SetState(sm->available_states->program_2);
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetState(sm->available_states->turn_off)
    }
}


// =============== Program 2 ===============================

void ProgramTwo::Enter(StateMachine *sm)
{
    sm->ClearAllEvents();
    sm->ClearTimer();
}

void ProgramTwo::Execute(StateMachine *sm)
{
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_2);

    if (sm->events.short_button_pressed)
    {
        sm->SetState(sm->available_states->idle);
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetState(sm->available_states->turn_off)
    }
}


// =============== Turn off ===============================

void TurnOff::Enter(StateMachine *sm)
{
    sm->ClearAllEvents();
    sm->ClearTimer();
}

void TurnOff::Execute(StateMachine *sm)
{
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_2);

    if (sm->events.short_button_pressed)
    {
        sm->SetState(sm->available_states->idle);
    }
}


// =============== Clean up ===============================

void Cleaning::Enter(StateMachine *sm)
{
    sm->ClearAllEvents();
    sm->ClearTimer();
}

void Cleaning::Execute(StateMachine *sm)
{
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_2);

    if (sm->events.short_button_pressed)
    {
        sm->SetState(sm->available_states->idle);
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetState(sm->available_states->turn_off)
    }
}

// Just in case - reading serial input to set triac output voltage manually
// if (Serial.available())
// {
//     byte m = Serial.readBytesUntil('\n', myData, 2);
//     myData[m] = '\0';     // insert null charcater
//     int x = atoi(myData); // converts string to int
//     Serial << F("Power: ") << x << F("\n");
//     sm->device_manager.exhaust_fan.SetRPM(x);
// }