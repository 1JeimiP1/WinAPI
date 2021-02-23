#include <windows.h>
#define BUTTON_CHANGE 1001
#define BUTTON_WARN 1002
#define BUTTON_EXIT 1003

HWND hEdit;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM RegMyWindowClass(HINSTANCE, LPCTSTR);

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE         hPrevInstance,
    LPSTR             lpCmdLine,
    int               nCmdShow)
{
    // имя будущего класса
    LPCTSTR lpzClass = TEXT("My Window Class!");

    // регистрация класса
    if (!RegMyWindowClass(hInstance, lpzClass))
        return 1;

    // вычисление координат центра экрана
    RECT screen_rect;
    GetWindowRect(GetDesktopWindow(), &screen_rect); // разрешение экрана
    int x = screen_rect.right / 2 - 150;
    int y = screen_rect.bottom / 2 - 75;

    // создание диалогового окна
    HWND hWnd = CreateWindow(lpzClass, TEXT("Jeimip"),
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, x, y, 500, 350, NULL, NULL,
        hInstance, NULL);

    // если окно не создано, описатель будет равен 0
    if (!hWnd) return 2;

    // цикл сообщений приложения
    MSG msg = { 0 };    // структура сообщения
    int iGetOk = 0;   // переменная состояния
    while ((iGetOk = GetMessage(&msg, NULL, 0, 0)) != 0) // цикл сообщений
    {
        if (iGetOk == -1) return 3;  // если GetMessage вернул ошибку - выход
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;  // возвращаем код завершения программы
}

// функция регистрации класса окон
ATOM RegMyWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName)
{
    WNDCLASS wc = { 0 };
    // адрес ф-ции обработки сообщений
    wc.lpfnWndProc = (WNDPROC)WndProc;
    // стиль окна
    wc.style = CS_HREDRAW | CS_VREDRAW;
    // дискриптор экземпляра приложения
    wc.hInstance = hInst;
    // название класса
    wc.lpszClassName = lpzClassName;
    // загрузка курсора
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    // загрузка цвета окон
    wc.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
    return RegisterClass(&wc); 
}
 
LRESULT CALLBACK WndProc(
    HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{   
    TCHAR text[1024];
    GetWindowTextW(hEdit, text, 1024);
    switch (message)
    {
        case WM_COMMAND:
            switch (wParam)
            {
                case BUTTON_CHANGE:
                    SetWindowTextW(hWnd, text);
                    break;
                case BUTTON_WARN:
                    MessageBoxW(hWnd, text, L"Warning", MB_OK | MB_ICONINFORMATION);
                    break;
                case BUTTON_EXIT:
                    PostQuitMessage(EXIT_SUCCESS);
                    break;
            }
            break;
        case WM_CREATE:
            CreateWindow(TEXT("Button"), TEXT("Изменить"),
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                10, 10, 90, 35,
                hWnd, (HMENU)BUTTON_CHANGE, NULL, NULL
            );
            CreateWindow(TEXT("Button"), TEXT("Варн"),
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                10, 60, 90, 35,
                hWnd, (HMENU)BUTTON_WARN, NULL, NULL
            );
            CreateWindow(TEXT("Button"), TEXT("Закрыть"),
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                10, 110, 90, 35,
                hWnd, (HMENU)BUTTON_EXIT, NULL, NULL
            );
    
            hEdit = CreateWindow(TEXT("edit"), TEXT("..."),
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                120, 70, 120, 60, hWnd, (HMENU)2, NULL, NULL
            );
        
            //Createwindow(text("static"), null, // label tipo 
            //    ws_visible | ws_child,
            //    10, 170, 90, 22,
            //    hwnd, (hmenu)3, null, null
            //);
            break;
        case WM_LBUTTONUP:
            MessageBox(hWnd, TEXT("It's me"), TEXT("1987"), 0);
            break;
        case WM_DESTROY:
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
