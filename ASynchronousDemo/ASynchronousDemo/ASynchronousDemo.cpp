// ASynchronousDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#pragma comment(lib,"user32")
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>
#include <windows.h>

#define _CRT_SECURE_NO_WARNINGS

char datestr[16];
char timestr[16];
char mss[4];
void log(char *s) 
{
    struct tm now;
    struct timeb tb;

    ftime(&tb);
    localtime_s(&now,&tb.time);
    sprintf_s(datestr, "%04d-%02d-%02d", now.tm_year + 1900, now.tm_mon + 1, now.tm_mday);
    sprintf_s(timestr, "%02d:%02d:%02d", now.tm_hour, now.tm_min, now.tm_sec);
    sprintf_s(mss, "%03d", tb.millitm);
    printf("%s %s.%s %s", datestr, timestr, mss, s);
}
VOID CALLBACK myTimerProc1(
    HWND hwnd, // handle of window for timer messages
    UINT uMsg, // WM_TIMER message
    UINT idEvent, // timer identifier
    DWORD dwTime // current system time
) {
    log("In myTimerProc1\n");
}
VOID CALLBACK myTimerProc2(
    HWND hwnd, // handle of window for timer messages
    UINT uMsg, // WM_TIMER message
    UINT idEvent, // timer identifier
    DWORD dwTime // current system time
) {
    log("In myTimerProc2\n");
}
int main() 
{
    int i;
    MSG msg;

    SetTimer(NULL, 0, 1000, myTimerProc1);
    SetTimer(NULL, 0, 2000, myTimerProc2);
    for (i = 0; i<20; i++) 
    {
        Sleep(500);
        log("In main\n");
        if (GetMessage(&msg, NULL, 0, 0)) 
        {
            TranslateMessage(&msg);
             DispatchMessage(&msg);
        }

    }
    getchar();
    return 0;
}

