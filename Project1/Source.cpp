#include <windows.h>
#include <windowsX.h>
#include <tchar.h>
#include "resource.h"
#include<vector>	
#include <string>
#include <algorithm>	
#include <Commctrl.h>
#include <time.h>

int CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}


HMENU hMenu;
HWND hbutton1, hbutton2, hbutton3, hbutton4, hbutton5, hbutton6, hbutton7,
hbutton8, hbutton9, hbutton10, hbutton11, hbutton12, hbutton13, hbutton14, hbutton15, hbutton16;
std::vector<int>nembers;
std::vector<HWND>buttons;
HWND hProgress1;	
int count = 0;	
int CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp)
{
	switch (mes)
	{
	case WM_INITDIALOG:
	{
		srand(time(0));	
		hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
		SetMenu(hWnd, hMenu);
		hbutton1 = GetDlgItem(hWnd, IDC_BUTTON1);
		hbutton2 = GetDlgItem(hWnd, IDC_BUTTON2);
		hbutton3 = GetDlgItem(hWnd, IDC_BUTTON3);
		hbutton4 = GetDlgItem(hWnd, IDC_BUTTON4);	
		hbutton5 = GetDlgItem(hWnd, IDC_BUTTON5);
		hbutton6 = GetDlgItem(hWnd, IDC_BUTTON6);	
		hbutton7 = GetDlgItem(hWnd, IDC_BUTTON7);
		hbutton8 = GetDlgItem(hWnd, IDC_BUTTON8);
		hbutton9 = GetDlgItem(hWnd, IDC_BUTTON9);
		hbutton10 = GetDlgItem(hWnd, IDC_BUTTON10);
		hbutton11 = GetDlgItem(hWnd, IDC_BUTTON11);
		hbutton12 = GetDlgItem(hWnd, IDC_BUTTON12);
		hbutton13 = GetDlgItem(hWnd, IDC_BUTTON13);
		hbutton14 = GetDlgItem(hWnd, IDC_BUTTON14);
		hbutton15 = GetDlgItem(hWnd, IDC_BUTTON15);
		hbutton16 = GetDlgItem(hWnd, IDC_BUTTON16);	
		buttons.push_back(hbutton1);	
		buttons.push_back(hbutton2);
		buttons.push_back(hbutton3);
		buttons.push_back(hbutton4);
		buttons.push_back(hbutton5);
		buttons.push_back(hbutton6);
		buttons.push_back(hbutton7);
		buttons.push_back(hbutton8);
		buttons.push_back(hbutton9);
		buttons.push_back(hbutton10);
		buttons.push_back(hbutton11);
		buttons.push_back(hbutton12);
		buttons.push_back(hbutton13);
		buttons.push_back(hbutton14);
		buttons.push_back(hbutton15);
		buttons.push_back(hbutton16);	

		hProgress1 = GetDlgItem(hWnd, IDC_PROGRESS1);;	
		SendMessage(hProgress1, PBM_SETRANGE, 0, MAKELPARAM(0, 60)); // Установка интервала для индикатора	
		SendMessage(hProgress1, PBM_SETSTEP, 1, 0); // Установка шага приращения  индикатора	
		SendMessage(hProgress1, PBM_SETPOS, 0, 0); // Установка текущей позиции индикатора	
		SendMessage(hProgress1, PBM_SETBKCOLOR, 0, LPARAM(RGB(0, 0, 255))); // Установка цвета фона индикатора	
		SendMessage(hProgress1, PBM_SETBARCOLOR, 0, LPARAM(RGB(255, 255, 0))); // Установка цвета заполняемых прямоугольников	
		
		HWND hSpin = GetDlgItem(hWnd, IDC_SPIN1);		
		HWND hEdit2 = GetDlgItem(hWnd, IDC_EDIT1);				

		SendMessage(hSpin, UDM_SETRANGE32, 0, 100);	
		SendMessage(hSpin, UDM_SETBUDDY, WPARAM(hEdit2), 0);	
		SetWindowText(hEdit2, TEXT("0"));	
		
		break;
	}
	case WM_TIMER:	
	{	
		SendMessage(hProgress1, PBM_STEPIT, 0, 0);
	}
	case WM_COMMAND:
	{	
		int controlId = LOWORD(wp);
		if (HIWORD(wp) == BN_CLICKED)
		{
			if (controlId >= IDC_BUTTON1 && controlId <= IDC_BUTTON16)
			{
				HWND hButton = GetDlgItem(hWnd, controlId);
				TCHAR buttonText[256];
				GetWindowText(hButton, buttonText, 256);
				int buttonValue = _wtoi(buttonText);
				int newNumber = nembers[count];				

				if (buttonValue == newNumber)	
				{	
					count++;
					SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)buttonText);	
				}
				else
				{
					MessageBox(0, L"Неврно!", L"Information", MB_OK);
				}
			}
		}
	 switch (LOWORD(wp))
		{
		case ID_NewGame:
			MessageBox(0, L"New Game", L"Новая игра", MB_OK);
			break;
		case ID_Exit:
			MessageBox(0, L"Exit Game", L"Exit Game", MB_OK);
			break;	
		case IDC_BUTTON17:	
			nembers.clear(); 
			SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);	
			for (int i = 0; i < 16; ++i) {
				nembers.push_back(rand() % 100);	
			}
			std::sort(nembers.begin(), nembers.end());	
			for (size_t i = 0; i < buttons.size(); ++i) {	
				if (i < nembers.size()) {	
					std::wstring buttonText = std::to_wstring(nembers[i]);	
					SetWindowText(buttons[i], buttonText.c_str());
				}
			}	
			SetTimer(hWnd, 1, 100, NULL);		
			break;	
		default:
			break;
		}
		break;


	}

	case WM_CLOSE:
	  EndDialog(hWnd, 0); // закрываем модальный диалог
	  return TRUE;
	}
	return FALSE;
}
