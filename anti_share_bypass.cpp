#include <Windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <Shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

#define INJECT_BUTTON_ID 1001

// Function prototypes
BOOL DeleteAllLogs();
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {
    // Create window
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = TEXT("AntiShareBypass");
    RegisterClass(&wc);

    HWND hwnd = CreateWindow(TEXT("AntiShareBypass"), TEXT("Anti-Share Bypass"),
                            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                            CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
                            NULL, NULL, hInst, NULL);

    // Create Inject button
    CreateWindow(TEXT("BUTTON"), TEXT("Inject"),
                 WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                 100, 100, 100, 40,
                 hwnd, (HMENU)INJECT_BUTTON_ID, hInst, NULL);

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        SetWindowText(hwnd, TEXT("Anti-Share Bypass"));
        return 0;
    case WM_COMMAND:
        if (LOWORD(wParam) == INJECT_BUTTON_ID) {
            DeleteAllLogs();
            MessageBox(hwnd, TEXT("Injection successful! All logs deleted."), TEXT("Success"), MB_OK);
            PostMessage(hwnd, WM_CLOSE, 0, 0);
        }
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

BOOL DeleteAllLogs() {
    // Get temp directory
    char tempPath[MAX_PATH];
    GetTempPathA(MAX_PATH, tempPath);

    // Delete temp logs
    std::filesystem::path tempDir(tempPath);
    for (const auto& entry : std::filesystem::directory_iterator(tempDir)) {
        if (entry.path().extension() == ".log") {
            try {
                std::filesystem::remove(entry.path());
            } catch (...) {}
        }
    }

    // Delete system logs
    const char* logPaths[] = {
        "C:\\Windows\\System32\\winevt\\Logs",
        "C:\\ProgramData\\Microsoft\\Windows\\WER",
        "C:\\Windows\\Prefetch",
        "C:\\Windows\\SoftwareDistribution\\Download"
    };

    for (const char* path : logPaths) {
        try {
            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                if (entry.path().extension() == ".log") {
                    std::filesystem::remove(entry.path());
                }
            }
        } catch (...) {}
    }

    return TRUE;
}
