#pragma once
#include "afxdialogex.h"
#include "SingNote.h"
#include <vector>


// DeleteNoteDlg 대화 상자

class DeleteNoteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteNoteDlg)

public:
	DeleteNoteDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~DeleteNoteDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELETE_NOTE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CListBox DeleteList;
	std::vector<SingNote*> ForDelete;
	int index = 0;
public:
	void SetArr(std::vector<SingNote*>& v) { ForDelete = v; }
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeListDelte();
	virtual BOOL OnInitDialog();
	int GetIndex() { return index; }
};
