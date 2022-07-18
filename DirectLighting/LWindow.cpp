#include "LWindow.h"

LWindow::LWindow()
{
}

LWindow::~LWindow()
{
}

bool LWindow::Init(HINSTANCE& _hInstance, int _showWnd, int _width, int _height, bool _windowed, WNDPROC _wndProc, LPCSTR _title)
{
  m_fullscreen = !_windowed;
  m_width = _width;
  m_height = _height;
  
  typedef struct _WNDCLASS {
    UINT cbSize;
    UINT style;
    WNDPROC lpfnWndProc;
    int cbClsExtra;
    int cbWndExtra;
    HANDLE hInstance;
    HICON hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    LPCTSTR lpszMenuName;
    LPCTSTR lpszClassName;
  } WNDCLASS;

  WNDCLASSEX wc;
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = _wndProc;
  wc.cbClsExtra = NULL;
  wc.cbWndExtra = NULL;
  wc.hInstance = _hInstance;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = m_WND_CLASS_NAME;
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  if (!RegisterClassEx(&wc))
  {
    MessageBox(NULL, "Error registering class",
      "Error", MB_OK | MB_ICONERROR);
    return false;
  }

  m_hwnd = CreateWindowEx(
    NULL,
    m_WND_CLASS_NAME,
    _title,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    _width, _height,
    NULL,
    NULL,
    _hInstance,
    NULL
  );

  if (!m_hwnd)
  {
    MessageBox(NULL, "Error creating window",
      "Error", MB_OK | MB_ICONERROR);
    return false;
  }

  ShowWindow(m_hwnd, _showWnd);
  UpdateWindow(m_hwnd);

  return true;
}
