#include "Windows.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//엔트리 포인트
//APIENTRY 지정자는 윈도우 표준 호출 규약인 __stdcall 을 사용한다는 의미

//함수 호출 방법(호출규약)
//__stdcall	:	매개변수의 개수가 고정된 함수	/ 크기가 작다	/	callee (피호출자) stack 정리
//__cdecl	:	매개변수의 개수가 가변적인 함수	/ 크기가 크다	/	caller (호출자) stack 정리


//매개변수
//hInstance		:현재 프로그램 인스턴스 핸들
//hPrevInstance	:이전에 실행시킨 같은 프로그램 인스턴스 핸들	(사용 x)
//IpszCmdparam	:명령행으로 입력된 프로그램 인수				(사용 x)
//nCmdShow		:프로그램이 실행 될 형태						(사용 x)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow) {

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
	PAINTSTRUCT ps;
	int i;
	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;

	switch (msg) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		for (int i = 0; i < 300; i += 5) {
			MoveToEx(hdc, 0, i, NULL);
			LineTo(hdc, 600, i);
		}
		//빨간 펜, 초록 브러쉬인 사각형
		MyBrush = CreateSolidBrush(RGB(0, 255, 0));
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
		MyPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		OldPen = (HPEN)SelectObject(hdc, MyPen);
		Rectangle(hdc, 20, 20, 150, 150);

		//빨간펜, 널 (null)브러쉬 원
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
		Ellipse(hdc, 220, 20, 350, 150);

		//널(null) 펜, 초록 브러쉬
		SelectObject(hdc, MyBrush);
		DeleteObject(SelectObject(hdc, GetStockObject(NULL_PEN)));
		Rectangle(hdc, 420, 20, 550, 150);

		//검정 파선, 바둑판 파랑 브러쉬 원
		DeleteObject(MyPen);
		DeleteObject(SelectObject(hdc, OldBrush));

		MyPen = CreatePen(PS_DASH, 1, RGB(0, 0, 0));
		MyBrush = CreateHatchBrush(HS_CROSS, RGB(0, 0, 255));

		SelectObject(hdc, MyPen);
		SelectObject(hdc, MyBrush);
		Ellipse(hdc, 20, 170, 150, 300);

		//1.(220,170,350,300)좌표에 PS_DASHDOT 파랑펜 /HS_DIAGCROSS 초록 브러쉬 원
		DeleteObject(SelectObject(hdc, OldBrush));
		DeleteObject(SelectObject(hdc, OldPen));
		MyPen = CreatePen(PS_DASH, 1, RGB(0, 0, 255));
		MyBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(0, 255, 0));
		SelectObject(hdc, MyPen);
		SelectObject(hdc, MyBrush);
		Ellipse(hdc, 220, 170, 350, 300);

		//2. (420,170,550,300)좌표에 PS_SOLID 초록펜/ HS_FDIAGONAL 빨강 브러쉬 사각형
		DeleteObject(SelectObject(hdc, OldBrush));
		DeleteObject(SelectObject(hdc, OldPen));
		MyPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		MyBrush = CreateHatchBrush(HS_FDIAGONAL, RGB(0, 255, 0));
		SelectObject(hdc, MyPen);
		SelectObject(hdc, MyBrush);
		Rectangle(hdc, 420, 170, 550, 300);




		DeleteObject(SelectObject(hdc, OldBrush));		//MYBrush를 해제
		DeleteObject(SelectObject(hdc, OldPen));
		DeleteObject(MyPen);
		DeleteObject(MyBrush);
		EndPaint(hwnd, &ps);

		return 0;



		//윈도우를 종료하려고 한다면
	case WM_DESTROY:
		//WM_QUIT 메세지를 발송
		PostQuitMessage(0);
		return 0;
	}

	//그 외의 메세지는 윈도우에서 알아서 처리하도록 설정
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
