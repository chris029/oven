#pragma once

class ExhaustFan
{
    int rpm = 0;

public:
    void SetRPM(int rotation_speed);
    int GetRPM();
    void Start();
    void Stop();
};