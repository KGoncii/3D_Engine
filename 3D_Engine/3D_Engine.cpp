// 3D_Engine.cpp : Definiuje punkt wejścia dla aplikacji.
//

#include "pch.h"
#include "framework.h"
#include "3D_Engine.h"
#include <fstream>
#include <CommCtrl.h>

#define MAX_LOADSTRING 100

// Zmienne globalne:
HWND g_hComboBox;
HBITMAP g_hBitmap = NULL;
HWND g_hTextBox1, g_hTextBox2, g_hTextBox3, g_hTextBox4,g_hTextBox5, g_hTextBox6;
HINSTANCE hInst;  // bieżące wystąpienie
WCHAR szTitle[MAX_LOADSTRING];                  // Tekst paska tytułu
WCHAR szWindowClass[MAX_LOADSTRING];    
wchar_t selectedOption[256] = L"";// nazwa klasy okna głównego

// Przekaż dalej deklaracje funkcji dołączone w tym module kodu:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL CreateText(HWND hWnd);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: W tym miejscu umieść kod.

    // Inicjuj ciągi globalne
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY3DENGINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Wykonaj inicjowanie aplikacji:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3DENGINE));

    MSG msg;

    // Główna pętla komunikatów:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
   
    return (int) msg.wParam;
}



//
//  FUNKCJA: MyRegisterClass()
//
//  PRZEZNACZENIE: Rejestruje klasę okna.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3DENGINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY3DENGINE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKCJA: InitInstance(HINSTANCE, int)
//
//   PRZEZNACZENIE: Zapisuje dojście wystąpienia i tworzy okno główne
//
//   KOMENTARZE:
//
//        W tej funkcji dojście wystąpienia jest zapisywane w zmiennej globalnej i
//        jest tworzone i wyświetlane okno główne programu.
//
BOOL CreateComboBox(HWND hWnd) {
    g_hComboBox = CreateWindowW(WC_COMBOBOX, L"", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE | SS_CENTER,
        280, 260, 200, 100, hWnd, NULL, hInst, NULL);

    if (!g_hComboBox) {
        return FALSE;
    }

    // Dodaj przykładowe elementy do listy rozwijanej
    SendMessage(g_hComboBox, CB_ADDSTRING, 0, (LPARAM)L"1");
    SendMessage(g_hComboBox, CB_ADDSTRING, 1, (LPARAM)L"2");
    SendMessage(g_hComboBox, CB_ADDSTRING, 2, (LPARAM)L"3");
    SendMessage(g_hComboBox, CB_ADDSTRING, 3, (LPARAM)L"4");

    SendMessage(g_hComboBox, CB_SETCURSEL, 0, 0); // Ustawienie początkowej opcji wybranej

    return TRUE;
}
BOOL CreateTextBox(HWND hWnd) {
    g_hTextBox1 = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | SS_CENTER,
        360, 20, 200, 30, hWnd, NULL, hInst, NULL);

    if (!g_hTextBox1) {
        return FALSE;
    }
    g_hTextBox2 = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | SS_CENTER,
        360, 60, 200, 30, hWnd, NULL, hInst, NULL);

    if (!g_hTextBox2) {
        return FALSE;
    }
    
    g_hTextBox3 = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | SS_CENTER,
        360, 100, 200, 30, hWnd, NULL, hInst, NULL);

    if (!g_hTextBox3) {
        return FALSE;
    }
    g_hTextBox4 = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | SS_CENTER,
        360, 140, 200, 30, hWnd, NULL, hInst, NULL);

    if (!g_hTextBox4) {
        return FALSE;
    }
    g_hTextBox5 = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | SS_CENTER,
        360, 180, 200, 30, hWnd, NULL, hInst, NULL);

    if (!g_hTextBox5) {
        return FALSE;
    }
    g_hTextBox6 = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | SS_CENTER,
        360, 220, 200, 30, hWnd, NULL, hInst, NULL);

    if (!g_hTextBox6) {
        return FALSE;
    }

    return TRUE;
}
BOOL CreateText(HWND hWnd) {
    HWND hStatic1 = CreateWindowW(L"STATIC", L"Start", WS_VISIBLE | WS_CHILD | SS_CENTER,
        220, 20, 120, 30, hWnd, NULL, hInst, NULL);
    HWND hStatic2 = CreateWindowW(L"STATIC", L"Prędkość", WS_VISIBLE | WS_CHILD | SS_CENTER,
        220, 60, 120, 30, hWnd, NULL, hInst, NULL);
    HWND hStatic3 = CreateWindowW(L"STATIC", L"Przyśpieszenie", WS_VISIBLE | WS_CHILD | SS_CENTER,
        220, 100, 120, 30, hWnd, NULL, hInst, NULL);
    HWND hStatic4 = CreateWindowW(L"STATIC", L"Rotacja", WS_VISIBLE | WS_CHILD | SS_CENTER,
        220, 140, 120, 30, hWnd, NULL, hInst, NULL);
    HWND hStatic5 = CreateWindowW(L"STATIC", L"Masa", WS_VISIBLE | WS_CHILD | SS_CENTER,
        220, 180, 120, 30, hWnd, NULL, hInst, NULL);
    HWND hStatic6 = CreateWindowW(L"STATIC", L"Śr. Ciężkości", WS_VISIBLE | WS_CHILD | SS_CENTER,
        220, 220, 120, 30, hWnd, NULL, hInst, NULL);

    if (!hStatic1 || !hStatic2 || !hStatic3 || !hStatic4) {
        return FALSE;
    }

    return TRUE;
}

BOOL CreateButton(HWND hWnd) {
    HWND hButton1 = CreateWindowW(L"BUTTON", L"Zatwierdź", WS_VISIBLE | WS_CHILD | SS_CENTER | WS_BORDER,
        320, 300, 120, 30, hWnd, (HMENU)ID_BUTTON_DISPLAY_TEXT, hInst, NULL);

    if (!hButton1) {
        return FALSE;
    }

    return TRUE;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Przechowuj dojście wystąpienia w naszej zmiennej globalnej

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    if (!CreateTextBox(hWnd)) {
        return FALSE;
    }

    if (!CreateButton(hWnd)) {
        return FALSE;
    }
    if (!CreateText(hWnd)) {
        return FALSE;
    }
    if (!CreateComboBox(hWnd)) {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNKCJA: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PRZEZNACZENIE: Przetwarza komunikaty dla okna głównego.
//
//  WM_COMMAND  - przetwarzaj menu aplikacji
//  WM_PAINT    - Maluj okno główne
//  WM_DESTROY  - opublikuj komunikat o wyjściu i wróć
//
//
void SaveDataToFile(HWND hComboBox) {
    // Pobranie danych z pól tekstowych
    wchar_t buffer1[256];
    GetWindowText(g_hTextBox1, buffer1, 256);

    wchar_t buffer2[256];
    GetWindowText(g_hTextBox2, buffer2, 256);

    wchar_t buffer3[256];
    GetWindowText(g_hTextBox3, buffer3, 256);

    wchar_t buffer4[256];
    GetWindowText(g_hTextBox4, buffer4, 256);

    wchar_t buffer5[256];
    GetWindowText(g_hTextBox5, buffer5, 256);

    wchar_t buffer6[256];
    GetWindowText(g_hTextBox6, buffer6, 256);

    wchar_t selectedOption[256] = L"";
    int index = SendMessage(hComboBox, CB_GETCURSEL, 0, 0);
    if (index != CB_ERR) {
        SendMessage(hComboBox, CB_GETLBTEXT, index, (LPARAM)selectedOption);
    }

    // Otwarcie pliku w trybie zapisu
    std::wofstream file(L"dane.txt"); // Uwaga: Ta operacja nadpisze plik 'data.txt'
    // Sprawdzenie, czy plik został otwarty poprawnie
    if (file.is_open()) {
        // Zapisanie danych do pliku
        file << buffer1 << L"\n";
        file << buffer2 << L"\n";
        file << buffer3 << L"\n";
        file << buffer4 << L"\n";
        file << buffer5 << L"\n";
        file << buffer6 << L"\n";
        file << selectedOption << L"\n";
        MessageBox(g_hTextBox1, L"Pomyślnie przesłano dane", L"Gotowe", MB_OK);
        // Zamknięcie pliku
        file.close();
    }
    else {
        // Komunikat w przypadku błędu otwarcia pliku
        MessageBox(g_hTextBox1, L"Nie można otworzyć pliku!", L"Błąd", MB_OK | MB_ICONERROR);
    }
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
   
    case WM_COMMAND:
    {

        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;

        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case ID_BUTTON_DISPLAY_TEXT: // Dodaj identyfikator dla przycisku w pliku zasobów (resource.h)
        {
            SaveDataToFile(g_hComboBox);
        }
        break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
 
    case WM_SIZE: {
        // Tutaj możesz zmieniać rozmiar okna
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        // Zmiana rozmiaru okna na nowe wymiary (np. 800x600)
        SetWindowPos(hWnd, NULL, 0, 0, 800, 600, SWP_NOMOVE | SWP_NOZORDER);
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Definicja punktów kolorów dla gradientu
        TRIVERTEX vert[3] = {
    {0, 0, 0xBB00, 0xd200, 0xc500, 0x0000},     // Punkt 1 - kolor początkowy (RGBA: 0, 0, 0, 0)
    {800, 800, 0x5300, 0x6900, 0x7600, 0x0000}, // Punkt 2 - kolor środkowy (RGBA: 255, 255, 255, 0)
    {800, 800, 0x2900, 0x2e00, 0x4900, 0x0000}  // Punkt 3 - kolor końcowy (RGBA: 0, 255, 0, 0)
        };

        // Ustawienia gradientu
        GRADIENT_RECT gRect = { 0, 1};

        // Rysowanie gradientu
        GradientFill(hdc, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_H); // Dla poziomego gradientu

        EndPaint(hWnd, &ps);
    }
    break;
    
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
 default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Procedura obsługi komunikatów dla okna informacji o programie.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
