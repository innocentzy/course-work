#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <commctrl.h>
#include <wchar.h>
#include <strsafe.h>
#include "SoftwareDefinitions.h"
#include "Functions.h"

LRESULT WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) 
{
	if (message == WM_DESTROY) 
	{
		KillTimer(hwnd, IDT_TIMER1);
		PostQuitMessage(0);
	}

	if (message == WM_CREATE)
	{
		MainWndAddMenus(hwnd);
		SetOpenFileParams(hwnd);
	}

	else if (message == WM_COMMAND) 
	{
		if(LOWORD(wparam) == bt_set_time_id)
		{
			wchar_t buffer[TextBufferSize];
			GetWindowText(intedt, LPWSTR(buffer), sizeof(buffer));
			int timer_time = _wtoi(buffer) * 1000;
			if (timer_time > 0) {
				SetTimer(hwnd,
					IDT_TIMER1,
					timer_time,
					(TIMERPROC)NULL);
				SetWindowText(cap, L"Timer started");
				SetWindowText(cap1, LPCWSTR(buffer));
			}
			else MessageBox(GetActiveWindow(), L"Enter the time", L"Error!", MB_ICONERROR);
		}

		if (wparam == bt_date)
		{
			MonthCal_GetCurSel(hMonthCal, &st);
			wsprintf(buf, L"\r%d-%d-%d: ", st.wYear, st.wMonth, st.wDay);
			SendMessage(edt_note, EM_REPLACESEL, TRUE, LPARAM(buf));
		}

		if (wparam == bt_add_contact)
		{
			char ContactBuffer[TextBufferSize];
			GetWindowText(contactName_edt, LPWSTR(ContactBuffer), sizeof(ContactBuffer));
			AppendMenu(ConSubMenu, MF_POPUP, NULL, LPCWSTR(ContactBuffer));
		}
		if (wparam == OnMenuDelete)
		{
			if(GetMenuItemCount(ConSubMenu)>1)
			DeleteMenu(ConSubMenu, GetMenuItemCount(ConSubMenu)-1, MF_BYPOSITION);
			else MessageBox(GetActiveWindow(), L"No contacts", L"Error!", MB_ICONERROR);
		}
		if (wparam == OnMenuFileSave)
		{
			if (GetSaveFileName(&ofn)) SaveFile(filename);
		}
		if (wparam == OnMenuFileLoad)
		{
			if (GetSaveFileName(&ofn)) LoadFile(filename);
		}

		if (LOWORD(wparam) == bt_stop_alarm_id)
		{
			KillTimer(hwnd, IDT_TIMER1);
			SetWindowText(cap, L"Enter the time");
			SetWindowText(cap1, L"0");
			SetWindowText(intedt, L"");
		}

		if (LOWORD(wparam) == bt_clear_note_id)
		{
			SetWindowText(edt_note, L"");
		}
	}

	else if (message == WM_TIMER) 
	{
		if (wparam == IDT_TIMER1)
		{
			SetWindowText(cap, L"ALARM!");
			for (int i = 0; i < 5; i++) Beep(750, 150);
		}
	}

	else return DefWindowProcA(hwnd, message, wparam, lparam);
};

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR cmd, int iShow)
{
	WNDCLASSA wcl;
		ZeroMemory(&wcl, sizeof(WNDCLASSA));
		wcl.hIcon = LoadIcon(NULL, IDI_QUESTION);
		wcl.lpszClassName = "My Organaizer";
		wcl.lpfnWndProc = WndProc;
	RegisterClassA(&wcl);

	HWND hwnd; 
	hwnd = CreateWindow(L"My Organaizer", L"Organaizer", WS_OVERLAPPEDWINDOW,
		10, 10, 850, 500, NULL, NULL, NULL, NULL);

	ShowWindow(hwnd, SW_SHOWNORMAL);

	HWND bt1 = CreateWindow(L"button", L"Set", WS_VISIBLE | WS_CHILD,
		600, 370, 75, 40,
		hwnd, (HMENU)bt_set_time_id, NULL, NULL);

	HWND bt2 = CreateWindow(L"button", L"Stop", WS_VISIBLE | WS_CHILD,
		700, 370, 75, 40,
		hwnd, (HMENU)bt_stop_alarm_id, NULL, NULL);

	HWND bt3 = CreateWindow(L"button", L"Clear", WS_VISIBLE | WS_CHILD,
		309, 315, 184, 40,
		hwnd, (HMENU)bt_clear_note_id, NULL, NULL);

	HWND btAdd = CreateWindow(L"button", L"Add", WS_VISIBLE | WS_CHILD,
		600, 100, 175, 40,
		hwnd, (HMENU)bt_add_contact, NULL, NULL);

	HWND btDate = CreateWindow(L"button", L"Add date", WS_VISIBLE | WS_CHILD,
		10, 315, 200, 40,
		hwnd, (HMENU)bt_date, NULL, NULL);

	edt_note = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_MULTILINE | WS_VSCROLL,
		310, 110, 200, 200,
		hwnd, (HMENU)edt_note_id, NULL, NULL);

	intedt = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_NUMBER,
		600, 325, 175, 30,
		hwnd, NULL, NULL, NULL);

	contactName_edt = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT,
		600, 50, 175, 30,
		hwnd, NULL, NULL, NULL);

	hMonthCal = CreateWindow(MONTHCAL_CLASSW, L"",
		WS_BORDER | WS_CHILD | WS_VISIBLE | MCS_NOTODAYCIRCLE,
		10, 110, 200, 200, hwnd, NULL, NULL, NULL);

	calendarStat = CreateWindow(L"static", L"Calendar", WS_VISIBLE | WS_CHILD,
		80, 85, 60, 25,
		hwnd, (HMENU)CALENDAR, NULL, NULL);

	stat1 = CreateWindow(L"static", L"Note", WS_VISIBLE | WS_CHILD,
		395, 85, 30, 25,
		hwnd, NULL, NULL, NULL);

	stat2 = CreateWindow(L"static", L"Àlarm clock", WS_VISIBLE | WS_CHILD,
		665, 205, 75, 25,
		hwnd, NULL, NULL, NULL);

	stat3 = CreateWindow(L"static", L"Add contact", WS_VISIBLE | WS_CHILD,
		660, 10, 75, 25,
		hwnd, NULL, NULL, NULL);

	cap = CreateWindow(L"static", L"Enter the time", WS_VISIBLE | WS_CHILD,
		600, 245, 100, 25,
		hwnd, NULL, NULL, NULL);

	cap1 = CreateWindow(L"static", L"0", WS_VISIBLE | WS_CHILD,
		650, 280, 30, 25,
		hwnd, NULL, NULL, NULL);

	cap2 = CreateWindow(L"static", L"Time:", WS_VISIBLE | WS_CHILD,
		600, 280, 100, 25,
		hwnd, NULL, NULL, NULL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


