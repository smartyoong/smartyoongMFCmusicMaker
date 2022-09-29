// InsertNote.cpp: 구현 파일
//

#include "pch.h"
#include "MusicMaker.h"
#include "afxdialogex.h"
#include "InsertNote.h"


// InsertNote 대화 상자

IMPLEMENT_DYNAMIC(InsertNote, CDialogEx)

InsertNote::InsertNote(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INSERTNOTE, pParent)
	, OctaveStr(0)
	, IsSharp(FALSE)
	, isSlowNote(FALSE)
{
}

InsertNote::~InsertNote()
{
}

void InsertNote::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MUSICNOTE, RhythmNoteList);
	DDX_Control(pDX, IDC_LIST_NOTENAME, NoteNameList);
	DDX_Text(pDX, IDC_EDIT_OCTAVE, OctaveStr);
	DDX_Control(pDX, IDC_SPIN_OCTAVE, OcataveSpin);
	DDX_Check(pDX, IDC_CHECK_SHARP, IsSharp);
	DDX_Check(pDX, IDC_CHECK_SLOWNOTE, isSlowNote);
}


BEGIN_MESSAGE_MAP(InsertNote, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_MUSICNOTE, &InsertNote::OnLbnSelchangeListMusicnote)
	ON_BN_CLICKED(IDC_BUTTON_MAKE, &InsertNote::OnBnClickedButtonMake)
	ON_LBN_SELCHANGE(IDC_LIST_NOTENAME, &InsertNote::OnLbnSelchangeListNotename)
//	ON_WM_CREATE()
ON_BN_CLICKED(IDC_CHECK_SHARP, &InsertNote::OnBnClickedCheckSharp)
ON_BN_CLICKED(IDC_CHECK_SLOWNOTE, &InsertNote::OnBnClickedCheckSlownote)
ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_OCTAVE, &InsertNote::OnDeltaposSpinOctave)
END_MESSAGE_MAP()


// InsertNote 메시지 처리기


void InsertNote::OnLbnSelchangeListMusicnote()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = RhythmNoteList.GetCurSel();
	switch (index)
	{
	case 0:
		NoteRythmKind = R1;
		break;
	case 1:
		NoteRythmKind = RD2;
		break;
	case 2:
		NoteRythmKind = R2;
		break;
	case 3:
		NoteRythmKind = R4;
		break;
	case 4:
		NoteRythmKind = R8;
		break;
	case 5:
		NoteRythmKind = R16;
		break;
	default:
		AfxMessageBox(_T("음표 설정 실패"));
		break;
	}
	
}


void InsertNote::OnBnClickedButtonMake()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(25);
	::SendMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
}

double InsertNote::GetNoteRythm()
{
	if (NoteRythmKind == R4)
		return 1.0;
	else if (NoteRythmKind == R16)
		return 0.25;
	else if (NoteRythmKind == R8)
		return 0.5;
	else if (NoteRythmKind == R2)
		return 2.0;
	else if (NoteRythmKind == RD2)
		return 3.0;
	else if (NoteRythmKind == R1)
		return 4.0;
	else
	{
		AfxMessageBox(_T("음표 박자 선택 과정 오류발생"));
		return -1;
	}
}

void InsertNote::OnLbnSelchangeListNotename()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = NoteNameList.GetCurSel();
	switch (index)
	{
	case 0:
		NoteKind = DO;
		break;
	case 1:
		NoteKind = RAE;
		break;
	case 2:
		NoteKind = MI;
		break;
	case 3:
		NoteKind = PA;
		break;
	case 4:
		NoteKind = SOL;
		break;
	case 5:
		NoteKind = LA;
		break;
	case 6:
		NoteKind = SI;
		break;
	default:
		AfxMessageBox(_T("계이름 설정 실패"));
		break;
	}
}



BOOL InsertNote::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	OcataveSpin.SetRange(-1, 1);
	RhythmNoteList.InsertString(0, _T("온 음표"));
	RhythmNoteList.InsertString(1, _T("점 2분 음표"));
	RhythmNoteList.InsertString(2, _T("2분 음표"));
	RhythmNoteList.InsertString(3, _T("4분 음표"));
	RhythmNoteList.InsertString(4, _T("8분 음표"));
	RhythmNoteList.InsertString(5, _T("16분 음표"));
	NoteNameList.InsertString(0, _T("도"));
	NoteNameList.InsertString(1, _T("레"));
	NoteNameList.InsertString(2, _T("미"));
	NoteNameList.InsertString(3, _T("파"));
	NoteNameList.InsertString(4, _T("솔"));
	NoteNameList.InsertString(5, _T("라"));
	NoteNameList.InsertString(6, _T("시"));
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


int InsertNote::GetNoteName()
{
	// TODO: 여기에 구현 코드 추가.
	switch (NoteKind)
	{
	case DO:
		return 0;
		break;
	case RAE:
		return 1;
		break;
	case MI:
		return 2;
		break;
	case PA:
		return 3;
		break;
	case SOL:
		return 4;
		break;
	case LA:
		return 5;
		break;
	case SI:
		return 6;
		break;
	default:
		AfxMessageBox(_T("계이름 불러오기 실패"));
		return -1;
		break;
	}
}


int InsertNote::GetOctavePower()
{
	// TODO: 여기에 구현 코드 추가.
	return Ocatave;
}

bool InsertNote::Sharp()
{
	if (IsSharp == TRUE)
		return true;
	else
		return false;
}

bool InsertNote::SlowNote()
{
	if (isSlowNote == TRUE)
		return true;
	else
		return false;
}

void InsertNote::OnBnClickedCheckSharp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (IsSharp == FALSE)
		IsSharp = TRUE;
	else
		IsSharp = FALSE;
}


void InsertNote::OnBnClickedCheckSlownote()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (isSlowNote == FALSE)
		isSlowNote = TRUE;
	else
		isSlowNote = FALSE;
}


void InsertNote::OnDeltaposSpinOctave(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMUpDown->iDelta < 0)
	{
			Ocatave--;
			if (Ocatave < -1)
				Ocatave = -1;
	}
	else
	{
			Ocatave++;
			if (Ocatave > 1)
				Ocatave = 1;
	}
	UpdateData(FALSE);
	*pResult = 0;
}
