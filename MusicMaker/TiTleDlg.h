#pragma once
#include "afxdialogex.h"


// TiTleDlg 대화 상자

class TiTleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(TiTleDlg)

public:
	TiTleDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~TiTleDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TITLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString TitleStr;
	CFont font;
	afx_msg void OnClickedButtonTitleok();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
