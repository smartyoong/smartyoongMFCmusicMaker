
// MusicMakerView.h: CMusicMakerView 클래스의 인터페이스
//
#include "MusicMakerDoc.h"
#include "TiTleDlg.h"
#include "InsertNote.h"
#include "SingNote.h"
#include "Note.h"
#pragma once


class CMusicMakerView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMusicMakerView() noexcept;
	DECLARE_DYNCREATE(CMusicMakerView)

// 특성입니다.
public:
	CMusicMakerDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMusicMakerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	enum Rythmmode { R4by4, R3by4, R6by8 };
	enum RythmValMax {RM4by4 = 4, RM3by4 = 3, RM6by8 = 3};
	/*타이틀을 위한 변수*/
	CFont vfont;
	CFont* oldfont,*titlefont;
	TiTleDlg td;
	/*마디당 최대 박자수 지정하기 위한 변수*/
	double MaxRythmVal = RM4by4;
	bool Is4by4 = true;
	bool Is3by4 = false;
	bool Is6by8 = false;
	/*이 아래는 음표 설정을 위한 변수들*/
	InsertNote indlg;
	bool IsSharpOn = false;
	bool IsSlowOn = false;
	double SingleNoteTime = 0;
	int SingleNoteName = 0;
	int Oct = 0;
	/*사이즈 맞추기 위한 변수*/
	const int SXSTART = 250;
	const int SYSTART = 310;
	const int SXFIRSTGAP = 410;
	const int SYNOTEHEIGHT = 100;
	const int SXGAP = 40;
	const int SXWIDTH = 560;
	const int SYGAP = 125;
	/*악기 변수*/
	int instrument = PIANO;  /*SingleNote 클래스의 enum참조*/
	CString InstruStr = _T("현재 악기는 : 피아노");
	/*연주를 하기 위한 변수*/
	Note* np;
	/*스레드로 연주하기 위한 데이터*/
	std::vector<SingNote*> temp;
	CWinThread* pThread;
	/*화음 전용 변수*/
	double HarmonyNoteTime = 0;
	std::vector<int> ForHarmonyNote;
	std::vector<int> ForHarmonyOctave;
	std::vector<bool> ForHarmonySharp;
	std::vector<bool>ForHarmomonySlow;
	/*재생바 변수*/
	bool IsPlay = false;
	int PlayX = 0;
	int PlayY = 0;
	/*녹음 변수*/
	CString path;
	bool IsRecordNow = false;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CString TitleName;
	void DrawTitle(CString str, CDC* dc);
	afx_msg void OnModifyTitle();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void PanePos(CPoint point);
	int GetRythm();
	afx_msg void On4by4();
	afx_msg void On3by4();
	afx_msg void On6by4();
	afx_msg void OnUpdate3by4(CCmdUI* pCmdUI);
	afx_msg void OnUpdate4by4(CCmdUI* pCmdUI);
	afx_msg void OnUpdate6by4(CCmdUI* pCmdUI);
	void DrawRythm(CImage& im);
	void DrawSeperateLine(CDC& dc);
	afx_msg void OnNoteSave();
	afx_msg void OnInsertNote();
	afx_msg void OnSelectInstronumentMenu();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPlay();
	afx_msg void OnInsertRest();
	afx_msg void OnDeleteNote();
	afx_msg void OnInsertHarmony();
	afx_msg void OnNotereset();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRecord();
	Note* GetNoteP() { return np; }
	std::vector<SingNote*>* GetTempCon() { return &temp; }
	afx_msg void OnStoprecord();
	afx_msg void OnUpdateStoprecord(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecord(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // MusicMakerView.cpp의 디버그 버전
inline CMusicMakerDoc* CMusicMakerView::GetDocument() const
   { return reinterpret_cast<CMusicMakerDoc*>(m_pDocument); }
#endif

