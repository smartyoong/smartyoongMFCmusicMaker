#include "pch.h"
#include "SingNote.h"

DWORD SingNote::Sing()
{
	DWORD dw;
	switch (NoteName)
	{
	case 0:
		if (Sharp)
			dw = MidiCommand(0x90, 0, 61 + (Octave * 12), 127);
		else
			dw =MidiCommand(0x90, 0, 60+(Octave*12), 127);
		break;
	case 1 :
		if (Sharp)
			dw = MidiCommand(0x90, 0, 63 + (Octave * 12), 127);
		else
			dw = MidiCommand(0x90, 0, 62 + (Octave * 12), 127);
		break;
	case 2:
		if (Sharp)
			dw = MidiCommand(0x90, 0, 65 + (Octave * 12), 127);
		else
			dw = MidiCommand( 0x90, 0, 64 + (Octave * 12), 127);
		break;
	case 3:
		if (Sharp)
			dw = MidiCommand(0x90, 0, 66 + (Octave * 12), 127);
		else
			dw = MidiCommand(0x90, 0, 65 + (Octave * 12), 127);
		break;
	case 4:
		if (Sharp)
			dw = MidiCommand(0x90, 0, 68 + (Octave * 12), 127);
		else
			dw = MidiCommand(0x90, 0, 67 + (Octave * 12), 127);
		break;
	case 5:
		if (Sharp)
			dw = MidiCommand(0x90, 0, 70 + (Octave * 12), 127);
		else
			dw = MidiCommand(0x90, 0, 69 + (Octave * 12), 127);
		break;
	case 6:
		if (Sharp)
			dw = MidiCommand(0x90, 0, 72 + (Octave * 12), 127);
		else
			dw = MidiCommand(0x90, 0, 71 + (Octave * 12), 127);
		break;
	default:
		AfxMessageBox(_T("재생에러 (재생 에러)"));
		break;
	}
	return dw;
}

void SingNote::Wait() 
{
	if (Slow)
		Sleep(Time * 2000);
	else
		Sleep(Time * 1000);
}

SingNote::~SingNote()
{
}

DWORD SingNote::MidiCommand(int status, int channel, int low, int high)
{
	DWORD dw = (status | channel | (high << 16) | (low << 8));
	return dw;
}

DWORD SingNote::Stop()
{
	DWORD dw;
	switch (NoteName)
	{
	case 0:
		if (Sharp)
			dw = MidiCommand(0x80, 0, 61 + (Octave * 12), 127);
		else
			dw = MidiCommand(0x80, 0, 60 + (Octave * 12), 127);
		break;
	case 1:
		if (Sharp)
			dw = MidiCommand(0x80, 0, 63 + (Octave * 12), 127);
		else
			dw = MidiCommand(0x80, 0, 62 + (Octave * 12), 127);
		break;
	case 2:
		if (Sharp)
			dw = MidiCommand(0x80, 0, 65 + (Octave * 12), 127);
		else
			dw = MidiCommand(0x80, 0, 64 + (Octave * 12), 127);
		break;
	case 3:
		if (Sharp)
			dw = MidiCommand(0x80, 0, 66 + (Octave * 12), 127);
		else
			dw = MidiCommand(0x80, 0, 65 + (Octave * 12), 127);
		break;
	case 4:
		if (Sharp)
			dw = MidiCommand(0x80, 0, 68 + (Octave * 12), 127);
		else
			dw = MidiCommand(0x80, 0, 67 + (Octave * 12), 127);
		break;
	case 5:
		if (Sharp)
			dw = MidiCommand(0x80, 0, 70 + (Octave * 12), 127);
		else
			dw = MidiCommand(0x80, 0, 69 + (Octave * 12), 127);
		break;
	case 6:
		if (Sharp)
			dw = MidiCommand(0x80, 0, 72 + (Octave * 12), 127);
		else
			dw = MidiCommand(0x80, 0, 71 + (Octave * 12), 127);
		break;
	default:
		AfxMessageBox(_T("재생에러 (재생 에러)"));
		break;
	}
	return dw;
}

DWORD SingNote::GetInstrument()
{
	DWORD dw;
	if (InstromentMode == PIANO)
		AfxMessageBox(_T("악기선택 연주중 오류"));
	else if (InstromentMode == GUITAR)
	{
		dw = MidiCommand(0xC0, 0, 30, 0);
	}
	else if (InstromentMode == ELECTRICPIANO)
	{
		dw = MidiCommand(0xC0, 0, 4, 0);
	}
	else if (InstromentMode == ACGUITAR)
	{
		dw = MidiCommand(0xC0, 0, 25, 0);
	}
	else if (InstromentMode == BASSGUITAR)
	{
		dw = MidiCommand(0xC0, 0, 33, 0);
	}
	else if (InstromentMode == VIOLIN)
	{
		dw = MidiCommand(0xC0, 0, 40, 0);
	}
	else if (InstromentMode == TRUMPET)
	{
		dw = MidiCommand(0xC0, 0, 56, 0);
	}
	else if (InstromentMode == SAX)
	{
		dw = MidiCommand(0xC0, 0, 64, 0);
	}
	else if (InstromentMode == FLUTE)
	{
		dw = MidiCommand(0xC0, 0, 73, 0);
	}
	else if (InstromentMode == ENSENBLE)
	{
		dw = MidiCommand(0xC0, 0, 48, 0);
	}
	else if (InstromentMode == VOICE)
	{
		dw = MidiCommand(0xC0, 0, 52, 0);
	}
	else if (InstromentMode == OCARINA)
	{
		dw = MidiCommand(0xC0, 0, 79, 0);
	}
	else if (InstromentMode == PAD)
	{
		dw = MidiCommand(0xC0, 0, 88, 0);
	}
	return dw;
}