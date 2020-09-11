// Win32Thread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<Windows.h>
#include<stdio.h>

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
    HANDLE hThread;
    DWORD  threadId;
    int a = sizeof(DWORD);
    for (int i = 0; i < 5; i++)
    {
        hThread = CreateThread(NULL,
            0,
            ThreadFunc,
            (LPVOID)i,
            0,
            &threadId);
        if (hThread)
        {
            printf("Thread launched %d\n", i);
            CloseHandle(hThread);
        }
    }
    Sleep(8000);
    //GetExitCodeThread();
    return 0;
}

DWORD WINAPI ThreadFunc(LPVOID p)
{
    int n;
    for (n = 0; n<100; n++)
        printf("%d%d%d%d%d%d%d%d\n", n, n, n, n, n, n, n, n);
    printf("Thread Completed %d\n", (int)p);
    return 0;
#
}

