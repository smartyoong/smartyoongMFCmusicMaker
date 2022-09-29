#pragma once
#include "SingNote.h"
#include <vector>

using std::vector;
class SingHarmony :
    public SingNote
{
private:
    double SingTime = 0;
    int Instronument = PIANO;
	DWORD* dp;
	DWORD* ds;
public:
    vector<int> NoteName;
    vector<int> Octave;
    vector<bool> Sharp;
    vector <bool> Slow;
    SingHarmony(int i, double t) : Instronument(i), SingTime(t) {}
	DWORD* PlayHarmony();
	virtual void Wait();
	vector<int>& GetHarmonyNoteName() { return NoteName; }
	virtual double GetTime() { return SingTime; }
	vector<bool>& HarmonyIsSharp() {return Sharp; }
	vector<bool>& HarmonyIsSlow() { return Slow; }
	virtual DWORD MidiCommand(int status, int channel, int low, int high);
	DWORD* HarmonyStop();
	virtual bool IsRest() { return false; }
	vector<int>& GetHarmonyOcatave() { return Octave; }
	virtual bool IsHarmony() { return true; }
	int GetCount() { return NoteName.size(); }
};

