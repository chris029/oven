#include "states.hpp"

#include "operators.hpp"

// =============== Idle ===============================

void Idle::Enter(StateMachine *sm)
{
    Serial << F("IDLE enter\n");
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_IDLE);
}

void Idle::Execute(StateMachine *sm)
{
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.idle);
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
    Serial << F("STARTUP enter\n");
    sm->ClearAllEvents();
    sm->ClearTimer();
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.start_up);
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
        if (sm->timer_ms > INITIAL_FILL_UP_DURATION)
        {
            Serial << F("INITIAL_FILL_UP\n");
            sm->device_manager.pellet_spiral.Stop();
            sm->ClearTimer();
            sub_state = SubState::INITIAL_STALLING;
        }
        break;
    case SubState::INITIAL_STALLING:
        if (sm->timer_ms > INITIAL_STALLING_DURATION)
        {
            Serial << F("INITIAL_STALLING\n");
            sm->ClearTimer();
            sub_state = SubState::FILL_UP;
        }
        break;
    case SubState::FILL_UP:
        sm->device_manager.pellet_spiral.Start();
        if (sm->timer_ms > STARTUP_FILL_UP_DURATION)
        {
            Serial << F("FILL_UP\n");
            sm->device_manager.pellet_spiral.Stop();
            sm->ClearTimer();
            sub_state = SubState::STALLING;
        }
        break;
    case SubState::STALLING:
        if (sm->timer_ms > STARTUP_STALLING_DURATION)
        {
            Serial << F("STALLING\n");
            sm->ClearTimer();
            sub_state = SubState::FILL_UP;
        }
        break;
    }

    if (this->state_timer_ms >= START_UP_TIME)
    {
        sm->SetNextState(sm->available_states->program_1);
        sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_1);
        sm->device_manager.cartridge_heater.Stop();
        sm->events.short_button_pressed_cnt--;
    }

    // if (sm->events.short_button_pressed)
    // {
    //     sm->SetNextState(sm->available_states->program_1);
    //     sm->device_manager.cartridge_heater.Stop();
    // }

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
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_1360);
}

void ProgramOne::Execute(StateMachine *sm)
{
    this->IncrementStateTimer();

    switch (this->sub_state)
    {
    case SubState::FILL_UP:
        sm->device_manager.pellet_spiral.Start();
        if (sm->timer_ms > PROGRAM_ONE_FILL_UP_DURATION)
        {
            // Serial << F("FILL_UP\n");
            sm->device_manager.pellet_spiral.Stop();
            sm->ClearTimer();
            sub_state = SubState::STALLING;
        }
        break;
    case SubState::STALLING:
        if (sm->timer_ms > PROGRAM_ONE_STALLING_DURATION)
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

    if (sm->events.short_button_pressed_cnt > 0)
    {
        if (this->state_timer_ms > MINIMUM_STATE_DURATION)
        {
            sm->SetNextState(sm->available_states->program_2);
            sm->events.short_button_pressed_cnt--;
        }
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
    Serial << F("P2 enter\n");
    sm->ClearAllEvents();
    sm->ClearTimer();
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_1470);
}

void ProgramTwo::Execute(StateMachine *sm)
{
    this->IncrementStateTimer();

    switch (this->sub_state)
    {
    case SubState::FILL_UP:
        sm->device_manager.pellet_spiral.Start();
        if (sm->timer_ms > PROGRAM_TWO_FILL_UP_DURATION)
        {
            // Serial << F("FILL_UP\n");
            sm->device_manager.pellet_spiral.Stop();
            sm->ClearTimer();
            sub_state = SubState::STALLING;
        }
        break;
    case SubState::STALLING:
        if (sm->timer_ms > PROGRAM_TWO_STALLING_DURATION)
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

    if (sm->events.short_button_pressed_cnt > 0)
    {
        if (this->state_timer_ms > MINIMUM_STATE_DURATION)
        {
            sm->SetNextState(sm->available_states->program_3);
            sm->events.short_button_pressed_cnt--;
        }
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states->turn_off);
    }
}

void ProgramTwo::Exit(StateMachine *sm)
{
    Serial << F("P2 exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states->program_2);
}

// =============== Program 3 ===============================
ProgramThree::ProgramThree()
{
    this->sub_state = SubState::FILL_UP;
}

void ProgramThree::Enter(StateMachine *sm)
{
    Serial << F("P3 enter\n");
    sm->ClearAllEvents();
    sm->ClearTimer();
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_1610);
}

void ProgramThree::Execute(StateMachine *sm)
{
    this->IncrementStateTimer();

    switch (this->sub_state)
    {
    case SubState::FILL_UP:
        sm->device_manager.pellet_spiral.Start();
        if (sm->timer_ms > PROGRAM_THREE_FILL_UP_DURATION)
        {
            // Serial << F("FILL_UP\n");
            sm->device_manager.pellet_spiral.Stop();
            sm->ClearTimer();
            sub_state = SubState::STALLING;
        }
        break;
    case SubState::STALLING:
        if (sm->timer_ms > PROGRAM_THREE_STALLING_DURATION)
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

    if (sm->events.short_button_pressed_cnt > 0)
    {
        if (this->state_timer_ms > MINIMUM_STATE_DURATION)
        {
            sm->SetNextState(sm->available_states->program_4);
            sm->events.short_button_pressed_cnt--;
        }
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states->turn_off);
    }
}

void ProgramThree::Exit(StateMachine *sm)
{
    Serial << F("P3 exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states->program_3);
}

// =============== Program 3 ===============================
ProgramFour::ProgramFour()
{
    this->sub_state = SubState::FILL_UP;
}

void ProgramFour::Enter(StateMachine *sm)
{
    Serial << F("P4 enter\n");
    sm->ClearAllEvents();
    sm->ClearTimer();
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_1690);
}

void ProgramFour::Execute(StateMachine *sm)
{
    this->IncrementStateTimer();

    switch (this->sub_state)
    {
    case SubState::FILL_UP:
        sm->device_manager.pellet_spiral.Start();
        if (sm->timer_ms > PROGRAM_FOUR_FILL_UP_DURATION)
        {
            // Serial << F("FILL_UP\n");
            sm->device_manager.pellet_spiral.Stop();
            sm->ClearTimer();
            sub_state = SubState::STALLING;
        }
        break;
    case SubState::STALLING:
        if (sm->timer_ms > PROGRAM_FOUR_STALLING_DURATION)
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

    if (sm->events.short_button_pressed_cnt > 0)
    {
        if (this->state_timer_ms > MINIMUM_STATE_DURATION)
        {
            sm->SetNextState(sm->available_states->program_5);
            sm->events.short_button_pressed_cnt--;
        }
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states->turn_off);
    }
}

void ProgramFour::Exit(StateMachine *sm)
{
    Serial << F("P4 exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states->program_4);
}

// =============== Program 5 ===============================
ProgramFive::ProgramFive()
{
    this->sub_state = SubState::FILL_UP;
}

void ProgramFive::Enter(StateMachine *sm)
{
    Serial << F("P5 enter\n");
    sm->ClearAllEvents();
    sm->ClearTimer();
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_1850);
}

void ProgramFive::Execute(StateMachine *sm)
{
    this->IncrementStateTimer();

    switch (this->sub_state)
    {
    case SubState::FILL_UP:
        sm->device_manager.pellet_spiral.Start();
        if (sm->timer_ms > PROGRAM_FIVE_FILL_UP_DURATION)
        {
            // Serial << F("FILL_UP\n");
            sm->device_manager.pellet_spiral.Stop();
            sm->ClearTimer();
            sub_state = SubState::STALLING;
        }
        break;
    case SubState::STALLING:
        if (sm->timer_ms > PROGRAM_FIVE_STALLING_DURATION)
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

    if (sm->events.short_button_pressed_cnt > 0)
    {
        if (this->state_timer_ms > MINIMUM_STATE_DURATION)
        {
            sm->SetNextState(sm->available_states->program_1);
            sm->events.short_button_pressed_cnt--;
        }
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states->turn_off);
    }
}

void ProgramFive::Exit(StateMachine *sm)
{
    Serial << F("P5 exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states->program_5);
}

// =============== Turn off ===============================

void TurnOff::Enter(StateMachine *sm)
{
    sm->ClearAllEvents();
    sm->ClearTimer();
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.turn_off);
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_2660);
    sm->device_manager.pellet_spiral.Stop();
}

void TurnOff::Execute(StateMachine *sm)
{
    this->IncrementStateTimer();

    if (this->state_timer_ms >= TURN_OFF_TIME)
    {
        sm->SetNextState(sm->available_states->idle);
    }
}

void TurnOff::Exit(StateMachine *sm)
{
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states->turn_off);
    sm->device_manager.cartridge_heater.Stop();
    sm->device_manager.pellet_spiral.Stop();
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
    // sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.cleaning);
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
        sm->SetNextState(sm->available_states->program_1);
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