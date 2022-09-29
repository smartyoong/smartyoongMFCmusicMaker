#pragma once
#include "afxdialogex.h"


// InsertNote 대화 상자

class InsertNote : public CDialogEx
{
	DECLARE_DYNAMIC(InsertNote)

public:
	InsertNote(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~InsertNote();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INSERTNOTE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	enum NoteRythm {R16,R8,R4,R2,RD2,R1};
	enum NoteNameKind {DO,RAE,MI,PA,SOL,LA,SI};
	BOOL IsSharp = FALSE;
	BOOL isSlowNote = FALSE;
	int OctaveStr = 0; // 에디트 컨트롤에 보여주기 위한값
	CListBox RhythmNoteList;
	CSpinButtonCtrl OcataveSpin;
	CListBox NoteNameList;
	int NoteKind = DO;
	int NoteRythmKind = R4;
	int Ocatave = 0;
public:
	afx_msg void OnLbnSelchangeListMusicnote();
	afx_msg void OnBnClickedButtonMake();
	double GetNoteRythm();
	bool Sharp();
	bool SlowNote();
	afx_msg void OnLbnSelchangeListNotename();
	virtual BOOL OnInitDialog();
	int GetNoteName();
	int GetOctavePower();
	afx_msg void OnBnClickedCheckSharp();
	afx_msg void OnBnClickedCheckSlownote();
	afx_msg void OnDeltaposSpinOctave(NMHDR* pNMHDR, LRESULT* pResult);
	void SetOctavwe() { Ocatave = 0; }
};
