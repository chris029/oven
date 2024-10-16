#include "states.hpp"
#include "operators.hpp"
#include "state_machine.hpp"

// =============== Idle ===============================

void Idle::Enter(StateMachine *sm)
{
    Serial << F("IDLE enter\n");
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_IDLE);
    sm->current_state_label = "IDLE";
}

void Idle::Execute(StateMachine *sm)
{
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.idle);
    Serial << F("IDLE...\n");
    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states.start_up);
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
    sm->device_manager.display.DisplayNextState();
    sm->device_manager.display.label_switch_cnt = -1;
    sm->current_state_label = "STARTUP";
    sub_state = SubState::INITIAL_FILL_UP;
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

    Serial << F("Start up time: ") << START_UP_TIME << F("\n");
    Serial << F("Current timer value: ") << this->state_timer_ms << F("\n");
    Serial << F("STARTUP Event number: ") << sm->events.short_button_pressed_cnt << F("\n");

    if (this->state_timer_ms >= START_UP_TIME)
    {
        sm->SetNextState(sm->available_states.program_1);
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states.turn_off);
    }
}

void StartUp::Exit(StateMachine *sm)
{
    Serial << F("STARTUP exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states.start_up);
    sm->device_manager.cartridge_heater.Stop();
    if (sm->events.short_button_pressed_cnt > 0)
    {
        sm->events.short_button_pressed_cnt--;
    }
    else
    {
        sm->device_manager.display.DisplayNextState();
    }
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
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_1);
    sm->device_manager.display.label_switch_cnt = 0;
    sm->current_state_label = "P1";
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

    Serial << F("Time for cleaning at: ") << TIME_FOR_CLEANING << F("\n");
    Serial << F("P1 Current timer value: ") << this->state_timer_ms << F("\n");
    Serial << F("P1 Event number: ") << sm->events.short_button_pressed_cnt << F("\n");

    if (this->state_timer_ms >= TIME_FOR_CLEANING)
    {
        sm->SetNextState(sm->available_states.cleaning);
    }

    if (sm->events.short_button_pressed_cnt > 0)
    {
        if (this->state_timer_ms > MINIMUM_STATE_DURATION)
        {
            sm->SetNextState(sm->available_states.program_2);
            sm->events.short_button_pressed_cnt--;
        }
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states.turn_off);
    }
}

void ProgramOne::Exit(StateMachine *sm)
{
    Serial << F("P1 exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states.program_1);
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
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_2);
    sm->current_state_label = "P2";
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

    Serial << F("Time for cleaning at: ") << TIME_FOR_CLEANING << F("\n");
    Serial << F("P2 Current timer value: ") << this->state_timer_ms << F("\n");
    Serial << F("P2 Event number: ") << sm->events.short_button_pressed_cnt << F("\n");

    if (this->state_timer_ms >= TIME_FOR_CLEANING)
    {
        sm->SetNextState(sm->available_states.cleaning);
    }

    if (sm->events.short_button_pressed_cnt > 0)
    {
        if (this->state_timer_ms > MINIMUM_STATE_DURATION)
        {
            sm->SetNextState(sm->available_states.program_3);
            sm->events.short_button_pressed_cnt--;
        }
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states.turn_off);
    }
}

void ProgramTwo::Exit(StateMachine *sm)
{
    Serial << F("P2 exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states.program_2);
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
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_3);
    sm->current_state_label = "P3";
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

    Serial << F("Time for cleaning at: ") << TIME_FOR_CLEANING << F("\n");
    Serial << F("P3 Current timer value: ") << this->state_timer_ms << F("\n");
    Serial << F("P3 Event number: ") << sm->events.short_button_pressed_cnt << F("\n");

    if (this->state_timer_ms >= TIME_FOR_CLEANING)
    {
        sm->SetNextState(sm->available_states.cleaning);
    }

    if (sm->events.short_button_pressed_cnt > 0)
    {
        if (this->state_timer_ms > MINIMUM_STATE_DURATION)
        {
            sm->SetNextState(sm->available_states.program_4);
            sm->events.short_button_pressed_cnt--;
        }
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states.turn_off);
    }
}

void ProgramThree::Exit(StateMachine *sm)
{
    Serial << F("P3 exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states.program_3);
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
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_4);
    sm->current_state_label = "P4";
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

    Serial << F("Time for cleaning at: ") << TIME_FOR_CLEANING << F("\n");
    Serial << F("P4 Current timer value: ") << this->state_timer_ms << F("\n");
    Serial << F("P4 Event number: ") << sm->events.short_button_pressed_cnt << F("\n");

    if (this->state_timer_ms >= TIME_FOR_CLEANING)
    {
        sm->SetNextState(sm->available_states.cleaning);
    }

    if (sm->events.short_button_pressed_cnt > 0)
    {
        if (this->state_timer_ms > MINIMUM_STATE_DURATION)
        {
            sm->SetNextState(sm->available_states.program_5);
            sm->events.short_button_pressed_cnt--;
        }
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states.turn_off);
    }
}

void ProgramFour::Exit(StateMachine *sm)
{
    Serial << F("P4 exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states.program_4);
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
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.program_5);
    sm->current_state_label = "P5";
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

    Serial << F("Time for cleaning at: ") << TIME_FOR_CLEANING << F("\n");
    Serial << F("P5 Current timer value: ") << this->state_timer_ms << F("\n");
    Serial << F("P5 Event number: ") << sm->events.short_button_pressed_cnt << F("\n");

    if (this->state_timer_ms >= TIME_FOR_CLEANING)
    {
        sm->SetNextState(sm->available_states.cleaning);
    }

    if (sm->events.short_button_pressed_cnt > 0)
    {
        if (this->state_timer_ms > MINIMUM_STATE_DURATION)
        {
            sm->SetNextState(sm->available_states.program_1);
            sm->events.short_button_pressed_cnt--;
        }
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states.turn_off);
    }
}

void ProgramFive::Exit(StateMachine *sm)
{
    Serial << F("P5 exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states.program_5);
}

// =============== Turn off ===============================

void TurnOff::Enter(StateMachine *sm)
{
    Serial << F("TURN OFF enter\n");
    sm->ClearAllEvents();
    sm->ClearTimer();
    sm->events.short_button_pressed_cnt = 0;
    sm->device_manager.display.label_switch_cnt = 0;
    sm->device_manager.display.pStateLabels = &sm->device_manager.display.kStateLabel.turn_off;
    sm->device_manager.display.UpdateStateLabel();
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.turn_off);
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_2660);
    sm->device_manager.pellet_spiral.Stop();
    sm->current_state_label = "TURN_OFF";
}

void TurnOff::Execute(StateMachine *sm)
{
    this->IncrementStateTimer();

    if (this->state_timer_ms >= TURN_OFF_TIME)
    {
        sm->SetNextState(sm->available_states.idle);
    }

    Serial << F("Turn off at: ") << TURN_OFF_TIME << F("\n");
    Serial << F("TURN OFF Current timer value: ") << this->state_timer_ms << F("\n");
}

void TurnOff::Exit(StateMachine *sm)
{
    Serial << F("TURN OFF exit\n");
    this->ClearStateTimer();
    sm->SetPreviousState(sm->available_states.turn_off);
    sm->device_manager.display.pStateLabels = &sm->device_manager.display.kStateLabel.idle;
    sm->device_manager.display.UpdateStateLabel();
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
    sm->device_manager.display.label_switch_cnt = 0;
    sm->device_manager.display.pStateLabels = &sm->device_manager.display.kStateLabel.program_1;
    sm->device_manager.display.label_switch_cnt = 0;
    sm->device_manager.display.UpdateStateLabel();
    sm->device_manager.display.DisplayState(sm->device_manager.display.kStateLabel.cleaning);
    sm->device_manager.exhaust_fan.SetRPM(RPMValues::RPM_2660);
    sm->current_state_label = "CLEANING";
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

    Serial << F("Cleaning time: ") << CLEANING_TIME << F("\n");
    Serial << F("Current timer value: ") << this->state_timer_ms << F("\n");
    Serial << F("CLEANING Event number: ") << sm->events.short_button_pressed_cnt << F("\n");

    if (this->state_timer_ms >= CLEANING_TIME) // 20 s
    {
        if (this->sub_state == SubState::STALLING)
            sm->SetNextState(sm->available_states.program_1);
    }

    if (sm->events.long_button_pressed)
    {
        sm->SetNextState(sm->available_states.turn_off);
    }
}

void Cleaning::Exit(StateMachine *sm)
{
    Serial << F("CLEANING exit\n");
    this->ClearStateTimer();
    Serial << F("CLEANING clear timer done.\n");
    sm->SetPreviousState(sm->available_states.cleaning);
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