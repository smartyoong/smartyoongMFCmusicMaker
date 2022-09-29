#pragma once
#include <mmsystem.h>
#pragma comment(lib, "WinMM.lib")
enum Instroment { PIANO, GUITAR, ELECTRICPIANO,ACGUITAR,BASSGUITAR,VIOLIN,TRUMPET,SAX,FLUTE ,ENSENBLE,VOICE,OCARINA,PAD};
class SingNote
{
private:
	int InstromentMode = PIANO; //악기
	double Time = 0; // 음표 개인당 시간
	int Octave = 0; // 옥타브 여부
	int NoteName = 0; // 계이름
	bool Slow = false; // 기타 부호
	bool Sharp = false;
public:
	SingNote() = default;
	SingNote(int i, double t, int o, int n, bool sl, bool sh) : InstromentMode(i), Time(t), Octave(o), NoteName(n), Slow(sl), Sharp(sh) { }
	~SingNote();
	virtual DWORD Sing();
	virtual void Wait();
	virtual int GetNoteName() { return NoteName; }
	virtual double GetTime() { return Time; }
	virtual bool IsSharp() { return Sharp; }
	virtual bool IsSlow() { return Slow; }
	virtual DWORD MidiCommand(int status, int channel, int low, int high);
	virtual DWORD Stop();
	virtual bool IsRest() { return false; }
	virtual int GetOcatave() { return Octave; }
	virtual bool IsHarmony() { return false; }
	DWORD GetInstrument();
	bool IsNotPiano() { return InstromentMode != PIANO; }
	void Setinstrument(int x) { InstromentMode = x; }
};

