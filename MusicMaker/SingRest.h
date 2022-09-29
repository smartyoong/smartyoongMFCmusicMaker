#pragma once
#include "SingNote.h"
class SingRest :
    public SingNote
{
private:
    double time =0;
    bool Rest = true;
    /*������ ���� �ʱ� ���� ������*/
    bool sharp = false;
    bool slow = false;
    int Notename = 3;
    int Ocatave = 0;
public:
    SingRest(double t ) : time(t) {}
    void SetTime(double t) { time = t; }
    virtual DWORD Sing();
    virtual DWORD Stop();
    virtual void Wait();
    virtual DWORD MidiCommand(int status, int channel, int low, int high);
    virtual double GetTime() { return time; }
    virtual bool IsSharp() { return sharp; }
    virtual bool IsSlow() { return slow; }
    virtual int GetNoteName() { return Notename; }
    virtual int GetOcatave() { return Ocatave; }
    virtual bool IsHarmony() { return false; }
    bool IsRest() { return Rest; }
};

