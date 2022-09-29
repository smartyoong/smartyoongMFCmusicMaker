#include "pch.h"
#include "SingHarmony.h"

void SingHarmony::Wait()
{
	if (Slow[0])
		Sleep(SingTime * 2000);
	else
		Sleep(SingTime * 1000);
}

DWORD SingHarmony::MidiCommand(int status, int channel, int low, int high)
{
	DWORD dw = (status | channel | (high << 16) | (low << 8));
	return dw;
}

DWORD* SingHarmony::PlayHarmony()
{
	int i = NoteName.size();
	dp = new DWORD[i];
	for (int j = 0; j < i; ++j)
	{
		int p = NoteName[j];
		int o = Octave[j];
		bool s = Sharp[j];
		switch (p)
		{
		case 0:
			if (s)
				dp[j] = MidiCommand(0x90, 0, 61 + (o * 12), 127);
			else
				dp[j] = MidiCommand(0x90, 0, 60 + (o * 12), 127);
		case 1:
			if (s)
				dp[j] = MidiCommand(0x90, 0, 63 + (o * 12), 127);
			else
				dp[j] = MidiCommand(0x90, 0, 62 + (o * 12), 127);
			break;
		case 2:
			if (s)
				dp[j] = MidiCommand(0x90, 0, 65 + (o * 12), 127);
			else
				dp[j] = MidiCommand(0x90, 0, 64 + (o * 12), 127);
			break;
		case 3:
			if (s)
				dp[j] = MidiCommand(0x90, 0, 66 + (o * 12), 127);
			else
				dp[j] = MidiCommand(0x90, 0, 65 + (o * 12), 127);
			break;
		case 4:
			if (s)
				dp[j] = MidiCommand(0x90, 0, 68 + (o * 12), 127);
			else
				dp[j] = MidiCommand(0x90, 0, 67 + (o * 12), 127);
			break;
		case 5:
			if (s)
				dp[j] = MidiCommand(0x90, 0, 70 + (o * 12), 127);
			else
				dp[j] = MidiCommand(0x90, 0, 69 + (o * 12), 127);
			break;
		case 6:
			if (s)
				dp[j] = MidiCommand(0x90, 0, 72 + (o * 12), 127);
			else
				dp[j] = MidiCommand(0x90, 0, 71 + (o * 12), 127);
			break;
		default:
			AfxMessageBox(_T("재생에러 (재생 에러)"));
			break;
		}
	}
	return dp;
}

DWORD* SingHarmony::HarmonyStop()
{
	int i = NoteName.size();
	ds = new DWORD[i];
	for (int j = 0; j < i; ++j)
	{
		int p = NoteName[j];
		int o = Octave[j];
		bool s = Sharp[j];
		switch (p)
		{
		case 0:
			if (s)
				ds[j] = MidiCommand(0x80, 0, 61 + (o * 12), 127);
			else
				ds[j] = MidiCommand(0x80, 0, 60 + (o * 12), 127);
		case 1:
			if (s)
				ds[j] = MidiCommand(0x80, 0, 63 + (o * 12), 127);
			else
				ds[j] = MidiCommand(0x80, 0, 62 + (o * 12), 127);
			break;
		case 2:
			if (s)
				ds[j] = MidiCommand(0x80, 0, 65 + (o * 12), 127);
			else
				ds[j] = MidiCommand(0x80, 0, 64 + (o * 12), 127);
			break;
		case 3:
			if (s)
				ds[j] = MidiCommand(0x80, 0, 66 + (o * 12), 127);
			else
				ds[j] = MidiCommand(0x80, 0, 65 + (o * 12), 127);
			break;
		case 4:
			if (s)
				ds[j] = MidiCommand(0x80, 0, 68 + (o * 12), 127);
			else
				ds[j] = MidiCommand(0x80, 0, 67 + (o * 12), 127);
			break;
		case 5:
			if (s)
				ds[j] = MidiCommand(0x80, 0, 70 + (o * 12), 127);
			else
				ds[j] = MidiCommand(0x80, 0, 69 + (o * 12), 127);
			break;
		case 6:
			if (s)
				ds[j] = MidiCommand(0x80, 0, 72 + (o * 12), 127);
			else
				ds[j] = MidiCommand(0x80, 0, 71 + (o * 12), 127);
			break;
		default:
			AfxMessageBox(_T("재생에러 (재생 에러)"));
			break;
		}
	}
	return ds;
}