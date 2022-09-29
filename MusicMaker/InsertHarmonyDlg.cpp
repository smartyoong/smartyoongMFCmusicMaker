// InsertHarmonyDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MusicMaker.h"
#include "afxdialogex.h"
#include "InsertHarmonyDlg.h"


// InsertHarmonyDlg 대화 상자

IMPLEMENT_DYNAMIC(InsertHarmonyDlg, CDialogEx)

InsertHarmonyDlg::InsertHarmonyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INSERT_HARMONY, pParent)
	, OctavePower(0)
	, Sharp(FALSE)
	, Slow(FALSE)
{

}

InsertHarmonyDlg::~InsertHarmonyDlg()
{
}

void InsertHarmonyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RHYTHM, ListRhythm);
	DDX_Control(pDX, IDC_LIST_NOTENAME, ListNoteName);
	DDX_Text(pDX, IDC_EDIT_OCTAVE, OctavePower);
	DDX_Control(pDX, IDC_SPIN_OCTAVE, SpinOctave);
	DDX_Check(pDX, IDC_CHECK_SHARP, Sharp);
	DDX_Check(pDX, IDC_CHECK_SLOW, Slow);
	DDX_Control(pDX, IDC_LIST_HARMONY, ListHarmony);
}


BEGIN_MESSAGE_MAP(InsertHarmonyDlg, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_RHYTHM, &InsertHarmonyDlg::OnLbnSelchangeListRhythm)
	ON_LBN_SELCHANGE(IDC_LIST_NOTENAME, &InsertHarmonyDlg::OnLbnSelchangeListNotename)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OCTAVE, &InsertHarmonyDlg::OnDeltaposSpinOctave)
	ON_BN_CLICKED(IDC_CHECK_SHARP, &InsertHarmonyDlg::OnBnClickedCheckSharp)
	ON_BN_CLICKED(IDC_CHECK_SLOW, &InsertHarmonyDlg::OnBnClickedCheckSlow)
	ON_BN_CLICKED(IDC_BUTTON_INSERT, &InsertHarmonyDlg::OnBnClickedButtonInsert)
	ON_BN_CLICKED(IDOK, &InsertHarmonyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_RHYTHMOK, &InsertHarmonyDlg::OnBnClickedButtonRhythmok)
END_MESSAGE_MAP()


// InsertHarmonyDlg 메시지 처리기


void InsertHarmonyDlg::OnLbnSelchangeListRhythm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	RhythmSelect = ListRhythm.GetCurSel();
}


void InsertHarmonyDlg::OnLbnSelchangeListNotename()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NoteSelect = ListNoteName.GetCurSel();
}


void InsertHarmonyDlg::OnDeltaposSpinOctave(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMUpDown->iDelta < 0)
	{
		OctavePower--;
		if (OctavePower < -1)
			OctavePower = -1;
	}
	else
	{
		OctavePower++;
		if (OctavePower > 1)
			OctavePower = 1;
	}
	UpdateData(FALSE);
	IsSlow = false;
	IsSharp = false;
	*pResult = 0;
}


void InsertHarmonyDlg::OnBnClickedCheckSharp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	IsSharp = !IsSharp;
}


void InsertHarmonyDlg::OnBnClickedCheckSlow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	IsSlow = !IsSlow;
}


void InsertHarmonyDlg::OnBnClickedButtonInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IsRhythmSelect == false)
	{
		AfxMessageBox(_T("박자를 선택후 확정해 주세요."));
	}
	else
	{
		NoteList.push_back(NoteSelect);
		SharpList.push_back(IsSharp);
		SlowList.push_back(IsSlow);
		OctaveList.push_back(OctavePower);
		CString str;
		switch (NoteSelect)
		{
		case 0:
			str += _T("도 ");
			break;
		case 1:
			str += _T("레 ");
			break;
		case 2:
			str += _T("미 ");
			break;
		case 3:
			str += _T("파");
			break;
		case 4:
			str += _T("솔 ");
			break;
		case 5:
			str += _T("라 ");
			break;
		case 6:
			str += _T("시 ");
			break;
		default:
			AfxMessageBox(_T("계이름 생성중에 오류 발생"));
			break;
		}
		switch (RhythmSelect)
		{
		case 0:
			str += _T("온 음표");
			break;
		case 1:
			str += _T("점 2분음표");
			break;
		case 2:
			str += _T("2분 음푠");
			break;
		case 3:
			str += _T("4분 음표");
			break;
		case 4:
			str += _T("8분 음표");
			break;
		case 5:
			str += (_T("16분 음표"));
			break;
		default:
			AfxMessageBox(_T("박자 생성중에 오류 발생"));
			break;
		}
		if (OctavePower == 0)
			str += _T(" 기본 음자리표");
		else if (OctavePower < 0)
			str += _T(" 낮은 음자리표");
		else if (OctavePower > 0)
			str += _T(" 높은 음자리표");
		else
			AfxMessageBox(_T("옥타브 생성중 오류 발생"));
		if (IsSlow)
			str += _T(" 늘임표");
		if (IsSharp)
			str += _T(" 샾");
		ListHarmony.InsertString(Harmonyindex, str);
		Harmonyindex++;
	}
}


void InsertHarmonyDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
	::SendMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
}


int InsertHarmonyDlg::GetRhythm()
{
	// TODO: 여기에 구현 코드 추가.
	return RhythmSelect;
}


BOOL InsertHarmonyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	ListRhythm.InsertString(0, _T("온 음표"));
	ListRhythm.InsertString(1, _T("점 2분 음표"));
	ListRhythm.InsertString(2, _T("2분 음표"));
	ListRhythm.InsertString(3, _T("4분 음표"));
	ListRhythm.InsertString(4, _T("8분 음표"));
	ListRhythm.InsertString(5, _T("16분 음표"));
	ListNoteName.InsertString(0, _T("도"));
	ListNoteName.InsertString(1, _T("레"));
	ListNoteName.InsertString(2, _T("미"));
	ListNoteName.InsertString(3, _T("파"));
	ListNoteName.InsertString(4, _T("솔"));
	ListNoteName.InsertString(5, _T("라"));
	ListNoteName.InsertString(6, _T("시"));
	SpinOctave.SetRange(-1, 1);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void InsertHarmonyDlg::OnBnClickedButtonRhythmok()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IsRhythmSelect)
	{
		AfxMessageBox(_T("이미 음표를 선택하셨습니다."));
	}
	else
	{
		IsRhythmSelect = true;
		ListRhythm.EnableWindow(FALSE);
	}
}
