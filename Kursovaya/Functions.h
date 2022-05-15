#pragma once

void SaveFile(LPCWSTR path) {
	HANDLE FileToSave = CreateFile(
		path,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	int saveLength = GetWindowTextLength(edt_note) + 1;
	char* data = new char[saveLength];

	saveLength = GetWindowTextA(edt_note, data, saveLength);

	DWORD bytesIterated;
	WriteFile(FileToSave, data, saveLength, &bytesIterated, NULL);

	CloseHandle(FileToSave);
	delete[] data;
}

void LoadFile(LPCWSTR path) {
	HANDLE FileToLoad = CreateFile(
		path,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD bytesIterated;
	ReadFile(FileToLoad, FileBuffer, TextBufferSize, &bytesIterated, NULL);

	SetWindowTextA(edt_note, FileBuffer);

	CloseHandle(FileToLoad);
}

void SetOpenFileParams(HWND hwnd) {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = L"*.txt";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}

void MainWndAddMenus(HWND hwnd) {
	RootMenu = CreateMenu();
	FileSubMenu = CreateMenu();
	ConSubMenu = CreateMenu();

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)FileSubMenu, L"Note");
	AppendMenu(FileSubMenu, MF_STRING, OnMenuFileSave, L"Save");
	AppendMenu(FileSubMenu, MF_STRING, OnMenuFileLoad, L"Load");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)ConSubMenu, L"Contacts");
	AppendMenu(ConSubMenu, MF_POPUP, OnMenuDelete, L"Delete Last");

	SetMenu(hwnd, RootMenu);
}