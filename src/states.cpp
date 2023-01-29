#include "states.hpp"

#include "operators.hpp"

// =============== Idle ===============================

void Idle::Enter(StateMachine *sm)
{
    // sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.idle);
}

void Idle::Execute(StateMachine *sm)
{
    // Serial << F("IDLE execute\n");
    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states->start_up);
    }
}

// =============== Start up ===============================

StartUp::StartUp()
{
    this->sub_state = SubState::INITIAL_FILL_UP;
}

void StartUp::Enter(StateMachine *sm)
{
    // Serial << F("STARTUP enter\n");
    sm->ClearAllEvents();
    sm->ClearTimer();
    // sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.start_up);
}

void StartUp::Execute(StateMachine *sm)
{
    // increment timer based on main timer - default: 100ms
    this->IncrementStateTimer();

    // Serial << "State StartUp is running...\n";
    switch (this->sub_state)
    {
    case SubState::INITIAL_FILL_UP:
        sm->device_manager.pellet_spiral.Start();
        sm->device_manager.cartridge_heater.Start();
        sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_1610);
        if (sm->timer_ms > 110000)
        {
            Serial << F("INITIAL_FILL_UP\n");
            sm->device_manager.pellet_spiral.Stop();
            sm->ClearTimer();
            sub_state = SubState::INITIAL_STALLING;
        }
        break;
    case SubState::INITIAL_STALLING:
        if (sm->timer_ms > 170000)
        {
            Serial << F("INITIAL_STALLING\n");
            sm->ClearTimer();
            sub_state = SubState::FILL_UP;
        }
        break;
    case SubState::FILL_UP:
        sm->device_manager.pellet_spiral.Start();
        if (sm->timer_ms > 1100)
        {
            Serial << F("FILL_UP\n");
            sm->device_manager.pellet_spiral.Stop();
            sm->ClearTimer();
            sub_state = SubState::STALLING;
        }
        break;
    case SubState::STALLING:
        if (sm->timer_ms > 2900)
        {
            Serial << F("STALLING\n");
            sm->ClearTimer();
            sub_state = SubState::FILL_UP;
        }
        break;
    }

    // timer will be replaced by temperature sensor event
    if (this->state_timer_ms >= START_UP_TIME)
    {
        sm->SetNextState(sm->available_states->program_1);
        sm->device_manager.cartridge_heater.Stop();
    }

    if (sm->events.short_button_pressed)
    {
        sm->SetNextState(sm->available_states->program_1);
        sm->device_manager.cartridge_heater.Stop();
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states->turn_off);
    }
}

void StartUp::Exit(StateMachine *sm)
{
    Serial << F("STARTUP exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states->start_up);
}

// =============== Program 1 ===============================
ProgramOne::ProgramOne()
{
    this->sub_state = SubState::FILL_UP;
}

void ProgramOne::Enter(StateMachine *sm)
{
    Serial << F("P1 enter\n");
    sm->ClearAllEvents();
    sm->ClearTimer();
    // sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_1);
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_1360);
}

void ProgramOne::Execute(StateMachine *sm)
{
    // Serial << F("P1 execute\n");
    this->IncrementStateTimer();

    switch (this->sub_state)
    {
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

    if (this->state_timer_ms >= TIME_FOR_CLEANING)
    {
        sm->SetNextState(sm->available_states->cleaning);
    }

    if (sm->events.short_button_pressed)
    {
        sm->SetNextState(sm->available_states->program_2);
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states->turn_off);
    }
}

void ProgramOne::Exit(StateMachine *sm)
{
    Serial << F("P1 exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states->program_1);
}

// =============== Program 2 ===============================
ProgramTwo::ProgramTwo()
{
    this->sub_state = SubState::FILL_UP;
}

void ProgramTwo::Enter(StateMachine *sm)
{
    sm->ClearAllEvents();
    sm->ClearTimer();
    // sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_2);
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_1470);
}

void ProgramTwo::Execute(StateMachine *sm)
{
    this->IncrementStateTimer();

    switch (this->sub_state)
    {
    case SubState::FILL_UP:
        sm->device_manager.pellet_spiral.Start();
        if (sm->timer_ms > 1500)
        {
            // Serial << F("FILL_UP\n");
            sm->device_manager.pellet_spiral.Stop();
            sm->ClearTimer();
            sub_state = SubState::STALLING;
        }
        break;
    case SubState::STALLING:
        if (sm->timer_ms > 2500)
        {
            // Serial << F("STALLING\n");
            sm->ClearTimer();
            sub_state = SubState::FILL_UP;
        }
        break;
    }

    if (this->state_timer_ms >= TIME_FOR_CLEANING)
    {
        sm->SetNextState(sm->available_states->cleaning);
    }

    if (sm->events.short_button_pressed)
    {
        sm->SetNextState(sm->available_states->idle);
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states->turn_off);
    }
}

void ProgramTwo::Exit(StateMachine *sm)
{
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states->program_2);
}

// =============== Turn off ===============================

void TurnOff::Enter(StateMachine *sm)
{
    sm->ClearAllEvents();
    sm->ClearTimer();
    // sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.turn_off);
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_2660);
    sm->device_manager.pellet_spiral.Stop();
}

void TurnOff::Execute(StateMachine *sm)
{
    this->IncrementStateTimer();

    if (this->state_timer_ms >= 3000)
    {
        sm->SetNextState(sm->available_states->idle);
    }
}

void TurnOff::Exit(StateMachine *sm)
{
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states->turn_off);
}

// =============== Clean up ===============================

Cleaning::Cleaning()
{
    this->sub_state = SubState::FILL_UP;
}

void Cleaning::Enter(StateMachine *sm)
{
    Serial << F("CLEANING enter\n");
    sm->ClearAllEvents();
    sm->ClearTimer();
    // sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_2);
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_2660);
}

void Cleaning::Execute(StateMachine *sm)
{
    this->IncrementStateTimer();

    switch (this->sub_state)
    {
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

    if (this->state_timer_ms >= 20000) // 20 s
    {
        sm->SetNextState(*sm->GetPreviousState());
    }
}

void Cleaning::Exit(StateMachine *sm)
{
    Serial << F("CLEANING exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states->cleaning);
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