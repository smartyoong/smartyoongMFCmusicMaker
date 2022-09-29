// RecordMusic.cpp: 구현 파일
//

#include "pch.h"
#include "MusicMaker.h"
#include "afxdialogex.h"
#include "RecordMusic.h"
#include "Note.h"

// RecordMusic 대화 상자

IMPLEMENT_DYNAMIC(RecordMusic, CDialogEx)

RecordMusic::RecordMusic(CMusicMakerView* p,CWnd* pParent /*=nullptr*/)
	:vp(p), CDialogEx(IDD_DIALOG_RECORD, pParent)
{
	WaveIn = NULL;
}

RecordMusic::~RecordMusic()
{
}

void RecordMusic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RecordMusic, CDialogEx)
	ON_BN_CLICKED(IDOK, &RecordMusic::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_SAVERECORD, &RecordMusic::OnBnClickedButtonSaverecord)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &RecordMusic::OnBnClickedButtonStop)
END_MESSAGE_MAP()


// RecordMusic 메시지 처리기
DWORD recordWAVEFile(HWND h,DWORD dwMilliSeconds);

void RecordMusic::OnBnClickedOk() //재생
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (vp->GetNoteP()[0].GetCount() == 0)
	{
		AfxMessageBox(_T("입력된 음이 없습니다."));
		return;
	}
	vp->GetTempCon()->clear();
	for (int i = 0; i < 20; ++i)
	{
		if (vp->GetNoteP()[i].IsOn())
		{
			for (auto a : vp->GetNoteP()[i].SNarr)
				vp->GetTempCon()->push_back(a);
		}
	}
	auto t =vp->GetTempCon();
	LPVOID tmp = &*t;
	CWinThread* pThread = AfxBeginThread(NotePlay, tmp);
	//CDialogEx::OnOK();
}


void RecordMusic::OnBnClickedButtonSaverecord()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!IsRecord)
	{
		AfxMessageBox(_T("녹음을 먼저 실행하세요"));
	}
	else
	{
		Have->dwFlags = WHDR_DONE;
		waveInStop(WaveIn);
		CFileDialog fd(FALSE, L"wav", L"음악", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"(음악(*wav)|*wave|모든파일(*.*)|*.*||");
		if (fd.DoModal() == IDOK)
		{
			CString str = fd.GetPathName();
			CStringA csA = CStringA(str);
			const char* c = csA;
			SaveWavFile(c, &WaveFormat, Have);
		}
		else
		{
			AfxMessageBox(_T("저장 취소"));
		}
	}
	IsRecord = false;
	waveInReset(WaveIn);
	waveInUnprepareHeader(WaveIn, Have, sizeof(WAVEHDR));
	::HeapFree(GetProcessHeap(), 0, Have->lpData);
	::HeapFree(GetProcessHeap(), 0, Have);
	waveInClose(WaveIn);
	WaveIn = NULL;
	EndDialog(IDC_BUTTON_SAVERECORD);
}


void RecordMusic::OnBnClickedButtonStop() //녹음
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (WaveIn == NULL)
	{
		IsRecord = true;
		RecordIndex = 0;
		Have = (WAVEHDR*)::HeapAlloc(GetProcessHeap(), 0, sizeof(WAVEHDR));
		Have->lpData = (char*)::HeapAlloc(GetProcessHeap(), 0, MAX_QUEUE_SIZE);
		Have->dwBufferLength = MAX_QUEUE_SIZE;
		Have->dwFlags = 0;
		Have->dwLoops = 0;
		waveInOpen(&WaveIn, WAVE_MAPPER, &WaveFormat, (DWORD)m_hWnd, NULL, CALLBACK_WINDOW);
		waveInPrepareHeader(WaveIn, Have, sizeof(WAVEHDR));
		waveInAddBuffer(WaveIn, Have, sizeof(WAVEHDR));
		waveInStart(WaveIn);
	}
}


BOOL RecordMusic::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
	WaveFormat.nChannels = 2;
	WaveFormat.nSamplesPerSec = 44100;
	WaveFormat.nAvgBytesPerSec = 44100;//WaveFormat.nSamplesPerSec * WaveFormat.nBlockAlign;
	WaveFormat.wBitsPerSample = 16;
	WaveFormat.nBlockAlign = WaveFormat.nChannels * (WaveFormat.wBitsPerSample / 8);
	WaveFormat.cbSize = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

LRESULT RecordMusic::WndProc(UINT um, WPARAM w, LPARAM l)
{
	if (um == MM_WIM_DATA && WaveIn != NULL)
	{
		WAVEHDR* h = (WAVEHDR*)l;
		Have = h;
		memcpy(Have->lpData, h->lpData, h->dwBytesRecorded);
		Have->dwBufferLength = h->dwBytesRecorded;
	}
	return RecordMusic::WindowProc(um, w, l);
}

void RecordMusic::SaveWavFile(const char* fn, WAVEFORMATEX* wf, PWAVEHDR p)
{
	std::ofstream os;
	os.open(fn, std::fstream::binary);
	int subchunksize = 16;
	int byterate = wf->nSamplesPerSec * wf->nBlockAlign;
	int subchunksize2 = p->dwBufferLength * wf->nChannels;
	int chunksize = 36;+subchunksize2;
	os.seekp(0, std::ios::beg);
	os.write("RIFF", 4);
	os.write((char*)&chunksize, 4);
	os.write("WAVE", 4);
	os.write("fmt", 4);
	os.write((char*)&subchunksize, 4);
	os.write((char*)&wf->wFormatTag, 2);
	os.write((char*)&wf->nChannels, 2);
	os.write((char*)&wf->nSamplesPerSec, 4);
	os.write((char*)&byterate, 4);
	os.write((char*)&wf->nBlockAlign, 2);
	os.write((char*)&wf->wBitsPerSample, 2);
	os.write("data", 4);
	os.write((char*)&subchunksize2, 4);
	os.write(p->lpData, subchunksize2);
	os.close();
}

//p->dwBufferLength

/*
if (waveInOpen(&WaveIn, WAVE_MAPPER, &WaveFormat, (DWORD_PTR)m_hWnd, 0, CALLBACK_WINDOW))
	{
		AfxMessageBox(_T("wavform 열기 실패"));
		return;
	}
	Have.dwBufferLength = WaveFormat.nAvgBytesPerSec;
	Have.lpData = (char*)malloc(Have.dwBufferLength);
	Have.dwBytesRecorded = 0;
	Have.dwLoops = 0;
	Have.reserved = 0;
	Have.dwUser = (ULONG_PTR)new BufferNode;
	bn = (BufferNode*)Have.dwUser;
	bn->buffer = (char*)malloc(1);
	bn->buffer = 0;
	if (waveInPrepareHeader(WaveIn, &Have, sizeof(WAVEHDR)))
	{
		AfxMessageBox(_T("녹음 준비중 오류"));
		return;
	}
	if (waveInAddBuffer(WaveIn, &Have, sizeof(WAVEHDR)))
	{
		AfxMessageBox(_T("녹음버퍼 할당중 에러"));
		waveInClose(WaveIn);
		return;
	}
	if (waveInStart(WaveIn))
	{
		AfxMessageBox(_T("녹음시작 에러"));
		waveInClose(WaveIn);
		return;
	}
	IsRecord = true;
*/

/*
CREATESTRUCT* cs = (CREATESTRUCT*)l;
	if (um == MM_WIM_DATA)
	{
		WAVEHDR* wh = (WAVEHDR*)l;
		BufferNode* bn = (BufferNode*)wh->dwUser;
		bn->buffer = realloc(bn->buffer, bn->length + wh->dwBytesRecorded);
		memcpy((char*)bn->buffer + bn->length, wh->lpData, wh->dwBytesRecorded);
		bn->length += wh->dwBytesRecorded;
		if (waveInPrepareHeader(WaveIn, wh, sizeof(WAVEHDR)))
		{
			AfxMessageBox(_T("WndProc1 에러"));
			waveInClose(WaveIn);
			return TRUE;

		}
		if (waveInAddBuffer(WaveIn, wh, sizeof(WAVEHDR)))
		{
			AfxMessageBox(_T("WndProc 에러"));
			waveInClose(WaveIn);
			return TRUE;
		}
	}
	return(WndProc(h, um, w, l));
*/

/*
if (WaveIn == NULL)
	{
		IsRecord = true;
		RecordIndex = 0;
		Have = (WAVEHDR*)::HeapAlloc(GetProcessHeap(), 0, sizeof(WAVEHDR));
		Have->lpData = (char*)::HeapAlloc(GetProcessHeap(), 0, MAX_QUEUE_SIZE);
		Have->dwBufferLength = MAX_QUEUE_SIZE;
		Have->dwFlags = 0;
		Have->dwLoops = 0;
		waveInOpen(&WaveIn, WAVE_MAPPER, &WaveFormat, (DWORD)m_hWnd, NULL, CALLBACK_WINDOW);
		waveInPrepareHeader(WaveIn, Have, sizeof(WAVEHDR));
		waveInAddBuffer(WaveIn, Have, sizeof(WAVEHDR));
		waveInStart(WaveIn);
	}
*/