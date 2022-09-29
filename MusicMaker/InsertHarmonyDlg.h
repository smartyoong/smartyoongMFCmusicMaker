#pragma once
#include "afxdialogex.h"
#include <vector>

// InsertHarmonyDlg 대화 상자

class InsertHarmonyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InsertHarmonyDlg)

public:
	InsertHarmonyDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~InsertHarmonyDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INSERT_HARMONY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CListBox ListRhythm;
	CListBox ListNoteName;
	int OctavePower = 0;
	CSpinButtonCtrl SpinOctave;
	BOOL Sharp;
	BOOL Slow;
	bool IsSharp = false;
	bool IsSlow = false;
	CListBox ListHarmony;
	int RhythmSelect = 0;
	int NoteSelect = 0;
	bool IsRhythmSelect = false;
	int Harmonyindex = 0;
public:
	std::vector<int> NoteList;
	std::vector<BOOL> SharpList;
	std::vector<BOOL> SlowList;
	std::vector<int> OctaveList;
	afx_msg void OnLbnSelchangeListRhythm();
	afx_msg void OnLbnSelchangeListNotename();
	afx_msg void OnDeltaposSpinOctave(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedCheckSharp();
	afx_msg void OnBnClickedCheckSlow();
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedOk();
	int GetRhythm();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonRhythmok();
};
