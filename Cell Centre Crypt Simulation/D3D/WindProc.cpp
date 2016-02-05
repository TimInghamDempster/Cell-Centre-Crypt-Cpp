const wchar_t g_className[] = L"myWindowClass";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
			
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
			break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

HWND TCreateWindow(HINSTANCE hInstance)
{
    WNDCLASSEX wc;
    HWND hwnd;

	wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_className;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Window Registration Failed!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

	RECT  wrect;
	DWORD style = WS_BORDER;

	 // Define desired client size.
	wrect.left   = 0;
	wrect.top    = 0;
	wrect.right  = 1280;
	wrect.bottom = 720;
  
	AdjustWindowRect(&wrect,style,false);

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_className,
        L"Cell Centre Crypt Model",
        style,
		CW_USEDEFAULT, CW_USEDEFAULT, wrect.right, wrect.bottom,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
    }

	ShowWindow(hwnd, 5);
	UpdateWindow(hwnd);

	return hwnd;
}

int WINAPI TWinMain()
{
    MSG Msg;
	
	while(PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

    return 0;
}