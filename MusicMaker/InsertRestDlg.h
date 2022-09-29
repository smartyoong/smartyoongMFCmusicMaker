#pragma once
#include "afxdialogex.h"


// InsertRestDlg 대화 상자

class InsertRestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InsertRestDlg)

public:
	InsertRestDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~InsertRestDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	int RestType = 0;
public:
	CListBox RestList;
	afx_msg void OnBnClickedOk();
	afx_msg void OnSelchangeListRest();
	int GetRestType() { return RestType; }
	virtual BOOL OnInitDialog();
};
