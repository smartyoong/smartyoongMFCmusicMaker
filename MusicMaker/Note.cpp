#include "pch.h"
#include "Note.h"

void Note::Draw(CDC& t)
{
	int SingleNoteXSize = 50;
	if (NoteCount == 1)
	{
		int MultiTime = 1;
		if (SNarr[0]->IsHarmony())
		{
			SingHarmony* sh = static_cast<SingHarmony*>(SNarr[0]);
			std::vector<int> HarmonyNote = sh->NoteName;
			std::vector<int> HarmonyOctave = sh->Octave;
			std::vector<bool> HarmonySharp = sh->Sharp;
			std::vector<bool> HarmonySlow = sh->Slow;
			double z = SNarr[0]->GetTime();
			for (int i = 0; i < sh->GetCount(); ++i)
			{
				int y = HarmonyNote[i];
				bool sharp = HarmonySharp[i];
				int OcatavePos = -(HarmonyOctave[i]);
				bool IsSlow = HarmonySlow[i];
				CImage cm;
				if (z == 0.25)
				{
					if (y == 0 && OcatavePos == 0)
							cm.Load(L"image/DO16U.jpg");
					else
						cm.Load(L"image/16U.jpg");
				}
				else if (z == 0.5)
				{
					if (y == 0 && OcatavePos == 0)
							cm.Load(L"image/DO8U.jpg");
					else
						cm.Load(L"image/8U.jpg");
				}
				else if (z == 1.0)
				{
					if (y == 0 && OcatavePos == 0)
							cm.Load(L"image/DO4U.jpg");
					else
					{
						cm.Load(L"image/4U.jpg");
					}
				}
				else if (z == 2.0)
				{
					if (y == 0 && OcatavePos == 0)
							cm.Load(L"image/DO2U.jpg");
					else
					{
						cm.Load(L"image/2U.jpg");
					}
				}
				else if (z == 3.0)
				{
					if (y == 0 && OcatavePos == 0)
							cm.Load(L"image/DOD2U.jpg");
					else
					{
						cm.Load(L"image/D2U.jpg");
					}
				}
				else if (z == 4.0)
				{
					if (y == 0 && OcatavePos == 0)
						cm.Load(L"image/DO1U.jpg");
					else
					{
						cm.Load(L"image/1U.jpg");
					}
				}
				else
					AfxMessageBox(_T("음표 그리기 중에 박자 획득에 실패"));
				int position = 0;
				switch (y)
				{
				case 0:
					position = DoPosition;
					break;
				case 1:
					position = RaePosition;
					break;
				case 2:
					position = MiPosition;
					break;
				case 3:
					position = PaPosition;
					break;
				case 4:
					position = SolPosition;
					break;
				case 5:
					position = RaPosition;
					break;
				case 6:
					position = SiPosition-54;
					if (z == 3.0)
						position = SiPosition - 40;
					break;
				default:
					AfxMessageBox(_T("음표 그리기 중에 계이름 획득 실패"));
				}
				CDC& memdc = *CDC::FromHandle(cm.GetDC());
				CImage SharpImage;
				SharpImage.Load(L"image/SHARP.jpg");
				CDC& memdc2 = *CDC::FromHandle(SharpImage.GetDC());
				int temp = NoteYStartPoint;
				if (z == 4.0)
				{
					if (sharp)
						t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 17 + 50, 30, 30, &memdc2, 0, 0, SharpImage.GetWidth(), SharpImage.GetHeight(), SRCAND);
					t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + 17 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
				}
				else if (z == 3.0 && y != 6)
				{
					if (sharp)
						t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 10 + 50, 30, 30, &memdc2, 0, 0, SharpImage.GetWidth(), SharpImage.GetHeight(), SRCAND);
					t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + 10 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
				}
				else if (z == 3.0 && y == 6)
				{
					if (sharp)
						t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position - 5 + 50, 30, 30, &memdc2, 0, 0, SharpImage.GetWidth(), SharpImage.GetHeight(), SRCAND);
					t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position - 5 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
				}
				else if (z == 0.25 || z == 0.5 && y == 6)
				{
					if (sharp)
						t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 5 + 50, 30, 30, &memdc2, 0, 0, SharpImage.GetWidth(), SharpImage.GetHeight(), SRCAND);
					t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + 5 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
				}
				else
				{
					if (sharp)
						t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 50, 30, 30, &memdc2, 0, 0, SharpImage.GetWidth(), SharpImage.GetHeight(), SRCAND);
					t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
				}
				if (IsSlow)
				{
					CImage SlowImagwe;
					SlowImagwe.Load(L"image/SLOW.png");
					CDC& memdc3 = *CDC::FromHandle(SlowImagwe.GetDC());
					memdc3.SetBkMode(TRANSPARENT);
					t.StretchBlt(NoteXStartPoint, NoteYStartPoint - 50 + (OcatavePos * 75), 30, 20, &memdc3, 0, 0, SlowImagwe.GetWidth(), SlowImagwe.GetHeight(), SRCAND);
					SlowImagwe.ReleaseDC();
				}
				cm.ReleaseDC();
				SharpImage.ReleaseDC();
				NoteYStartPoint = temp;
			}
		}
		else
		{
			int y = SNarr[0]->GetNoteName();
			double z = SNarr[0]->GetTime();
			bool sharp = SNarr[0]->IsSharp();
			int OcatavePos = 0;
			OcatavePos = -(SNarr[0]->GetOcatave());
			CImage cm;
			if (z == 0.25)
			{
				if (y == 0)
					if (OcatavePos < 0)
						cm.Load(L"image/R16U.jpg");
					else
						cm.Load(L"image/DO16U.jpg");
				else if (y >= 6 || OcatavePos < 0)
					cm.Load(L"image/R16U.jpg");
				else
				{
					if (SNarr[0]->IsRest())
						cm.Load(L"image/16R.jpg");
					else
						cm.Load(L"image/16U.jpg");
				}
			}
			else if (z == 0.5)
			{
				if (y == 0)
					if (OcatavePos < 0)
						cm.Load(L"image/R8U.jpg");
					else
						cm.Load(L"image/DO8U.jpg");
				else if (y >= 6 || OcatavePos < 0)
					cm.Load(L"image/R8U.jpg");
				else
				{
					if (SNarr[0]->IsRest())
						cm.Load(L"image/8R.jpg");
					else
						cm.Load(L"image/8U.jpg");
				}
			}
			else if (z == 1.0)
			{
				if (y == 0)
					if (OcatavePos < 0)
						cm.Load(L"image/R4U.jpg");
					else
						cm.Load(L"image/DO4U.jpg");
				else if (y >= 6 || OcatavePos < 0)
					cm.Load(L"image/R4U.jpg");
				else
				{
					if (SNarr[0]->IsRest())
						cm.Load(L"image/4R.jpg");
					else
						cm.Load(L"image/4U.jpg");
				}
			}
			else if (z == 2.0)
			{
				if (y == 0)
					if (OcatavePos < 0)
						cm.Load(L"image/R2U.jpg");
					else
						cm.Load(L"image/DO2U.jpg");
				else if (y >= 6 || OcatavePos < 0)
					cm.Load(L"image/R2U.jpg");
				else
				{
					if (SNarr[0]->IsRest())
						cm.Load(L"image/Rest2.jpg");
					else
						cm.Load(L"image/2U.jpg");
				}
			}
			else if (z == 3.0)
			{
				if (y == 0)
					if (OcatavePos < 0)
						cm.Load(L"image/RD2U.jpg");
					else
						cm.Load(L"image/DOD2U.jpg");
				else if (y >= 6 || OcatavePos > 0)
					cm.Load(L"image/RD2U.jpg");
				else
				{
					if (SNarr[0]->IsRest())
						cm.Load(L"image/D2R.jpg");
					else
						cm.Load(L"image/D2U.jpg");
				}
			}
			else if (z == 4.0)
			{
				if (y == 0)
					if (OcatavePos < 0)
						cm.Load(L"image/1U.jpg");
					else
						cm.Load(L"image/1U.jpg");
				else if (y >= 6 || OcatavePos > 0)
				{
					cm.Load(L"image/1U.jpg");
					SiPosition = -40;
				}
				else
				{
					if (SNarr[0]->IsRest())
						cm.Load(L"image/1R.jpg");
					else
						cm.Load(L"image/1U.jpg");
				}
			}
			else
				AfxMessageBox(_T("음표 그리기 중에 박자 획득에 실패"));
			int position = 0;
			switch (y)
			{
			case 0:
				position = DoPosition;
				break;
			case 1:
				position = RaePosition;
				break;
			case 2:
				position = MiPosition;
				break;
			case 3:
				position = PaPosition;
				break;
			case 4:
				position = SolPosition;
				break;
			case 5:
				position = RaPosition;
				break;
			case 6:
				position = SiPosition;
				break;
			default:
				AfxMessageBox(_T("음표 그리기 중에 계이름 획득 실패"));
			}
			CDC& memdc = *CDC::FromHandle(cm.GetDC());
			CImage SharpImage;
			SharpImage.Load(L"image/SHARP.jpg");
			CDC& memdc2 = *CDC::FromHandle(SharpImage.GetDC());
			int temp = NoteYStartPoint;
			if (OcatavePos < 0)
			{
				if (z != 4.0 && z != 3.0)
				{
					++OcatavePos;
					NoteYStartPoint -= 6;
				}
				else if (z == 4.0)
					NoteYStartPoint += 11;
				else
				{
					++OcatavePos;
					NoteYStartPoint -= 21;
				}
			}
			if (z == 4.0)
			{
				if (sharp)
					t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 17 + 50, 30, 30, &memdc2, 0, 0, SharpImage.GetWidth(), SharpImage.GetHeight(), SRCAND);
				t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + 17 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
			}
			else if (z == 3.0 && y != 6)
			{
				if (sharp)
					t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 10 + 50, 30, 30, &memdc2, 0, 0, SharpImage.GetWidth(), SharpImage.GetHeight(), SRCAND);
				t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + 10 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
			}
			else if (z == 3.0 && y == 6)
			{
				if (sharp)
					t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position - 5 + 50, 30, 30, &memdc2, 0, 0, SharpImage.GetWidth(), SharpImage.GetHeight(), SRCAND);
				t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position - 5 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
			}
			else if (z == 0.25 || z == 0.5 && y == 6)
			{
				if (sharp)
					t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 5 + 50, 30, 30, &memdc2, 0, 0, SharpImage.GetWidth(), SharpImage.GetHeight(), SRCAND);
				t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + 5 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
			}
			else
			{
				if (sharp)
					t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 50, 30, 30, &memdc2, 0, 0, SharpImage.GetWidth(), SharpImage.GetHeight(), SRCAND);
				t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
			}
			if (SNarr[0]->IsSlow())
			{
				CImage SlowImagwe;
				SlowImagwe.Load(L"image/SLOW.png");
				CDC& memdc3 = *CDC::FromHandle(SlowImagwe.GetDC());
				memdc3.SetBkMode(TRANSPARENT);
				t.StretchBlt(NoteXStartPoint, NoteYStartPoint - 50 + (OcatavePos * 75), 30, 20, &memdc3, 0, 0, SlowImagwe.GetWidth(), SlowImagwe.GetHeight(), SRCAND);
				SlowImagwe.ReleaseDC();
			}
			cm.ReleaseDC();
			SharpImage.ReleaseDC();
			NoteYStartPoint = temp;
		}
	}
	else
	{
		int MultiTime = 0;
		bool isfirst = false;
		for (auto a : SNarr)
		{
			if (a->IsHarmony())
			{
				SingHarmony* sh = static_cast<SingHarmony*>(a);
				std::vector<int> HarmonyNote = sh->NoteName;
				std::vector<int> HarmonyOctave = sh->Octave;
				std::vector<bool> HarmonySharp = sh->Sharp;
				std::vector<bool> HarmonySlow = sh->Slow;
				double z = a->GetTime();
				for (int i = 0; i < sh->GetCount(); ++i)
				{
					int y = HarmonyNote[i];
					bool sharp = HarmonySharp[i];
					int OcatavePos = -(HarmonyOctave[i]);
					bool IsSlow = HarmonySlow[i];
					CImage cm;
					if (z == 0.25)
					{
						if (y == 0 && OcatavePos == 0)
							cm.Load(L"image/DO16U.jpg");
						else
						{
							cm.Load(L"image/16U.jpg");
						}
					}
					else if (z == 0.5)
					{
						if (y == 0 && OcatavePos == 0)
							cm.Load(L"image/DO8U.jpg");
						else
						{
							cm.Load(L"image/8U.jpg");
						}
					}
					else if (z == 1.0)
					{
						if (y == 0 && OcatavePos == 0)
							cm.Load(L"image/DO4U.jpg");
						else
						{
							cm.Load(L"image/4U.jpg");
						}
					}
					else if (z == 2.0)
					{
						if (y == 0 && OcatavePos == 0)
							cm.Load(L"image/DO2U.jpg");
						else
						{
							cm.Load(L"image/2U.jpg");
						}
					}
					else if (z == 3.0)
					{
						if (y == 0 && OcatavePos == 0)
							cm.Load(L"image/DOD2U.jpg");
						else
						{
							cm.Load(L"image/D2U.jpg");
						}
					}
					else if (z == 4.0)
					{
						if (y == 0 && OcatavePos == 0)
							cm.Load(L"image/DO1U.jpg");
						else
						{
							cm.Load(L"image/1U.jpg");
						}
					}
					else
						AfxMessageBox(_T("음표 그리기 중에 박자 획득에 실패"));
					int position = 0;
					switch (y)
					{
					case 0:
						position = DoPosition;
						break;
					case 1:
						position = RaePosition;
						break;
					case 2:
						position = MiPosition;
						break;
					case 3:
						position = PaPosition;
						break;
					case 4:
						position = SolPosition;
						break;
					case 5:
						position = RaPosition;
						break;
					case 6:
						position = SiPosition -54;
						if (z == 3.0)
							position = SiPosition - 40;
						break;
					default:
						AfxMessageBox(_T("음표 그리기 중에 계이름 획득 실패"));
					}
					CDC& memdc = *CDC::FromHandle(cm.GetDC());
					CImage ImageSharp;
					ImageSharp.Load(L"image/SHARP.jpg");
					CDC& memdc2 = *CDC::FromHandle(ImageSharp.GetDC());
					int temp = NoteYStartPoint;
					if (isfirst)
					{
						if (z == 4.0)
						{
							if (sharp)
								t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 17 + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
							t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + 17 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
						}
						else if (z == 3.0 && y != 6)
						{
							if (sharp)
								t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 10 + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
							t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + 10 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
						}
						else if (z == 3.0 && y == 6)
						{
							if (sharp)
								t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position - 5 + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
							t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position - 5 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
						}
						else if (z == 0.25 || z == 0.5 && y == 6)
						{
							if (sharp)
								t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 8 + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
							t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + 8 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
						}
						else
						{
							if (sharp)
								t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
							t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
						}
						if (IsSlow)
						{
							CImage SlowImagwe;
							SlowImagwe.Load(L"image/SLOW.png");
							CDC& memdc3 = *CDC::FromHandle(SlowImagwe.GetDC());
							memdc3.SetBkMode(TRANSPARENT);
							t.StretchBlt(NoteXStartPoint, NoteYStartPoint - 50 + (OcatavePos * 75), 30, 20, &memdc3, 0, 0, SlowImagwe.GetWidth(), SlowImagwe.GetHeight(), SRCAND);
							SlowImagwe.ReleaseDC();
						}
						cm.ReleaseDC();
						ImageSharp.ReleaseDC();
					}
					else
					{
						if (z == 4.0)
						{
							if (sharp)
								t.StretchBlt((NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime) - 20, NoteYStartPoint + 17 + position + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
							t.StretchBlt(NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime, NoteYStartPoint + 17 + position + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
						}
						else if (z == 3.0 && y != 6)
						{
							if (sharp)
								t.StretchBlt((NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime) - 20, NoteYStartPoint + 10 + position + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
							t.StretchBlt(NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime, NoteYStartPoint + 10 + position + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
						}
						else if (z == 3.0 && y == 6)
						{
							if (sharp)
								t.StretchBlt((NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime) - 20, NoteYStartPoint - 5 + position + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
							t.StretchBlt(NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime, NoteYStartPoint - 5 + position + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
						}
						else if (z == 0.25 || z == 0.5 && y == 6)
						{
							if (sharp)
								t.StretchBlt((NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime) - 20, NoteYStartPoint + 8 + position + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
							t.StretchBlt(NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime, NoteYStartPoint + position + 8 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
						}
						else
						{
							if (IsSlow)
								t.StretchBlt((NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime) - 20, NoteYStartPoint + position + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
							t.StretchBlt(NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime, NoteYStartPoint + position + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
						}
						if (IsSlow)
						{
							CImage SlowImagwe;
							SlowImagwe.Load(L"image/SLOW.png");
							CDC& memdc3 = *CDC::FromHandle(SlowImagwe.GetDC());
							memdc3.SetBkMode(TRANSPARENT);
							t.StretchBlt(NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime, NoteYStartPoint - 50 + (OcatavePos * 75), 30, 20, &memdc3, 0, 0, SlowImagwe.GetWidth(), SlowImagwe.GetHeight(), SRCAND);
							SlowImagwe.ReleaseDC();
						}
						cm.ReleaseDC();
						ImageSharp.ReleaseDC();
					}
					isfirst = false;
					NoteYStartPoint = temp;
				}
				MultiTime++;
			}
			else
			{
				int OcatavePos = -(a->GetOcatave());
				int y = a->GetNoteName();
				double z = a->GetTime();
				CImage cm;
				if (z == 0.25)
				{
					if (y == 0)
						if (OcatavePos < 0)
							cm.Load(L"image/R16U.jpg");
						else
							cm.Load(L"image/DO16U.jpg");
					else if (y >= 6 || OcatavePos < 0)
					{
						cm.Load(L"image/R16U.jpg");
					}
					else
					{
						if (a->IsRest())
							cm.Load(L"image/16R.jpg");
						else
							cm.Load(L"image/16U.jpg");
					}
				}
				else if (z == 0.5)
				{
					if (y == 0)
						if (OcatavePos < 0)
							cm.Load(L"image/R8U.jpg");
						else
							cm.Load(L"image/DO8U.jpg");
					else if (y >= 6 || OcatavePos < 0)
					{
						cm.Load(L"image/R8U.jpg");
					}
					else
					{
						if (a->IsRest())
							cm.Load(L"image/8R.jpg");
						else
							cm.Load(L"image/8U.jpg");
					}
				}
				else if (z == 1.0)
				{
					if (y == 0)
						if (OcatavePos < 0)
							cm.Load(L"image/R4U.jpg");
						else
							cm.Load(L"image/DO4U.jpg");
					else if (y >= 6 || OcatavePos < 0)
						cm.Load(L"image/R4U.jpg");
					else
					{
						if (a->IsRest())
							cm.Load(L"image/4R.jpg");
						else
							cm.Load(L"image/4U.jpg");
					}
				}
				else if (z == 2.0)
				{
					if (y == 0)
						if (OcatavePos < 0)
							cm.Load(L"image/R2U.jpg");
						else
							cm.Load(L"image/DO2U.jpg");
					else if (y >= 6 || OcatavePos < 0)
						cm.Load(L"image/R2U.jpg");
					else
					{
						if (a->IsRest())
							cm.Load(L"image/Rest2.jpg");
						else
							cm.Load(L"image/2U.jpg");
					}
				}
				else if (z == 3.0)
				{
					if (y == 0)
						if (OcatavePos < 0)
							cm.Load(L"image/RD2U.jpg");
						else
							cm.Load(L"image/DOD2U.jpg");
					else if (y >= 6 || OcatavePos > 0)
					{
						cm.Load(L"image/RD2U.jpg");
					}
					else
					{
						if (a->IsRest())
							cm.Load(L"image/D2R.jpg");
						else
							cm.Load(L"image/D2U.jpg");
					}
				}
				else if (z == 4.0)
				{
					if (y == 0)
						cm.Load(L"image/DO1U.jpg");
					else if (y >= 6 || OcatavePos > 0)
					{
						cm.Load(L"image/1U.jpg");
						SiPosition = -40;
					}
					else
					{
						if (a->IsRest())
							cm.Load(L"image/1R.jpg");
						else
							cm.Load(L"image/1U.jpg");
					}
				}
				else
					AfxMessageBox(_T("음표 그리기 중에 박자 획득에 실패"));
				int position = 0;
				switch (y)
				{
				case 0:
					position = DoPosition;
					break;
				case 1:
					position = RaePosition;
					break;
				case 2:
					position = MiPosition;
					break;
				case 3:
					position = PaPosition;
					break;
				case 4:
					position = SolPosition;
					break;
				case 5:
					position = RaPosition;
					break;
				case 6:
					position = SiPosition;
					break;
				default:
					AfxMessageBox(_T("음표 그리기 중에 계이름 획득 실패"));
				}
				CDC& memdc = *CDC::FromHandle(cm.GetDC());
				CImage ImageSharp;
				ImageSharp.Load(L"image/SHARP.jpg");
				CDC& memdc2 = *CDC::FromHandle(ImageSharp.GetDC());
				int temp = NoteYStartPoint;
				if (OcatavePos < 0)
				{
					if (z != 4.0 && z != 3.0)
					{
						++OcatavePos;
						NoteYStartPoint -= 6;
					}
					else if (z == 4.0)
						NoteYStartPoint += 11;
					else
					{
						++OcatavePos;
						NoteYStartPoint -= 21;
					}
				}
				if (isfirst)
				{
					if (z == 4.0)
					{
						if (a->IsSharp())
							t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 17 + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
						t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + 17 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
					}
					else if (z == 3.0 && y != 6)
					{
						if (a->IsSharp())
							t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 10 + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
						t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + 10 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
					}
					else if (z == 3.0 && y == 6)
					{
						if (a->IsSharp())
							t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position - 5 + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
						t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position - 5 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
					}
					else if (z == 0.25 || z == 0.5 && y == 6)
					{
						if (a->IsSharp())
							t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 8 + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
						t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + 8 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
					}
					else
					{
						if (a->IsSharp())
							t.StretchBlt(NoteXStartPoint - 20, NoteYStartPoint + position + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
						t.StretchBlt(NoteXStartPoint, NoteYStartPoint + position + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
					}
					if (a->IsSlow())
					{
						CImage SlowImagwe;
						SlowImagwe.Load(L"image/SLOW.png");
						CDC& memdc3 = *CDC::FromHandle(SlowImagwe.GetDC());
						memdc3.SetBkMode(TRANSPARENT);
						t.StretchBlt(NoteXStartPoint, NoteYStartPoint - 50 + (OcatavePos * 75), 30, 20, &memdc3, 0, 0, SlowImagwe.GetWidth(), SlowImagwe.GetHeight(), SRCAND);
						SlowImagwe.ReleaseDC();
					}
					cm.ReleaseDC();
					ImageSharp.ReleaseDC();
				}
				else
				{
					if (z == 4.0)
					{
						if (a->IsSharp())
							t.StretchBlt((NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime) - 20, NoteYStartPoint + 17 + position + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
						t.StretchBlt(NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime, NoteYStartPoint + 17 + position + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
					}
					else if (z == 3.0 && y != 6)
					{
						if (a->IsSharp())
							t.StretchBlt((NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime) - 20, NoteYStartPoint + 10 + position + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
						t.StretchBlt(NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime, NoteYStartPoint + 10 + position + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
					}
					else if (z == 3.0 && y == 6)
					{
						if (a->IsSharp())
							t.StretchBlt((NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime) - 20, NoteYStartPoint - 5 + position + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
						t.StretchBlt(NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime, NoteYStartPoint - 5 + position + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
					}
					else if (z == 0.5 && y == 6)
					{
						if (a->IsSharp())
							t.StretchBlt((NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime) - 20, NoteYStartPoint + 8 + position + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
						t.StretchBlt(NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime, NoteYStartPoint + position + 8 + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
					}
					else
					{
						if (a->IsSharp())
							t.StretchBlt((NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime) - 20, NoteYStartPoint + position + 50, 30, 30, &memdc2, 0, 0, ImageSharp.GetWidth(), ImageSharp.GetHeight(), SRCAND);
						t.StretchBlt(NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime, NoteYStartPoint + position + (OcatavePos * 75), SingleNoteXSize, NoteYSize, &memdc, 0, 0, cm.GetWidth(), cm.GetHeight(), SRCAND);
					}
					if (a->IsSlow())
					{
						CImage SlowImagwe;
						SlowImagwe.Load(L"image/SLOW.png");
						CDC& memdc3 = *CDC::FromHandle(SlowImagwe.GetDC());
						memdc3.SetBkMode(TRANSPARENT);
						t.StretchBlt(NoteXStartPoint + (NoteXSize / NoteCount) * MultiTime, NoteYStartPoint - 50 + (OcatavePos * 75), 30, 20, &memdc3, 0, 0, SlowImagwe.GetWidth(), SlowImagwe.GetHeight(), SRCAND);
						SlowImagwe.ReleaseDC();
					}
					MultiTime++;
					cm.ReleaseDC();
					ImageSharp.ReleaseDC();
				}
				isfirst = false;
				NoteYStartPoint = temp;
			}
		}
	}
}

void Note::AddSingleNote(SingNote* sn)
{
	SNarr.push_back(sn);
	CurTime += sn->GetTime();
	NoteCount++;
}

void Note::DrawPlaying(CDC& memdc, CDC* dc)
{
	// TODO: 여기에 구현 코드 추가.
	//그리고 무효화하고 잠수타고를 하고싶은데,,,, 그리고 끝나면 view클래스에서 무효화 한번더
	/*
	Image image;
for (int i=0;i<image.ImgHeight;i++)
{
    for (int j=0;j<image.ImgWidth;j++)
    {
        int index = i*image.ImgWidth+j;
        unsigned char* pucColor = reinterpret_cast<unsigned char *> (image.GetPixelAddress(j , i)); 
        pucColor[0] = bValues[index];   
        pucColor[1] = gValues[index];   
        pucColor[2] = rValues[index];  
    }
}
	*/
}
