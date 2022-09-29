// SelectInstronument.cpp: 구현 파일
//

#include "pch.h"
#include "MusicMaker.h"
#include "afxdialogex.h"
#include "SelectInstronument.h"


// SelectInstronument 대화 상자

IMPLEMENT_DYNAMIC(SelectInstronument, CDialogEx)

SelectInstronument::SelectInstronument(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SELECT_INSTROMENT, pParent)
{

}

SelectInstronument::~SelectInstronument()
{
}

void SelectInstronument::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_INSTRONUMENT, InstronumentList);
}


BEGIN_MESSAGE_MAP(SelectInstronument, CDialogEx)
	ON_BN_CLICKED(IDOK, &SelectInstronument::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST_INSTRONUMENT, &SelectInstronument::OnLbnSelchangeListInstronument)
END_MESSAGE_MAP()


// SelectInstronument 메시지 처리기


BOOL SelectInstronument::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	InstronumentList.InsertString(0, _T("피아노"));
	InstronumentList.InsertString(1, _T("일렉 기타"));
	InstronumentList.InsertString(2, _T("일렉트릭 피아노"));
	InstronumentList.InsertString(3, _T("어쿠아스틱 기타"));
	InstronumentList.InsertString(4, _T("베이스 기타"));
	InstronumentList.InsertString(5, _T("바이올린"));
	InstronumentList.InsertString(6, _T("트럼펫"));
	InstronumentList.InsertString(7, _T("섹소폰"));
	InstronumentList.InsertString(8, _T("플룻"));
	InstronumentList.InsertString(9, _T("현악기 앙상블"));
	InstronumentList.InsertString(10, _T("합창"));
	InstronumentList.InsertString(11, _T("오카리나"));
	InstronumentList.InsertString(12, _T("악기 패드"));
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void SelectInstronument::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (InstronumentList.GetCurSel() == -1)
	{
		AfxMessageBox(_T("악기를 선택해주세요"));
	}
	else
	{
		EndDialog(IDOK);
		::SendMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
	}
	CDialogEx::OnOK();
}


int SelectInstronument::GetinstronumentNo()
{
	// TODO: 여기에 구현 코드 추가.
	return InstronumentNumber;
}


void SelectInstronument::OnLbnSelchangeListInstronument()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	InstronumentNumber = InstronumentList.GetCurSel();
}
