#pragma once
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define OnMenuDelete 13
#define OnMenuFileSave 14
#define OnMenuFileLoad 15
#define CALENDAR 22

#define bt_set_time_id 2
#define edt_note_id 3
#define cb_id 4
#define IDT_TIMER1 5
#define bt_stop_alarm_id 6
#define bt_clear_note_id 7
#define bt_add_note_id 8
#define bt_add_contact 9
#define bt_date 1

#define TextBufferSize 256

char FileBuffer[TextBufferSize];

HWND cap;
HWND cap1;
HWND edt_note;
HWND contactName_edt;
HWND intedt;
HWND menuhwnd;
HWND Contacthwnd;
HWND calendarStat;
HWND cap2;
HWND stat3;
HWND stat2;
HWND stat1;
HWND hMonthCal;

int timer_time = 0;
int count = 0;

HMENU ConSubMenu;
HMENU RootMenu;
HMENU FileSubMenu;


SYSTEMTIME st{};
TCHAR buf[100]{};
wchar_t filename[260];
OPENFILENAME ofn;

void MainWndAddMenus(HWND hwnd);
void SetOpenFileParams(HWND hwnd);
void SaveFile(LPCWSTR path);
void LoadFile(LPCWSTR path);