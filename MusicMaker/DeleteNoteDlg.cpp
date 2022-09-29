// DeleteNoteDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MusicMaker.h"
#include "afxdialogex.h"
#include "DeleteNoteDlg.h"


// DeleteNoteDlg 대화 상자

IMPLEMENT_DYNAMIC(DeleteNoteDlg, CDialogEx)

DeleteNoteDlg::DeleteNoteDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DELETE_NOTE, pParent)
{

}

DeleteNoteDlg::~DeleteNoteDlg()
{
}

void DeleteNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DELTE, DeleteList);
}


BEGIN_MESSAGE_MAP(DeleteNoteDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &DeleteNoteDlg::OnBnClickedOk)
	ON_LBN_SELCHANGE(IDC_LIST_DELTE, &DeleteNoteDlg::OnLbnSelchangeListDelte)
END_MESSAGE_MAP()


// DeleteNoteDlg 메시지 처리기


void DeleteNoteDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	::SendMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
	CDialogEx::OnOK();
}


void DeleteNoteDlg::OnLbnSelchangeListDelte()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	index = DeleteList.GetCurSel();
}


BOOL DeleteNoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	int i = 0;
	for (auto a : ForDelete)
	{
		int j =a->GetNoteName();
		double k = a->GetTime();
		CString str;
		switch (j)
		{
		case 0:
			if (k == 0.25)
				str.Format(_T("%d번째 \t16분음표 도"), i + 1);
			else if(k == 0.5)
				str.Format(_T("%d번째 \t8분음표 도"), i + 1);
			else if (k == 1.0)
				str.Format(_T("%d번째 \t4분음표 도"), i + 1);
			else if (k == 2.0)
				str.Format(_T("%d번째 \t2분음표 도"), i + 1);
			else if (k == 3.0)
				str.Format(_T("%d번째 \t점 2분음표 도"), i + 1);
			else if (k == 4.0)
				str.Format(_T("%d번째 \t온음표 도"), i + 1);
			break;
		case 1:
			if (k == 0.25)
				str.Format(_T("%d번째 \t16분음표 레"), i + 1);
			else if (k == 0.5)
				str.Format(_T("%d번째 \t8분음표 레"), i + 1);
			else if (k == 1.0)
				str.Format(_T("%d번째 \t4분음표 레"), i + 1);
			else if (k == 2.0)
				str.Format(_T("%d번째 \t2분음표 레"), i + 1);
			else if (k == 3.0)
				str.Format(_T("%d번째 \t점 2분음표 레"), i + 1);
			else if (k == 4.0)
				str.Format(_T("%d번째 \t온음표 레"), i + 1);
			break;
		case 2:
			if (k == 0.25)
				str.Format(_T("%d번째 \t16분음표 미"), i + 1);
			else if (k == 0.5)
				str.Format(_T("%d번째 \t8분음표 미"), i + 1);
			else if (k == 1.0)
				str.Format(_T("%d번째 \t4분음표 미"), i + 1);
			else if (k == 2.0)
				str.Format(_T("%d번째 \t2분음표 미"), i + 1);
			else if (k == 3.0)
				str.Format(_T("%d번째 \t점 2분음표 미"), i + 1);
			else if (k == 4.0)
				str.Format(_T("%d번째 \t온음표 미"), i + 1);
			break;
		case 3:
			if (k == 0.25)
				str.Format(_T("%d번째 \t16분음표 파"), i + 1);
			else if (k == 0.5)
				str.Format(_T("%d번째 \t8분음표 파"), i + 1);
			else if (k == 1.0)
				str.Format(_T("%d번째 \t4분음표 파"), i + 1);
			else if (k == 2.0)
				str.Format(_T("%d번째 \t2분음표 파"), i + 1);
			else if (k == 3.0)
				str.Format(_T("%d번째 \t점 2분음표 파"), i + 1);
			else if (k == 4.0)
				str.Format(_T("%d번째 \t온음표 파"), i + 1);
			break;
		case 4:
			if (k == 0.25)
				str.Format(_T("%d번째 \t16분음표 솔"), i + 1);
			else if (k == 0.5)
				str.Format(_T("%d번째 \t8분음표 솔"), i + 1);
			else if (k == 1.0)
				str.Format(_T("%d번째 \t4분음표 솔"), i + 1);
			else if (k == 2.0)
				str.Format(_T("%d번째 \t2분음표 솔"), i + 1);
			else if (k == 3.0)
				str.Format(_T("%d번째 \t점 2분음표 솔"), i + 1);
			else if (k == 4.0)
				str.Format(_T("%d번째 \t온음표 솔"), i + 1);
			break;
		case 5:
			if (k == 0.25)
				str.Format(_T("%d번째 \t16분음표 라"), i + 1);
			else if (k == 0.5)
				str.Format(_T("%d번째 \t8분음표 라"), i + 1);
			else if (k == 1.0)
				str.Format(_T("%d번째 \t4분음표 라"), i + 1);
			else if (k == 2.0)
				str.Format(_T("%d번째 \t2분음표 라"), i + 1);
			else if (k == 3.0)
				str.Format(_T("%d번째 \t점 2분음표 라"), i + 1);
			else if (k == 4.0)
				str.Format(_T("%d번째 \t온음표 라"), i + 1);
			break;
		case 6:
			if (k == 0.25)
				str.Format(_T("%d번째 \t16분음표 시"), i + 1);
			else if (k == 0.5)
				str.Format(_T("%d번째 \t8분음표 시"), i + 1);
			else if (k == 1.0)
				str.Format(_T("%d번째 \t4분음표 시"), i + 1);
			else if (k == 2.0)
				str.Format(_T("%d번째 \t2분음표 시"), i + 1);
			else if (k == 3.0)
				str.Format(_T("%d번째 \t점 2분음표 시"), i + 1);
			else if (k == 4.0)
				str.Format(_T("%d번째 \t온음표 시"), i + 1);
			break;
		default:
			AfxMessageBox(_T("음 목록 초기화중 실패"));
			break;
		}
		if (a->IsRest())
			str.Format(_T("%d번째 \t쉼표"), i + 1);
		else if (a->IsHarmony())
			str.Format(_T("%d번째 \t화음"), i + 1);
		DeleteList.InsertString(i, str);
		i++;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
