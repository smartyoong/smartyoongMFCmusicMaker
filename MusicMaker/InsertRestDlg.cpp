// InsertRestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MusicMaker.h"
#include "afxdialogex.h"
#include "InsertRestDlg.h"


// InsertRestDlg 대화 상자

IMPLEMENT_DYNAMIC(InsertRestDlg, CDialogEx)

InsertRestDlg::InsertRestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_REST, pParent)
{

}

InsertRestDlg::~InsertRestDlg()
{
}

void InsertRestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REST, RestList);
}


BEGIN_MESSAGE_MAP(InsertRestDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &InsertRestDlg::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST_REST, &InsertRestDlg::OnSelchangeListRest)
END_MESSAGE_MAP()


// InsertRestDlg 메시지 처리기


void InsertRestDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
	::SendMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
}


void InsertRestDlg::OnSelchangeListRest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	RestType = RestList.GetCurSel();
}


BOOL InsertRestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	RestList.InsertString(0, _T("온쉼표"));
	RestList.InsertString(1, _T("점 2분 쉼표"));
	RestList.InsertString(2, _T("2분 쉼표"));
	RestList.InsertString(3, _T("4분 쉼표"));
	RestList.InsertString(4, _T("8분 쉼표"));
	RestList.InsertString(5, _T("16분 쉼표"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
