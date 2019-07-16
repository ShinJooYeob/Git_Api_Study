#include "Windows.h"
//버튼 상수 설정
#define IDC_BUTTON_1			101
#define IDC_BUTTON_2			102

#define IDC_CHECBOX_BUTTON_1	103
#define IDC_CHECBOX_BUTTON_2	104
#define IDC_CHECBOX_BUTTON_3	105
#define IDC_CHECBOX_BUTTON_4	106

#define ID_RADIO_GROUP_1		107
#define ID_RADIO_GROUP_2		108

#define IDC_RADIO_BUTTON_1		109
#define IDC_RADIO_BUTTON_2		110
#define IDC_RADIO_BUTTON_3		111
#define IDC_RADIO_BUTTON_4		112
#define IDC_RADIO_BUTTON_5		113
#define IDC_RADIO_BUTTON_6		114

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
	HDC hdc;
	PAINTSTRUCT			ps;
	static HWND			c1, c2, c3, c4;
	static bool			bEllipse = false;
	static HWND			r1, r2, r3, r4, r5, r6;
	static int			graph = 0;
	static COLORREF		color = RGB(0, 0, 0);

	switch (msg) {
	case WM_CREATE:
		CreateWindow(TEXT("BUTTON"), TEXT("BUTTON1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 20, 100, 25,
			hwnd, (HMENU)IDC_BUTTON_1, g_hinst, NULL);

		CreateWindow(TEXT("BUTTON"), TEXT("BUTTON2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 50, 100, 25,
			hwnd, (HMENU)IDC_BUTTON_2, g_hinst, NULL);

		//체크박스 버튼 만들기
		c1 = CreateWindow(TEXT("BUTTON"), TEXT("원그리기"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 20, 80, 160, 25, hwnd,
			(HMENU)IDC_CHECBOX_BUTTON_1, g_hinst, NULL);//오토 상태이면 토글 안해도 자동적으로 체크가 가능
		c2 = CreateWindow(TEXT("BUTTON"), TEXT("종료 메세지 활성화"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 20, 110, 160, 25, hwnd,
			(HMENU)IDC_CHECBOX_BUTTON_2, g_hinst, NULL);
		c3 = CreateWindow(TEXT("BUTTON"), TEXT("3 State"), WS_CHILD | WS_VISIBLE | BS_3STATE, 20, 140, 160, 25, hwnd,
			(HMENU)IDC_CHECBOX_BUTTON_3, g_hinst, NULL);
		c4 = CreateWindow(TEXT("BUTTON"), TEXT("Auto 3 State"), WS_CHILD | WS_VISIBLE | BS_AUTO3STATE, 20, 170, 160, 25, hwnd,
			(HMENU)IDC_CHECBOX_BUTTON_4, g_hinst, NULL);

		//라디오 그룹 만들기
		CreateWindow(TEXT("BUTTON"), TEXT("도형"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 200, 120, 110, hwnd,
			(HMENU)ID_RADIO_GROUP_1, g_hinst, NULL);
		CreateWindow(TEXT("BUTTON"), TEXT("색상"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 145, 200, 120, 110, hwnd,
			(HMENU)ID_RADIO_GROUP_2, g_hinst, NULL);

		//라디오 버튼 만들기
		r1 = CreateWindow(TEXT("BUTTON"), TEXT("사각형"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 10, 215, 100, 30, hwnd,
			(HMENU)IDC_RADIO_BUTTON_1, g_hinst, NULL);
		r2 = CreateWindow(TEXT("BUTTON"), TEXT("원"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 245, 100, 30, hwnd,
			(HMENU)IDC_RADIO_BUTTON_2, g_hinst, NULL);
		r3 = CreateWindow(TEXT("BUTTON"), TEXT("선"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 275, 100, 30, hwnd,
			(HMENU)IDC_RADIO_BUTTON_3, g_hinst, NULL);
		r4 = CreateWindow(TEXT("BUTTON"), TEXT("검정"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 215, 100, 30, hwnd,
			(HMENU)IDC_RADIO_BUTTON_4, g_hinst, NULL);
		r5 = CreateWindow(TEXT("BUTTON"), TEXT("빨강"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 245, 100, 30, hwnd,
			(HMENU)IDC_RADIO_BUTTON_5, g_hinst, NULL);
		r6 = CreateWindow(TEXT("BUTTON"), TEXT("파랑"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 275, 100, 30, hwnd,
			(HMENU)IDC_RADIO_BUTTON_6, g_hinst, NULL);

		CheckRadioButton(hwnd, IDC_RADIO_BUTTON_1, IDC_RADIO_BUTTON_3, IDC_RADIO_BUTTON_1);
		CheckRadioButton(hwnd, IDC_RADIO_BUTTON_4, IDC_RADIO_BUTTON_6, IDC_RADIO_BUTTON_4);
		return 0;



		//버튼을 누를 경우 윈도우 메세지 커멘트 메세지가 발송됨
	case WM_COMMAND:
		switch (LOWORD(wParam)) {//wParam을 참조하면 버튼의 아이디 값을 받을 수 있다
		//버튼 푸시 이벤트 처리
		case IDC_BUTTON_1:
			MessageBox(hwnd, TEXT("1번째 버튼 클릭"), TEXT("알림"), MB_OK);
			break;
		case IDC_BUTTON_2:
			MessageBox(hwnd, TEXT("2번째 버튼 클릭"), TEXT("알림"), MB_OK);
			//체크박스 처리
		case IDC_CHECBOX_BUTTON_1://BM_GETCHECK 눌렷는지 확인할 수 있음
			if (SendMessage(c1, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessage(c1, BM_SETCHECK, BST_CHECKED, 0);
				bEllipse = true;
			}
			else {
				SendMessage(c1, BM_SETCHECK, BST_UNCHECKED, 0);
				bEllipse = false;
			}
			break;

		case IDC_CHECBOX_BUTTON_3:
			if (SendMessage(c3, BM_GETCHECK, 0, 0) == BST_UNCHECKED) {
				SendMessage(c3, BM_SETCHECK, BST_CHECKED, 0);
			}
			else if (SendMessage(c3, BM_GETCHECK, 0, 0) == BST_INDETERMINATE) {
				SendMessage(c3, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			else SendMessage(c3, BM_SETCHECK, BST_INDETERMINATE, 0);
			break;


			//라디오 버튼 이벤트 처리
		case IDC_RADIO_BUTTON_1: graph = 0; break;
		case IDC_RADIO_BUTTON_2: graph = 1; break;
		case IDC_RADIO_BUTTON_3: graph = 2; break;

		case IDC_RADIO_BUTTON_4: color = RGB(0, 0, 0); break;
		case IDC_RADIO_BUTTON_5: color = RGB(255, 0, 0); break;
		case IDC_RADIO_BUTTON_6: color = RGB(0, 0, 255); break;

		}
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;



	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//체크 박스 이벤트 그리기
		if (bEllipse)	Ellipse(hdc, 200, 100, 400, 200);
		else Rectangle(hdc, 200, 100, 400, 200);

		//라디오 버튼 이벤트 도형 그리기
		HBRUSH myBrush, OldBrush;
		myBrush = CreateSolidBrush(color);
		OldBrush = (HBRUSH)SelectObject(hdc, myBrush);

		switch (graph) {
		case 0: Rectangle(hdc, 300, 210, 500, 310); break;
		case 1: Ellipse(hdc, 300, 210, 500, 310); break;
		case 2: MoveToEx(hdc, 300, 210, NULL); LineTo(hdc, 500, 310); break;
		}


		DeleteObject(SelectObject(hdc, OldBrush));
		EndPaint(hwnd, &ps);
		return 0;


		//윈도우를 종료하려고 한다면
	case WM_DESTROY:
		if (SendMessage(c2, BM_GETCHECK, 0, 0) == BST_CHECKED) {
			MessageBox(hwnd, TEXT("Bye Bye"), TEXT("종료 알림"), MB_OK);
		}
		//WM_QUIT 메세지를 발송
		PostQuitMessage(0);
		return 0;
	}

	//그 외의 메세지는 윈도우에서 알아서 처리하도록 설정
	return DefWindowProc(hwnd, msg, wParam, lParam);
}