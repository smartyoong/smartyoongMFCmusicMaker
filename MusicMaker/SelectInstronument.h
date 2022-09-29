#pragma once
#include "afxdialogex.h"


// SelectInstronument 대화 상자

class SelectInstronument : public CDialogEx
{
	DECLARE_DYNAMIC(SelectInstronument)

public:
	SelectInstronument(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SelectInstronument();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SELECT_INSTROMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox InstronumentList;
	afx_msg void OnBnClickedOk();
	int InstronumentNumber = 0;
	int GetinstronumentNo();
	afx_msg void OnLbnSelchangeListInstronument();
};
