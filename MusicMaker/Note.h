#pragma once
#include <vector>
#include "SingNote.h"
#include "SingHarmony.h"
class Note
{
private :
	const int DoPosition = 14; //마디 y축 스타트 기준 그대로 즉, SYSTART 빼는값 불필요.
	const int RaePosition = 7;//SYSTART-10퍼
	const int MiPosition = 0; // -15퍼
	const int PaPosition = -8; // SYSTART -20퍼
	const int SolPosition = -18; // -25
	const int RaPosition = -28; // -30
	 int SiPosition = 15; // -35
	double MaxTime = 0;
	double CurTime = 0;
	int NoteXSize = 0;
	int NoteYSize = 0;
	int NoteXStartPoint = 0;
	int NoteYStartPoint = 0;
	int NoteCount = 0;
public :
	std::vector<SingNote*> SNarr;
	Note() = default;
	void SetNote(int M, int XS, int YS, int XSP, int YSP)
	{
		MaxTime = M;
		NoteXSize = XS;
		NoteYSize = YS;
		NoteXStartPoint = XSP;
		NoteYStartPoint = YSP;
	 }
	void AddSingleNote(SingNote* sn);
	void SetMaxTime(int n) { MaxTime = n; }
	void Draw(CDC& t);
	void Delete(int n) {CurTime -= SNarr[n]->GetTime(), SNarr.erase(SNarr.begin()+n); NoteCount--; }
	bool FindInsert() { return MaxTime > CurTime; }
	bool CanInsert(int x) { return MaxTime >= CurTime + x; }
	bool IsOn() { return NoteCount >= 1; }
	int GetCount() { return NoteCount; }
	void NoteClear() 
	{
		SNarr.clear();
		NoteCount = 0; 
		MaxTime = 0;
		CurTime = 0;
	}
	void DrawPlaying(CDC& memdc, CDC* dc);
};
static UINT NotePlay(LPVOID va)
{
	std::vector<SingNote*>* v = (std::vector<SingNote*>*)va;
	int c = v->size();
	HMIDIOUT hMidi;
	midiOutOpen(&hMidi, MIDIMAPPER, 0, 0, CALLBACK_NULL);
	DWORD dw;
	DWORD* hdp;
	DWORD* hds;
	if ((*v)[0]->IsNotPiano())
	{
		dw = (*v)[0]->GetInstrument();
		midiOutShortMsg(hMidi, dw);
	}
	for (int i = 0; i < c; ++i)
	{
		if ((*v)[i]->IsHarmony())
		{
			SingHarmony* sh = static_cast<SingHarmony*>((*v)[i]);
			hdp = sh->PlayHarmony();
			hds = sh->HarmonyStop();
			for (int y = 0; y < sh->GetCount(); ++y)
			{
				midiOutShortMsg(hMidi, hdp[y]);
			}
			sh->Wait();
			if (i < c - 1)
			{
				if ((*v)[i + 1]->IsHarmony())
				{
					SingHarmony* sp = static_cast<SingHarmony*>((*v)[i+1]);
					hdp = sp->PlayHarmony();
					hds = sp->HarmonyStop();
					for (int y = 0; y < sp->GetCount(); ++y)
					{
						midiOutShortMsg(hMidi, hdp[y]);
					}
				}
				else
				{
					dw = (*v)[i + 1]->Sing();
					midiOutShortMsg(hMidi, dw);
				}
			}
			for(int i=0; i < sh->GetCount(); ++i)
				midiOutShortMsg(hMidi, hds[i]);
		}
		else
		{
			dw = (*v)[i]->Sing();
			midiOutShortMsg(hMidi, dw);
			(*v)[i]->Wait();
			if (i < c - 1)
			{
				if ((*v)[i + 1]->IsHarmony())
				{
					SingHarmony* sp = static_cast<SingHarmony*>((*v)[i + 1]);
					hdp = sp->PlayHarmony();
					hds = sp->HarmonyStop();
					for (int y = 0; y < sp->GetCount(); ++y)
					{
						midiOutShortMsg(hMidi, hdp[y]);
					}
				}
				else
				{
					dw = (*v)[i + 1]->Sing();
					midiOutShortMsg(hMidi, dw);
				}
			}
			dw = (*v)[i]->Stop();
			midiOutShortMsg(hMidi, dw);
		}
	}
	midiOutReset(hMidi);
	midiOutClose(hMidi);
	return 0;
}

