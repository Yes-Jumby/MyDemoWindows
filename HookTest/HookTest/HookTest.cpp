// HookTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
// ȫ�ֱ���
//LPDWORD		g_lpdwVirtualKey[9] = { 65,66,67,68,69,70,71,72,73 };		// Keycode �����ָ��
DWORD		g_lpdwVirtualKey[9] = { 65,66,67,68,69,70,71,72,73 };
int			g_nLength = 9;					// Keycode ����Ĵ�С
BOOL		g_bDisableKeyboard = FALSE;		// �Ƿ�������������
HINSTANCE	g_hInstance = nullptr;				// ģ��ʵ�����
HHOOK		g_hHook = nullptr;					// ���Ӿ��
                                                // �ײ���̹��Ӻ���
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    // ���ü��̵�ĳ������, ��� g_bDisableKeyboard Ϊ TRUE �������������
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

    // ����ϵͳ�е���һ������
    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

    
int main()
{
    g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, g_hInstance, 0);
    
    return 0;
}

