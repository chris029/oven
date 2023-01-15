#pragma once

// both times are defined in seconds
struct DosingTimes
{
    float rotation_time_s;
    float waiting_time_s;
};

struct AvailableDosingModes
{
    DosingTimes start_up = {110, 170};
    DosingTimes mode_1 = {2.9, 1.1};
    DosingTimes mode_2 = {2.5, 1.5};
    DosingTimes mode_3 = {2.1, 1.9};
    DosingTimes mode_4 = {1.8, 2.2};
    DosingTimes mode_5 = {1.5, 2.5};
    DosingTimes cleaning = {2.9, 1.1};
};

class PelletSpiral
{
    DosingTimes dosing_mode;

public:
    const AvailableDosingModes kAvailableDosingModes;

    PelletSpiral();
    void SetDosingMode(DosingTimes dosing);
    float GetRotationTime();
    float GetWaitingTime();
    void Rotate();
};