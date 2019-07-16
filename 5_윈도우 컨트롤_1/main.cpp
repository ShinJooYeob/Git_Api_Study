#include "Windows.h"
//��ư ��� ����
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

		//üũ�ڽ� ��ư �����
		c1 = CreateWindow(TEXT("BUTTON"), TEXT("���׸���"), WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 20, 80, 160, 25, hwnd,
			(HMENU)IDC_CHECBOX_BUTTON_1, g_hinst, NULL);//���� �����̸� ��� ���ص� �ڵ������� üũ�� ����
		c2 = CreateWindow(TEXT("BUTTON"), TEXT("���� �޼��� Ȱ��ȭ"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 20, 110, 160, 25, hwnd,
			(HMENU)IDC_CHECBOX_BUTTON_2, g_hinst, NULL);
		c3 = CreateWindow(TEXT("BUTTON"), TEXT("3 State"), WS_CHILD | WS_VISIBLE | BS_3STATE, 20, 140, 160, 25, hwnd,
			(HMENU)IDC_CHECBOX_BUTTON_3, g_hinst, NULL);
		c4 = CreateWindow(TEXT("BUTTON"), TEXT("Auto 3 State"), WS_CHILD | WS_VISIBLE | BS_AUTO3STATE, 20, 170, 160, 25, hwnd,
			(HMENU)IDC_CHECBOX_BUTTON_4, g_hinst, NULL);

		//���� �׷� �����
		CreateWindow(TEXT("BUTTON"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 200, 120, 110, hwnd,
			(HMENU)ID_RADIO_GROUP_1, g_hinst, NULL);
		CreateWindow(TEXT("BUTTON"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 145, 200, 120, 110, hwnd,
			(HMENU)ID_RADIO_GROUP_2, g_hinst, NULL);

		//���� ��ư �����
		r1 = CreateWindow(TEXT("BUTTON"), TEXT("�簢��"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 10, 215, 100, 30, hwnd,
			(HMENU)IDC_RADIO_BUTTON_1, g_hinst, NULL);
		r2 = CreateWindow(TEXT("BUTTON"), TEXT("��"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 245, 100, 30, hwnd,
			(HMENU)IDC_RADIO_BUTTON_2, g_hinst, NULL);
		r3 = CreateWindow(TEXT("BUTTON"), TEXT("��"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 10, 275, 100, 30, hwnd,
			(HMENU)IDC_RADIO_BUTTON_3, g_hinst, NULL);
		r4 = CreateWindow(TEXT("BUTTON"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 215, 100, 30, hwnd,
			(HMENU)IDC_RADIO_BUTTON_4, g_hinst, NULL);
		r5 = CreateWindow(TEXT("BUTTON"), TEXT("����"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 245, 100, 30, hwnd,
			(HMENU)IDC_RADIO_BUTTON_5, g_hinst, NULL);
		r6 = CreateWindow(TEXT("BUTTON"), TEXT("�Ķ�"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 275, 100, 30, hwnd,
			(HMENU)IDC_RADIO_BUTTON_6, g_hinst, NULL);

		CheckRadioButton(hwnd, IDC_RADIO_BUTTON_1, IDC_RADIO_BUTTON_3, IDC_RADIO_BUTTON_1);
		CheckRadioButton(hwnd, IDC_RADIO_BUTTON_4, IDC_RADIO_BUTTON_6, IDC_RADIO_BUTTON_4);
		return 0;



		//��ư�� ���� ��� ������ �޼��� Ŀ��Ʈ �޼����� �߼۵�
	case WM_COMMAND:
		switch (LOWORD(wParam)) {//wParam�� �����ϸ� ��ư�� ���̵� ���� ���� �� �ִ�
		//��ư Ǫ�� �̺�Ʈ ó��
		case IDC_BUTTON_1:
			MessageBox(hwnd, TEXT("1��° ��ư Ŭ��"), TEXT("�˸�"), MB_OK);
			break;
		case IDC_BUTTON_2:
			MessageBox(hwnd, TEXT("2��° ��ư Ŭ��"), TEXT("�˸�"), MB_OK);
			//üũ�ڽ� ó��
		case IDC_CHECBOX_BUTTON_1://BM_GETCHECK ���Ǵ��� Ȯ���� �� ����
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


			//���� ��ư �̺�Ʈ ó��
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
		//üũ �ڽ� �̺�Ʈ �׸���
		if (bEllipse)	Ellipse(hdc, 200, 100, 400, 200);
		else Rectangle(hdc, 200, 100, 400, 200);

		//���� ��ư �̺�Ʈ ���� �׸���
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


		//�����츦 �����Ϸ��� �Ѵٸ�
	case WM_DESTROY:
		if (SendMessage(c2, BM_GETCHECK, 0, 0) == BST_CHECKED) {
			MessageBox(hwnd, TEXT("Bye Bye"), TEXT("���� �˸�"), MB_OK);
		}
		//WM_QUIT �޼����� �߼�
		PostQuitMessage(0);
		return 0;
	}

	//�� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hwnd, msg, wParam, lParam);
}