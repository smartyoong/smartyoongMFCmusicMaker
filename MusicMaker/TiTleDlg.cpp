// TiTleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MusicMaker.h"
#include "afxdialogex.h"
#include "TiTleDlg.h"


// TiTleDlg 대화 상자

IMPLEMENT_DYNAMIC(TiTleDlg, CDialogEx)

TiTleDlg::TiTleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TITLE, pParent)
	, TitleStr(_T(""))
{

}

TiTleDlg::~TiTleDlg()
{
}

void TiTleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TITLE, TitleStr);
}


BEGIN_MESSAGE_MAP(TiTleDlg, CDialogEx)
	ON_BN_CLICKED(ID_BUTTON_TITLEOK, &TiTleDlg::OnClickedButtonTitleok)
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// TiTleDlg 메시지 처리기


void TiTleDlg::OnClickedButtonTitleok()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	if (TitleStr.IsEmpty())
	{
		GetDlgItem(IDC_EDIT_TITLE)->SetFocus();
		AfxMessageBox(_T("제목을 입력해주세요."), IDOK);
	}
	else
	{
		::SendMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
	}
}


int TiTleDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	return 0;
}


void TiTleDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	return;
}


BOOL TiTleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	GetDlgItem(IDC_EDIT_TITLE)->SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void TiTleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nID == SC_CLOSE)
		return;
	CDialogEx::OnSysCommand(nID, lParam);
}
