
// MusicMakerView.cpp: CMusicMakerView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MusicMaker.h"
#endif

#include "MusicMakerDoc.h"
#include "MusicMakerView.h"
#include "TiTleDlg.h"
#include "MainFrm.h"
#include "SelectInstronument.h"
#include <mmsystem.h>
#pragma comment(lib, "WinMM.lib")
#include <vector>
#include "InsertRestDlg.h"
#include "SingRest.h"
#include "DeleteNoteDlg.h"
#include "InsertHarmonyDlg.h"
#include "SingHarmony.h"
#include "RecordMusic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMusicMakerView

IMPLEMENT_DYNCREATE(CMusicMakerView, CView)

BEGIN_MESSAGE_MAP(CMusicMakerView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMusicMakerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_COMMAND(ID_MODIFY_TITLE, &CMusicMakerView::OnModifyTitle)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_4BY4, &CMusicMakerView::On4by4)
	ON_COMMAND(ID_3BY4, &CMusicMakerView::On3by4)
	ON_COMMAND(ID_6BY4, &CMusicMakerView::On6by4)
	ON_UPDATE_COMMAND_UI(ID_3BY4, &CMusicMakerView::OnUpdate3by4)
	ON_UPDATE_COMMAND_UI(ID_4BY4, &CMusicMakerView::OnUpdate4by4)
	ON_UPDATE_COMMAND_UI(ID_6BY4, &CMusicMakerView::OnUpdate6by4)
	ON_COMMAND(ID_NOTE_SAVE, &CMusicMakerView::OnNoteSave)
	ON_COMMAND(ID_INSERT_NOTE, &CMusicMakerView::OnInsertNote)
	ON_COMMAND(ID_SELECT_INSTRONUMENT_MENU, &CMusicMakerView::OnSelectInstronumentMenu)
	ON_WM_SIZE()
	ON_COMMAND(ID_PLAY, &CMusicMakerView::OnPlay)
	ON_COMMAND(ID_INSERT_REST, &CMusicMakerView::OnInsertRest)
	ON_COMMAND(ID_DELETE_NOTE, &CMusicMakerView::OnDeleteNote)
	ON_COMMAND(ID_INSERT_HARMONY, &CMusicMakerView::OnInsertHarmony)
	ON_COMMAND(ID_NOTERESET, &CMusicMakerView::OnNotereset)
	ON_WM_TIMER()
	ON_COMMAND(ID_RECORD, &CMusicMakerView::OnRecord)
	ON_COMMAND(ID_STOPRECORD, &CMusicMakerView::OnStoprecord)
	ON_UPDATE_COMMAND_UI(ID_STOPRECORD, &CMusicMakerView::OnUpdateStoprecord)
	ON_UPDATE_COMMAND_UI(ID_RECORD, &CMusicMakerView::OnUpdateRecord)
END_MESSAGE_MAP()

// CMusicMakerView 생성/소멸

CMusicMakerView::CMusicMakerView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CMusicMakerView::~CMusicMakerView()
{
}

BOOL CMusicMakerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMusicMakerView 그리기

void CMusicMakerView::OnDraw(CDC* pDC)
{
	CMusicMakerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CImage image, image2;
	CRect rect;
	GetClientRect(&rect);
	image.Load(L"image/RealMusicNote.jpg");
	this->DrawRythm(image2);
	CDC& memdc = *CDC::FromHandle(image.GetDC());
	CDC& memdc2 = *CDC::FromHandle(image2.GetDC());
	for (int i=0, j =0,co =0; co<5; i += 220, j += 5,co++)
	{
		memdc2.SetBkMode(TRANSPARENT);
		memdc.StretchBlt(170, 300 + i + j, 50, 100, &memdc2, 0, 0, image2.GetWidth(), image2.GetHeight(), SRCAND);
	}

	for (int i = 0; i < 20; ++i)
	{
		if(np[i].IsOn())
			np[i].Draw(memdc);
	}
	memdc.TextOutW(0, 0, InstruStr);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, image.GetWidth(), image.GetHeight(), SRCCOPY);
	this->DrawTitle(TitleName, pDC);
	image.ReleaseDC();
	image2.ReleaseDC();
}


// CMusicMakerView 인쇄


void CMusicMakerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMusicMakerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMusicMakerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMusicMakerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMusicMakerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMusicMakerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMusicMakerView 진단

#ifdef _DEBUG
void CMusicMakerView::AssertValid() const
{
	CView::AssertValid();
}

void CMusicMakerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMusicMakerDoc* CMusicMakerView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMusicMakerDoc)));
	return (CMusicMakerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMusicMakerView 메시지 처리기


int CMusicMakerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CRect r;
	GetClientRect(&r);
	td.DoModal();
	TitleName = td.TitleStr;
	np = new Note[20];
	for (int i = 0, j =SXSTART, f = SYSTART; i < 20; ++i)
	{
		if (i % 4 == 0)
		{
			if (i != 0)
			{
				j = SXSTART;
				f += SYGAP+SYNOTEHEIGHT;
			}
			np[i].SetNote(MaxRythmVal, SXFIRSTGAP, SYNOTEHEIGHT, j, f);
			j += SXFIRSTGAP+SXGAP;
		}
		else
		{
			np[i].SetNote(MaxRythmVal, SXWIDTH,SYNOTEHEIGHT, j, f);
			j += SXWIDTH + SXGAP;
		}
	}
	return 0;
}


void CMusicMakerView::DrawTitle(CString str, CDC* dc)
{
	// TODO: 여기에 구현 코드 추가.
	CRect r;
	GetClientRect(&r);
	r.top = 40;
	vfont.CreateFontW(60, 30, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("굴림"));
	oldfont = dc->SelectObject(&vfont);
	dc->SetBkMode(TRANSPARENT);
	dc->DrawTextW(TitleName, r, DT_CENTER);
	dc->SelectObject(oldfont);
	dc->SetBkMode(OPAQUE);
	vfont.DeleteObject();
}


void CMusicMakerView::OnModifyTitle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (td.DoModal() == ID_BUTTON_TITLEOK)
	{
		TitleName = td.TitleStr;
		Invalidate();
	}
	else
	{
		TitleName = td.TitleStr;
		Invalidate();
	}
}

void CMusicMakerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	PanePos(point);
	CView::OnMouseMove(nFlags, point);
}


void CMusicMakerView::PanePos(CPoint point)
{
	// TODO: 여기에 구현 코드 추가.
	CString str;
	str.Format(_T("(%d,%d)"), point.x, point.y);
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	pMain->GetStBar().SetPaneText(1, str);
}


int CMusicMakerView::GetRythm()
{
	// TODO: 여기에 구현 코드 추가.
	return MaxRythmVal;
}



void CMusicMakerView::On4by4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (Is4by4)
		AfxMessageBox(_T("박자는 최소한 1개 이상은 선택되어야 합니다."));
	else if (!Is4by4)
	{
		if (AfxMessageBox(_T("박자를 바꾸시면 악보가 초기화됩니다. 그래도 괜찮습니까?"), MB_YESNO) == IDYES)
		{
			Is4by4 = true;
			Is3by4 = false;
			Is6by8 = false;
			MaxRythmVal = RM4by4;
			for (int i = 0; i < 20; ++i)
			{
				np[i].NoteClear();
				np[i].SetMaxTime(MaxRythmVal);
			}
			Invalidate();
		}
	}
}


void CMusicMakerView::On3by4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (Is3by4)
		AfxMessageBox(_T("박자는 최소한 1개 이상은 선택되어야 합니다."));
	else if (!Is3by4)
	{
		if (AfxMessageBox(_T("박자를 바꾸시면 악보가 초기화됩니다. 그래도 괜찮습니까?"), MB_YESNO) == IDYES)
		{
			Is4by4 = false;
			Is3by4 = true;
			Is6by8 = false;
			MaxRythmVal = RM3by4;
			for (int i = 0; i < 20; ++i)
			{
				np[i].NoteClear();
				np[i].SetMaxTime(MaxRythmVal);
			}
			Invalidate();
		}
	}
}


void CMusicMakerView::On6by4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (Is6by8)
		AfxMessageBox(_T("박자는 최소한 1개 이상은 선택되어야 합니다."));
	else if (!Is6by8)
	{
		if (AfxMessageBox(_T("박자를 바꾸시면 악보가 초기화됩니다. 그래도 괜찮습니까?"), MB_YESNO) == IDYES)
		{
			Is4by4 = false;
			Is3by4 = false;
			Is6by8 = true;
			MaxRythmVal = RM6by8;
			for (int i = 0; i < 20; ++i)
			{
				np[i].NoteClear();
				np[i].SetMaxTime(MaxRythmVal);
			}
			Invalidate();
		}
	}
}


void CMusicMakerView::OnUpdate3by4(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (Is3by4)
		pCmdUI->SetCheck(true);
	else if (!Is3by4)
		pCmdUI->SetCheck(false);
}


void CMusicMakerView::OnUpdate4by4(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (Is4by4)
		pCmdUI->SetCheck(true);
	else if (!Is4by4)
		pCmdUI->SetCheck(false);
}


void CMusicMakerView::OnUpdate6by4(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (Is6by8)
		pCmdUI->SetCheck(true);
	else if (!Is6by8)
		pCmdUI->SetCheck(false);
}


void CMusicMakerView::DrawRythm(CImage& im)
{
	// TODO: 여기에 구현 코드 추가.
	if (Is4by4)
	{
		im.Load(L"image/44.png");
	}
	else if (Is3by4)
	{
		im.Load(L"image/34.jpg");
	}
	else if (Is6by8)
	{
		im.Load(L"image/68.jpg");
	}
}


void CMusicMakerView::DrawSeperateLine(CDC& dc)
{
	// TODO: 여기에 구현 코드 추가.
}


void CMusicMakerView::OnNoteSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog fd(FALSE,L"jpeg",L"악보",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,L"(사진(*jpeg)|*jpeg|모든파일(*.*)|*.*||");
	if (fd.DoModal() == IDOK)
	{
		CString str;
		HWND hwnd = ::GetActiveWindow();
		HDC hdc = ::GetDC(hwnd);
		CImage im;
		CRect r;
		GetClientRect(&r);
		int cx = r.right-5;
		int cy = r.bottom-100;
		int cd = GetDeviceCaps(hdc, BITSPIXEL);
		im.Create(cx, cy, cd, 0);
		::BitBlt(im.GetDC(), 0, 0, cx, cy, hdc, 5, 100, SRCCOPY);
		str.Format(_T("%s"), fd.GetPathName());
		im.Save(str, Gdiplus::ImageFormatJPEG);
		::ReleaseDC(NULL, hdc);
		im.ReleaseDC();
	}
}


void CMusicMakerView::OnInsertNote()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	indlg.SetOctavwe();
	if (indlg.DoModal() == 25)
	{
		IsSharpOn = indlg.Sharp();
		IsSlowOn = indlg.SlowNote();
		SingleNoteName = indlg.GetNoteName();
		SingleNoteTime = indlg.GetNoteRythm();
		Oct = indlg.GetOctavePower();
		SingNote*sp = new SingNote(instrument,SingleNoteTime,Oct,SingleNoteName,IsSlowOn,IsSharpOn);
		for (int i = 0; i < 20; ++i)
		{
			if (np[i].FindInsert())
			{
				if (np[i].CanInsert(sp->GetTime()))
					np[i].AddSingleNote(sp);
				else
					AfxMessageBox(_T("해당 음이 최대 마디당 박자수를 초과합니다."));
				break;
			}
		}
	}
	else
		AfxMessageBox(_T("음 추가를 위한 기본설정 실패"));
	Invalidate();
}


void CMusicMakerView::OnSelectInstronumentMenu()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SelectInstronument si;
	if (si.DoModal() == IDOK)
	{
		instrument = si.GetinstronumentNo();
		switch (instrument)
		{
		case PIANO:
			AfxMessageBox(_T("피아노로 설정"));
			InstruStr = _T("현재 악기는 : 피아노");
			Invalidate();
			for (int i = 0; i < 20; ++i)
			{
				if (np[i].IsOn())
				{
					for (auto a : np[i].SNarr)
						a->Setinstrument(instrument);
				}
			}
			break;
		case GUITAR:
			AfxMessageBox(_T("일렉트릭 기타로 설정"));
			InstruStr= _T("현재 악기는 : 일렉트릭 기타");
			Invalidate();
			for (int i = 0; i < 20; ++i)
			{
				if (np[i].IsOn())
				{
					for (auto a : np[i].SNarr)
						a->Setinstrument(instrument);
				}
			}
			break;
		case ELECTRICPIANO:
			MessageBox(_T("일렉트릭 피아노로 설정"));
			InstruStr = _T("현재 악기는 : 일렉트릭 피아노");
			Invalidate();
			for (int i = 0; i < 20; ++i)
			{
				if (np[i].IsOn())
				{
					for (auto a : np[i].SNarr)
						a->Setinstrument(instrument);
				}
			}
			break;
		case ACGUITAR:
			MessageBox(_T("아쿠아스틱 기타로 설정"));
			InstruStr = _T("현재 악기는 : 아쿠아스틱 기타");
			Invalidate();
			for (int i = 0; i < 20; ++i)
			{
				if (np[i].IsOn())
				{
					for (auto a : np[i].SNarr)
						a->Setinstrument(instrument);
				}
			}
			break;
		case BASSGUITAR:
			MessageBox(_T("베이스기타로 설정"));
			InstruStr = _T("현재 악기는 : 베이스 기타");
			Invalidate();
			for (int i = 0; i < 20; ++i)
			{
				if (np[i].IsOn())
				{
					for (auto a : np[i].SNarr)
						a->Setinstrument(instrument);
				}
			}
			break;
		case VIOLIN:
			MessageBox(_T("바이올린으로 설정"));
			InstruStr = _T("현재 악기는 : 바이올린");
			Invalidate();
			for (int i = 0; i < 20; ++i)
			{
				if (np[i].IsOn())
				{
					for (auto a : np[i].SNarr)
						a->Setinstrument(instrument);
				}
			}
			break;
		case TRUMPET:
			MessageBox(_T("트럼펫으로 설정"));
			InstruStr = _T("현재 악기는 : 트럼펫");
			Invalidate();
			for (int i = 0; i < 20; ++i)
			{
				if (np[i].IsOn())
				{
					for (auto a : np[i].SNarr)
						a->Setinstrument(instrument);
				}
			}
			break;
		case SAX:
			MessageBox(_T("섹소폰으로 설정"));
			InstruStr = _T("현재 악기는 : 섹소폰");
			Invalidate();
			for (int i = 0; i < 20; ++i)
			{
				if (np[i].IsOn())
				{
					for (auto a : np[i].SNarr)
						a->Setinstrument(instrument);
				}
			}
			break;
		case FLUTE:
			MessageBox(_T("플룻로 설정"));
			InstruStr = _T("현재 악기는 : 플룻");
			Invalidate();
			for (int i = 0; i < 20; ++i)
			{
				if (np[i].IsOn())
				{
					for (auto a : np[i].SNarr)
						a->Setinstrument(instrument);
				}
			}
			break;
		case ENSENBLE:
			MessageBox(_T("현악기 앙상블로 설정"));
			InstruStr = _T("현재 악기는 : 현악기 앙상블");
			Invalidate();
			for (int i = 0; i < 20; ++i)
			{
				if (np[i].IsOn())
				{
					for (auto a : np[i].SNarr)
						a->Setinstrument(instrument);
				}
			}
			break;
		case VOICE:
			MessageBox(_T("합창으로 설정"));
			InstruStr = _T("현재 악기는 : 합창");
			Invalidate();
			for (int i = 0; i < 20; ++i)
			{
				if (np[i].IsOn())
				{
					for (auto a : np[i].SNarr)
						a->Setinstrument(instrument);
				}
			}
			break;
		case OCARINA:
			MessageBox(_T("오카리나로 설정"));
			InstruStr = _T("현재 악기는 : 오카리나");
			Invalidate();
			for (int i = 0; i < 20; ++i)
			{
				if (np[i].IsOn())
				{
					for (auto a : np[i].SNarr)
						a->Setinstrument(instrument);
				}
			}
			break;
		case PAD:
			MessageBox(_T("악기패드로 설정"));
			InstruStr = _T("현재 악기는 : 악기패드");
			Invalidate();
			for (int i = 0; i < 20; ++i)
			{
				if (np[i].IsOn())
				{
					for (auto a : np[i].SNarr)
						a->Setinstrument(instrument);
				}
			}
			break;
		default:
			AfxMessageBox(_T("악기설정 실패"));
			break;
		}
	}
	else
	{
		AfxMessageBox(_T("악기 설정 실패"));
	}
}


void CMusicMakerView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	Invalidate();
}


void CMusicMakerView::OnPlay()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (np[0].GetCount() == 0)
	{
		AfxMessageBox(_T("입력된 음이 없습니다."));
		return;
	}
	temp.clear();
	for (int i = 0; i < 20; ++i)
	{
		if (np[i].IsOn())
		{
			for (auto a : np[i].SNarr)
				temp.push_back(a);
		}
	}
	LPVOID tmp = &temp;
	pThread = AfxBeginThread(NotePlay, tmp);
}
/*
IsPlay = true;
IsPlay = false;
	PlayX = 0;
	PlayY = 0;
	KillTimer(0);
	KillTimer(1);
*/

void CMusicMakerView::OnInsertRest()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	InsertRestDlg rd;
	double RestTime = 0;
	if (rd.DoModal() == IDOK)
	{
		int index = rd.GetRestType();
		switch (index)
		{
		case 0:
			RestTime = 4.0;
			break;
		case 1:
			RestTime = 3.0;
			break;
		case 2:
			RestTime = 2.0;
			break;
		case 3:
			RestTime = 1.0;
			break;
		case 4:
			RestTime = 0.5;
			break;
		case 5:
			RestTime = 0.25;
			break;
		default:
			AfxMessageBox(_T("쉼표 설정중에 오류 발생"));
			break;
		}
		SingRest* sr = new SingRest(RestTime);
		for (int i = 0; i < 20; ++i)
		{
			if (np[i].FindInsert())
			{
				if (np[i].CanInsert(sr->GetTime()))
					np[i].AddSingleNote(sr);
				else
					AfxMessageBox(_T("해당 쉼표가 최대 마디당 박자수를 초과합니다."));
				break;
			}
		}
	}
	else
		AfxMessageBox(_T("쉼표추가중에 비정상 종료"));
	Invalidate();
}


void CMusicMakerView::OnDeleteNote()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (np[0].SNarr.empty())
		AfxMessageBox(_T("삭제할 음이 없습니다."));
	else
	{
		temp.clear();
		int o = 0;
		for (int i = 0; i < 20; ++i)
		{
			if (np[i].IsOn())
			{
				for (auto a : np[i].SNarr)
					temp.push_back(a);
			}
		}
		DeleteNoteDlg dnd;
		dnd.SetArr(temp);
		if (dnd.DoModal() == IDOK)
		{
			o = dnd.GetIndex();
			int k = 0;
			int i = 0;
			for (; i < 20; ++i)
			{
				if (np[i].IsOn())
					k += np[i].GetCount();
				if (k > o)
					break;
			}
			k -= np[i].GetCount();
			o = o - k;
			np[i].Delete(o);
			temp.clear();
		}
		Invalidate();
	}
}


void CMusicMakerView::OnInsertHarmony()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	InsertHarmonyDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		switch (dlg.GetRhythm())
		{
		case 0:
			HarmonyNoteTime = 4.0;
			break;
		case 1:
			HarmonyNoteTime = 3.0;
			break;
		case 2:
			HarmonyNoteTime = 2.0;
			break;
		case 3:
			HarmonyNoteTime = 1.0;
			break;
		case 4:
			HarmonyNoteTime = 0.5;
			break;
		case 5:
			HarmonyNoteTime = 0.25;
			break;
		default:
			AfxMessageBox(_T("박자 읽기 도중 오류 발생"));
			break;
		}
		SingHarmony* hp = new SingHarmony(instrument,HarmonyNoteTime);
		for (auto a : dlg.NoteList)
		{
			hp->NoteName.push_back(a);
		}
		for (auto a : dlg.OctaveList)
			hp->Octave.push_back(a);
		for (auto a : dlg.SharpList)
			hp->Sharp.push_back(a);
		for (auto a : dlg.SlowList)
			hp->Slow.push_back(a);
		for (int i = 0; i < 20; ++i)
		{
			if (np[i].FindInsert())
			{
				if (np[i].CanInsert(hp->GetTime()))
					np[i].AddSingleNote(hp);
				else
					AfxMessageBox(_T("해당 쉼표가 최대 마디당 박자수를 초과합니다."));
				break;
			}
		}
	}
	else
		AfxMessageBox(_T("화음 추가 실패"));
	Invalidate();
}


void CMusicMakerView::OnNotereset()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (AfxMessageBox(_T("정말로 초기화 하시겠습니까?")) == IDOK)
	{
		for (int i = 0; i < 20; ++i)
		{
			if (np[i].IsOn())
				np[i].NoteClear();
		}
		Invalidate();
	}
}


void CMusicMakerView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CView::OnTimer(nIDEvent);
}


void CMusicMakerView::OnRecord()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	LPTSTR ls =0;
	if (IsRecordNow == false)
	{
		if (np[0].GetCount() == 0)
		{
			AfxMessageBox(_T("입력된 음이 없습니다."));
			return;
		}
		mciSendString(L"open new type waveaudio alias capture", ls,
			lstrlen(ls), NULL);
		mciSendString(L"record capture", ls,
			lstrlen(ls), NULL);
		temp.clear();
		for (int i = 0; i < 20; ++i)
		{
			if (np[i].IsOn())
			{
				for (auto a : np[i].SNarr)
					temp.push_back(a);
			}
		}
		LPVOID tmp = &temp;
		pThread = AfxBeginThread(NotePlay, tmp);
		IsRecordNow = true;
	}
}

/*
RecordMusic rmd(this);
	if (rmd.DoModal()==IDC_BUTTON_SAVERECORD)
	{

	}
	*/

void CMusicMakerView::OnStoprecord()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFileDialog fd(FALSE, L"wav", L"음악", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"(음악(*wav)|*wave|모든파일(*.*)|*.*||");
	LPTSTR ls = 0;
	if (IsRecordNow == true)
	{
		mciSendString(L"stop capture", ls,
			lstrlen(ls), NULL);
		if (fd.DoModal() == IDOK)
			path = L"save capture "+ fd.GetPathName();
		mciSendString(path, ls,
			lstrlen(ls), NULL);
		mciSendString(L"close capture", ls,
			lstrlen(ls), NULL);
		IsRecordNow = false;
	}
}


void CMusicMakerView::OnUpdateStoprecord(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (IsRecordNow)
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}


void CMusicMakerView::OnUpdateRecord(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (IsRecordNow)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable();
}
