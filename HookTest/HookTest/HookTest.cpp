// HookTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
// 全局变量
//LPDWORD		g_lpdwVirtualKey[9] = { 65,66,67,68,69,70,71,72,73 };		// Keycode 数组的指针
DWORD		g_lpdwVirtualKey[9] = { 65,66,67,68,69,70,71,72,73 };
int			g_nLength = 9;					// Keycode 数组的大小
BOOL		g_bDisableKeyboard = FALSE;		// 是否屏蔽整个键盘
HINSTANCE	g_hInstance = nullptr;				// 模块实例句柄
HHOOK		g_hHook = nullptr;					// 钩子句柄
                                                // 底层键盘钩子函数
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    // 禁用键盘的某个按键, 如果 g_bDisableKeyboard 为 TRUE 则禁用整个键盘
    if (nCode == HC_ACTION)
    {
        if (g_bDisableKeyboard)
        {
            return true;
        }
        KBDLLHOOKSTRUCT* pStruct = (KBDLLHOOKSTRUCT*)lParam;
        LPDWORD tmpVirtualKey = g_lpdwVirtualKey;
        for (int i = 0; i < g_nLength; i++)
        {
            if (pStruct->vkCode == *tmpVirtualKey++)
            {
                return true;
            }
        }

    }

    // 传给系统中的下一个钩子
    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

    
int main()
{
    g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, g_hInstance, 0);
    
    return 0;
}

