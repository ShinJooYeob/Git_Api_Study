#include "Windows.h"
#include "resource.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//��Ʈ�� ����Ʈ
//APIENTRY �����ڴ� ������ ǥ�� ȣ�� �Ծ��� __stdcall �� ����Ѵٴ� �ǹ�

//�Լ� ȣ�� ���(ȣ��Ծ�)
//__stdcall	:	�Ű������� ������ ������ �Լ�	/ ũ�Ⱑ �۴�	/	callee (��ȣ����) stack ����
//__cdecl	:	�Ű������� ������ �������� �Լ�	/ ũ�Ⱑ ũ��	/	caller (ȣ����) stack ����
HINSTANCE g_hinst;
int x;
int y;
TCHAR str[128];

//�Ű�����
//hInstance		:���� ���α׷� �ν��Ͻ� �ڵ�
//hPrevInstance	:������ �����Ų ���� ���α׷� �ν��Ͻ� �ڵ�	(��� x)
//IpszCmdparam	:��������� �Էµ� ���α׷� �μ�				(��� x)
//nCmdShow		:���α׷��� ���� �� ����						(��� x)
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow) {

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

BOOL CALLBACK infoDigProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
		SetDlgItemText(hwnd, IDC_EDITSTR, str);
		SetDlgItemInt(hwnd, IDC_EDITX, x, FALSE);
		SetDlgItemInt(hwnd, IDC_EDITY, y, FALSE);

		return true;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTONOK:
			GetDlgItemText(hwnd, IDC_EDITSTR, str, 128);//IDC_EDITSTR���� ������ str�� ����
			x = GetDlgItemInt(hwnd, IDC_EDITX, NULL, FALSE);//IDC_EDITX���� ���� ������
			y = GetDlgItemInt(hwnd, IDC_EDITY, NULL, FALSE);//IDC_EDITY���� ���� ������
			EndDialog(hwnd, IDOK);
			break;
		case IDC_BUTTONCANCLE:
			EndDialog(hwnd, IDCANCEL);

			break;
		}

		return true;
	}

	return FALSE;
}


//�ݹ��Լ� �Ű�����
//hwnd			�޼����� ���� ������ �ڵ鷯
//msg			� ������ �޼������� Ȯ���� �� �ִ� ��
//wParam		�޼����� �ΰ����� �޼������� �ٸ�
//lParam		�޼����� �ΰ����� �޼������� �ٸ�
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg) {
	case WM_LBUTTONDOWN:
		if (DialogBox(g_hinst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, infoDigProc) == IDOK) {
			InvalidateRect(hwnd, NULL, TRUE);
		}

		return 0;
	case WM_CREATE:
		x = 100;
		y = 100;
		lstrcpy(str, TEXT("���ڿ��� �Է����ּ���."));
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, x, y, str, lstrlen(str));
		EndPaint(hwnd, &ps);
		return 0;

		//�����츦 �����Ϸ��� �Ѵٸ�
	case WM_DESTROY:
		//WM_QUIT �޼����� �߼�
		PostQuitMessage(0);
		return 0;
	}

	//�� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
