#include "Windows.h"
//에디트
#define IDC_EDIT 101
HWND g_hEdit;

//리스트 박스
#define IDC_LISTBOX  102
const TCHAR * item[] = { TEXT("사과"),TEXT("오렌지"),TEXT("메론"),TEXT("포도"),TEXT("딸기") };
HWND g_hList;

//콤보박스
#define IDC_COMBOBOX 103
HWND g_hCombo;

//스크롤바
#define IDC_SCRRED 104
#define IDC_SCRGREEN 105
#define IDC_SCRBLUE 106
HWND g_hRed, g_hGreen, g_hBlue;
int iRed, iBlue, iGreen;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//엔트리 포인트
//APIENTRY 지정자는 윈도우 표준 호출 규약인 __stdcall 을 사용한다는 의미

//함수 호출 방법(호출규약)
//__stdcall	:	매개변수의 개수가 고정된 함수	/ 크기가 작다	/	callee (피호출자) stack 정리
//__cdecl	:	매개변수의 개수가 가변적인 함수	/ 크기가 크다	/	caller (호출자) stack 정리

HINSTANCE g_hinst;

//매개변수
//hInstance		:현재 프로그램 인스턴스 핸들
//hPrevInstance	:이전에 실행시킨 같은 프로그램 인스턴스 핸들	(사용 x)
//IpszCmdparam	:명령행으로 입력된 프로그램 인수				(사용 x)
//nCmdShow		:프로그램이 실행 될 형태						(사용 x)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow) {
	g_hinst = hInstance;
	HWND	hWnd;		//윈도우 핸들러
	MSG		Msg;		//윈도우 메세지
	WNDCLASS	WndClass;	//윈도우 구조체

	//1.윈도우 클래스 설정/초기화
	WndClass.style = CS_HREDRAW | CS_VREDRAW;		//윈도우 스타일 정의, 가로나 세로가 늘어나면 다시 그리겠다.
	WndClass.cbClsExtra = 0;						//특수한 목적으로 사용될 예약 영역
	WndClass.cbWndExtra = 0;						//특수한 목적으로 사용될 예약 영역
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//하얀색으로 배경 설정
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		//마우스 커서 지정
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//아이콘 지정
	WndClass.hInstance = hInstance;						//윈도우 클래스를 등록하는 번호
	WndClass.lpfnWndProc = WndProc;					//프로시저 설정 (메세지 처리)
	WndClass.lpszClassName = TEXT("똑요비");		//윈도우 클레스 이름 (아무거나 가능 나중에 이름만 맞춰주면 됨)
	WndClass.lpszMenuName = NULL;				//프로그렘이 사용할 메뉴 설정

	//2.윈도우 클래스 등록
	RegisterClass(&WndClass);//윈도우 클래스의 주소값을 전달합니다. 사용하기위해

	//3. 윈도우 창 생성
	hWnd = CreateWindow(
		WndClass.lpszClassName,			   //클래스이름
		TEXT("똑요비"),					   //타이틀 이름
		WS_OVERLAPPEDWINDOW,			   //윈도우 창 스타일
		CW_USEDEFAULT,					   //시작 x 좌표
		CW_USEDEFAULT,					   //시작 y 좌표
		800,							   //윈도우 창 너비
		640,							   //윈도우 창 높이
		NULL,							   //부모 윈도우 핸들 지정
		NULL,							   //윈도우 메뉴 핸들 지정
		hInstance,						   //윈도우 식별자 지정
		NULL);							   //여러개의 윈도우를 만들때 파라미터를 구조체를 이용하여 전달하는 목적

	//4. 윈도우 칭 활성화 표시
	 //SW_HIDE				 /윈도우 숨기기
	 //SW_MINIMIZE			 /윈도우를 최소화 시키고 활성화 하지 않습니다.
	 //SW_RESTORE			 /윈도우 활성화 
	 //SW_SHOW				 /윈도우 활성화. 화면에 표시
	 //SW_SHOWNORMAL		 /윈도우 활성화 . 화면에 표시
	ShowWindow(hWnd, SW_SHOW);

	//5. 메세지루프/처리
	//GetMessage()		-	메세지 큐에서 메세지를 읽어드린 후 WM_QUIT이라면, FALSE를 반환 아니면 TRUE를 반환
	//						(메세지가 있을 때 까지 대기)
	//PeekMessage()		-	받을 메세지가 있다면 TURE 아니라면 FALSE 을 반환 (게임 프로그레밍에 적당)

	while (GetMessage(&Msg, NULL, 0, 0)) {
		TranslateMessage(&Msg);		//키보드 입력 메세지를 프로그램에서 사용할 수 있도록 변환
		DispatchMessage(&Msg);	//	메세지 큐에서 꺼낸메세지를 프로시저에 전달
	}

	return (int)Msg.wParam;
}

//콜백함수 매개변수
//hwnd			메세지를 받을 윈도우 핸들러
//msg			어떤 종류의 메세지인지 확인할 수 있는 값
//wParam		메세지의 부가정보 메세지마다 다름
//lParam		메세지의 부가정보 메세지마다 다름
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	TCHAR str[128];
	//리스트 변수
	int i;
	TCHAR strList[128];
	//콤보박스 변수
	TCHAR strComb[128];

	//스크롤바 변수
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH myBrush, oldBrush;
	int tempPos;

	switch (msg) {
	case WM_CREATE:
		//에디트 생성
		g_hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 10, 10, 200, 25, hwnd, (HMENU)IDC_EDIT, g_hinst, NULL);
		//리스트 생성
		g_hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY, 10, 40, 100, 200, hwnd, (HMENU)IDC_LISTBOX, g_hinst, NULL);
		//콤보박스 생성
		g_hCombo = CreateWindow(TEXT("comboBox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN, 120, 40, 100, 200, hwnd, (HMENU)IDC_COMBOBOX, g_hinst, NULL);

		//리스트, 콤보박스 아이템 추가
		for (int i = 0; i < 5; i++) {
			SendMessage(g_hList, LB_ADDSTRING, 0, (LPARAM)item[i]);
			SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)item[i]);
		}

		//수평 스크롤바 생성
		g_hRed = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 70, 250, 400, 20, hwnd, (HMENU)IDC_SCRRED, g_hinst, NULL);
		g_hGreen = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 70, 280, 400, 20, hwnd, (HMENU)IDC_SCRGREEN, g_hinst, NULL);
		g_hBlue = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 70, 310, 400, 20, hwnd, (HMENU)IDC_SCRBLUE, g_hinst, NULL);

		//스크롤바의 범위 설정 및 최초 위치선정
		//SB_HORZ, SB_VERT, SB_CTL(비표준), SB_BOTH -스크롤바
		SetScrollRange(g_hRed, SB_CTL, 0, 255, TRUE);
		SetScrollPos(g_hRed, SB_CTL, 0, TRUE);
		SetScrollRange(g_hGreen, SB_CTL, 0, 255, TRUE);
		SetScrollPos(g_hGreen, SB_CTL, 0, TRUE);
		SetScrollRange(g_hBlue, SB_CTL, 0, 255, TRUE);
		SetScrollPos(g_hBlue, SB_CTL, 0, TRUE);

		//스테틱 컨트롤
		CreateWindow(TEXT("static"), TEXT("Red"), WS_CHILD | WS_VISIBLE, 10, 250, 50, 25, hwnd, (HMENU)-1, g_hinst, NULL);
		CreateWindow(TEXT("static"), TEXT("Green"), WS_CHILD | WS_VISIBLE, 10, 280, 50, 25, hwnd, (HMENU)-1, g_hinst, NULL);
		CreateWindow(TEXT("static"), TEXT("Blue"), WS_CHILD | WS_VISIBLE, 10, 310, 50, 25, hwnd, (HMENU)-1, g_hinst, NULL);

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {//아이디 검사
		case IDC_COMBOBOX://콤보박스 이벤트 처리
			switch (HIWORD(wParam)) {//통지코드 검사
			case CBN_EDITCHANGE:
				GetWindowText(g_hCombo, strComb, 128);
				SetWindowText(hwnd, strComb);
				break;

			case CBN_SELCHANGE:
				i = SendMessage(g_hCombo, CB_GETCURSEL, 0, 0);
				SendMessage(g_hCombo, CB_GETLBTEXT, i, (LPARAM)strComb);
				SetWindowText(hwnd, strComb);
				break;

			}

			break;


		case IDC_LISTBOX://리스트 이벤트 처리

			switch (HIWORD(wParam)) {//통지 코드 검사

			case LBN_SELCHANGE:
				//사용자에 의해 항목이 변경되었을떄
				i = SendMessage(g_hList, LB_GETCURSEL, 0, 0);
				SendMessage(g_hList, LB_GETTEXT, i, (LPARAM)strList);//인덱스번째 텍스트를 가져와서 스트링 리스트에 저장
				SetWindowText(hwnd, strList);						//윈도우 텍스트 변경
				break;

			}
			return 0;

		case IDC_EDIT:
			switch (HIWORD(wParam)) {//통지 코드 검사

			case EN_CHANGE: //에디트의 문자열이 변경되었다면
				GetWindowText(g_hEdit, str, 128);
				SetWindowText(hwnd, str);
				break;
			}
			break;

		}
		return 0;
		//윈도우를 종료하려고 한다면
	case WM_HSCROLL:
		//현재 포지션값을 받음
		if ((HWND)lParam == g_hRed) tempPos = iRed;
		if ((HWND)lParam == g_hGreen) tempPos = iGreen;
		if ((HWND)lParam == g_hBlue) tempPos = iBlue;

		//이벤트처리
		switch (LOWORD(wParam)) {

		case SB_LINELEFT:
			tempPos = max(0, tempPos - 1);
			break;

		case SB_LINERIGHT:
			tempPos = min(tempPos + 1, 255);
			break;

		case SB_PAGELEFT:
			tempPos = max(0, tempPos - 10);
			break;

		case SB_PAGERIGHT:
			tempPos = min(255, tempPos + 10);
			break;

		case SB_THUMBTRACK:
			tempPos = HIWORD(wParam);
			break;
		}
		//포지션값으로 스크롤 위치 변경
		SetScrollPos((HWND)lParam, SB_CTL, tempPos, TRUE);
		InvalidateRect(hwnd, NULL, FALSE);

		//처리후 포지션값 저장
		if ((HWND)lParam == g_hRed)  iRed = tempPos;
		if ((HWND)lParam == g_hGreen)iGreen = tempPos;
		if ((HWND)lParam == g_hBlue)  iBlue = tempPos;

		return 0;

	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);
		myBrush = CreateSolidBrush(RGB(iRed, iGreen, iBlue));
		oldBrush = (HBRUSH)SelectObject(hdc, myBrush);
		Rectangle(hdc, 70, 340, 470, 540);
		DeleteObject(SelectObject(hdc, oldBrush));
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		//WM_QUIT 메세지를 발송
		PostQuitMessage(0);
		return 0;
	}

	//그 외의 메세지는 윈도우에서 알아서 처리하도록 설정
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
