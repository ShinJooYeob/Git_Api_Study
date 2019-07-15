#include "Windows.h"
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//��Ʈ�� ����Ʈ
//APIENTRY �����ڴ� ������ ǥ�� ȣ�� �Ծ��� __stdcall �� ����Ѵٴ� �ǹ�

//�Լ� ȣ�� ���(ȣ��Ծ�)
//__stdcall	:	�Ű������� ������ ������ �Լ�	/ ũ�Ⱑ �۴�	/	callee (��ȣ����) stack ����
//__cdecl	:	�Ű������� ������ �������� �Լ�	/ ũ�Ⱑ ũ��	/	caller (ȣ����) stack ����
HINSTANCE g_hinst;

//�Ű�����
//hInstance		:���� ���α׷� �ν��Ͻ� �ڵ�
//hPrevInstance	:������ �����Ų ���� ���α׷� �ν��Ͻ� �ڵ�	(��� x)
//IpszCmdparam	:��������� �Էµ� ���α׷� �μ�				(��� x)
//nCmdShow		:���α׷��� ���� �� ����						(��� x)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow) {

	g_hinst = hInstance;
	HWND	hWnd;		//������ �ڵ鷯
	MSG		Msg;		//������ �޼���
	WNDCLASS	WndClass;	//������ ����ü

	//1.������ Ŭ���� ����/�ʱ�ȭ
	WndClass.style = CS_HREDRAW | CS_VREDRAW;		//������ ��Ÿ�� ����, ���γ� ���ΰ� �þ�� �ٽ� �׸��ڴ�.
	WndClass.cbClsExtra = 0;						//Ư���� �������� ���� ���� ����
	WndClass.cbWndExtra = 0;						//Ư���� �������� ���� ���� ����
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//�Ͼ������ ��� ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		//���콺 Ŀ�� ����
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//������ ����
	WndClass.hInstance = hInstance;						//������ Ŭ������ ����ϴ� ��ȣ
	WndClass.lpfnWndProc = WndProc;					//���ν��� ���� (�޼��� ó��)
	WndClass.lpszClassName = TEXT("�ȿ��");		//������ Ŭ���� �̸� (�ƹ��ų� ���� ���߿� �̸��� �����ָ� ��)
	WndClass.lpszMenuName = NULL;				//���α׷��� ����� �޴� ����

	//2.������ Ŭ���� ���
	RegisterClass(&WndClass);//������ Ŭ������ �ּҰ��� �����մϴ�. ����ϱ�����

	//3. ������ â ����
	hWnd = CreateWindow(
		WndClass.lpszClassName,			   //Ŭ�����̸�
		TEXT("�ȿ��"),					   //Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW,			   //������ â ��Ÿ��
		CW_USEDEFAULT,					   //���� x ��ǥ
		CW_USEDEFAULT,					   //���� y ��ǥ
		800,							   //������ â �ʺ�
		640,							   //������ â ����
		NULL,							   //�θ� ������ �ڵ� ����
		NULL,							   //������ �޴� �ڵ� ����
		hInstance,						   //������ �ĺ��� ����
		NULL);							   //�������� �����츦 ���鶧 �Ķ���͸� ����ü�� �̿��Ͽ� �����ϴ� ����

	//4. ������ Ī Ȱ��ȭ ǥ��
	 //SW_HIDE				 /������ �����
	 //SW_MINIMIZE			 /�����츦 �ּ�ȭ ��Ű�� Ȱ��ȭ ���� �ʽ��ϴ�.
	 //SW_RESTORE			 /������ Ȱ��ȭ 
	 //SW_SHOW				 /������ Ȱ��ȭ. ȭ�鿡 ǥ��
	 //SW_SHOWNORMAL		 /������ Ȱ��ȭ . ȭ�鿡 ǥ��
	ShowWindow(hWnd, SW_SHOW);

	//5. �޼�������/ó��
	//GetMessage()		-	�޼��� ť���� �޼����� �о�帰 �� WM_QUIT�̶��, FALSE�� ��ȯ �ƴϸ� TRUE�� ��ȯ
	//						(�޼����� ���� �� ���� ���)
	//PeekMessage()		-	���� �޼����� �ִٸ� TURE �ƴ϶�� FALSE �� ��ȯ (���� ���α׷��ֿ� ����)

	while (GetMessage(&Msg, NULL, 0, 0)) {
		TranslateMessage(&Msg);		//Ű���� �Է� �޼����� ���α׷����� ����� �� �ֵ��� ��ȯ
		DispatchMessage(&Msg);	//	�޼��� ť���� �����޼����� ���ν����� ����
	}

	return (int)Msg.wParam;
}

//�ݹ��Լ� �Ű�����
//hwnd			�޼����� ���� ������ �ڵ鷯
//msg			� ������ �޼������� Ȯ���� �� �ִ� ��
//wParam		�޼����� �ΰ����� �޼������� �ٸ�
//lParam		�޼����� �ΰ����� �޼������� �ٸ�
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	static int posX, posY, oldX, oldY;
	static bool bDraw = false;
	HDC hdc;
	PAINTSTRUCT ps;

	static HBITMAP myBitmap;

	switch (msg) {
	case WM_CREATE:
		myBitmap = LoadBitmap(g_hinst, MAKEINTRESOURCE(IDB_TEST));
		return 0;

	case WM_PAINT: {

		hdc = BeginPaint(hwnd, &ps);
		//�޸� DC ����
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, myBitmap);
		BITMAP bit; // ��Ʈ�� ������ �˰������;
		int bWidth, bHeight;
		GetObject(myBitmap, sizeof(BITMAP), &bit);

		bWidth = bit.bmWidth;
		bHeight = bit.bmHeight;

		BitBlt(hdc, 10, 10, bWidth, bHeight, memDC, 0, 0, SRCCOPY);

		SelectObject(memDC, oldBitmap);
		DeleteDC(memDC);
		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_LBUTTONDOWN:
		posX = LOWORD(lParam);
		posY = HIWORD(lParam);
		oldX = posX;
		oldY = posY;
		bDraw = true;

		return 0;

	case WM_MOUSEMOVE:
		if (bDraw) {
			hdc = GetDC(hwnd);

			//�׸��� ��� ����
			SetROP2(hdc, R2_NOT);		//���� �׸��� �������Ѽ� �׸��� ������ ��ġ�� ������
			MoveToEx(hdc, posX, posY, NULL);
			LineTo(hdc, oldX, oldY);
			oldX = LOWORD(lParam);
			oldY = HIWORD(lParam);
			MoveToEx(hdc, posX, posY, NULL);
			LineTo(hdc, oldX, oldY);

			ReleaseDC(hwnd, hdc);
		}
		return 0;

	case WM_LBUTTONUP:
		bDraw = false;
		hdc = GetDC(hwnd);
		MoveToEx(hdc, posX, posY, NULL);
		LineTo(hdc, oldX, oldY);
		ReleaseDC(hwnd, hdc);
		return 0;




		//�����츦 �����Ϸ��� �Ѵٸ�
	case WM_DESTROY:
		//WM_QUIT �޼����� �߼�
		PostQuitMessage(0);
		DeleteObject(myBitmap);
		return 0;
	}

	//�� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
