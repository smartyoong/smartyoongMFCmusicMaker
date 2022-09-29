#include "pch.h"
#include "SingRest.h"

DWORD SingRest::Sing()
{
	DWORD dw = MidiCommand(0x80, 0, 127, 0);
	return dw;
}

DWORD SingRest::MidiCommand(int status, int channel, int low, int high)
{
	DWORD dw = (status | channel | (high << 16) | (low << 8));
	return dw;
}

DWORD SingRest::Stop()
{
	DWORD dw = MidiCommand(0x80, 0, 127, 0);
	return dw;
}

void SingRest::Wait()
{
	Sleep(time * 1000);
}