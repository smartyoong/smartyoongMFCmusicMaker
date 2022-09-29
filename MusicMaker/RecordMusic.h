#pragma once
#include "afxdialogex.h"
#include "MusicMakerView.h"
#include <fstream>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define MAX_QUEUE_SIZE 1440000

// RecordMusic 대화 상자
typedef struct BufferNode 
{ 
	int length;
	void* buffer;
};

class RecordMusic : public CDialogEx
{
	DECLARE_DYNAMIC(RecordMusic)

public:
	RecordMusic(CMusicMakerView* p, CWnd* pParent = nullptr);  // 표준 생성자입니다.
	virtual ~RecordMusic();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RECORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CMusicMakerView* vp = nullptr;
	bool IsRecord = false;
	int RecordMode = 3;
	WAVEFORMATEX WaveFormat;
	HWAVEIN WaveIn;
	WAVEHDR* Have;
	WAVEHDR* WaveSave;
	int RecordIndex = 0;
	BufferNode* bn; //복구용
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonSaverecord();
	afx_msg void OnBnClickedButtonStop();
	int ReturnMode() { return RecordMode; }
	virtual BOOL OnInitDialog();
	LRESULT WndProc(UINT um, WPARAM w, LPARAM l); // static으로 지정 필수 이거땜에 고생했습니다... 함수 포인터를 데이터 포인터로 변환하는 것은 정의되지 않는 동작입니다.
	void SaveWavFile(const char* fn, WAVEFORMATEX* wf, PWAVEHDR p); // wave형식에 맞게 저장하는 함수
};