#include "Windows.h"
//����Ʈ
#define IDC_EDIT 101
HWND g_hEdit;

//����Ʈ �ڽ�
#define IDC_LISTBOX  102
const TCHAR * item[] = { TEXT("���"),TEXT("������"),TEXT("�޷�"),TEXT("����"),TEXT("����") };
HWND g_hList;

//�޺��ڽ�
#define IDC_COMBOBOX 103
HWND g_hCombo;

//��ũ�ѹ�
#define IDC_SCRRED 104
#define IDC_SCRGREEN 105
#define IDC_SCRBLUE 106
HWND g_hRed, g_hGreen, g_hBlue;
int iRed, iBlue, iGreen;

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
	TCHAR str[128];
	//����Ʈ ����
	int i;
	TCHAR strList[128];
	//�޺��ڽ� ����
	TCHAR strComb[128];

	//��ũ�ѹ� ����
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH myBrush, oldBrush;
	int tempPos;

	switch (msg) {
	case WM_CREATE:
		//����Ʈ ����
		g_hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 10, 10, 200, 25, hwnd, (HMENU)IDC_EDIT, g_hinst, NULL);
		//����Ʈ ����
		g_hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY, 10, 40, 100, 200, hwnd, (HMENU)IDC_LISTBOX, g_hinst, NULL);
		//�޺��ڽ� ����
		g_hCombo = CreateWindow(TEXT("comboBox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN, 120, 40, 100, 200, hwnd, (HMENU)IDC_COMBOBOX, g_hinst, NULL);

		//����Ʈ, �޺��ڽ� ������ �߰�
		for (int i = 0; i < 5; i++) {
			SendMessage(g_hList, LB_ADDSTRING, 0, (LPARAM)item[i]);
			SendMessage(g_hCombo, CB_ADDSTRING, 0, (LPARAM)item[i]);
		}

		//���� ��ũ�ѹ� ����
		g_hRed = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 70, 250, 400, 20, hwnd, (HMENU)IDC_SCRRED, g_hinst, NULL);
		g_hGreen = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 70, 280, 400, 20, hwnd, (HMENU)IDC_SCRGREEN, g_hinst, NULL);
		g_hBlue = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ, 70, 310, 400, 20, hwnd, (HMENU)IDC_SCRBLUE, g_hinst, NULL);

		//��ũ�ѹ��� ���� ���� �� ���� ��ġ����
		//SB_HORZ, SB_VERT, SB_CTL(��ǥ��), SB_BOTH -��ũ�ѹ�
		SetScrollRange(g_hRed, SB_CTL, 0, 255, TRUE);
		SetScrollPos(g_hRed, SB_CTL, 0, TRUE);
		SetScrollRange(g_hGreen, SB_CTL, 0, 255, TRUE);
		SetScrollPos(g_hGreen, SB_CTL, 0, TRUE);
		SetScrollRange(g_hBlue, SB_CTL, 0, 255, TRUE);
		SetScrollPos(g_hBlue, SB_CTL, 0, TRUE);

		//����ƽ ��Ʈ��
		CreateWindow(TEXT("static"), TEXT("Red"), WS_CHILD | WS_VISIBLE, 10, 250, 50, 25, hwnd, (HMENU)-1, g_hinst, NULL);
		CreateWindow(TEXT("static"), TEXT("Green"), WS_CHILD | WS_VISIBLE, 10, 280, 50, 25, hwnd, (HMENU)-1, g_hinst, NULL);
		CreateWindow(TEXT("static"), TEXT("Blue"), WS_CHILD | WS_VISIBLE, 10, 310, 50, 25, hwnd, (HMENU)-1, g_hinst, NULL);

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {//���̵� �˻�
		case IDC_COMBOBOX://�޺��ڽ� �̺�Ʈ ó��
			switch (HIWORD(wParam)) {//�����ڵ� �˻�
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


		case IDC_LISTBOX://����Ʈ �̺�Ʈ ó��

			switch (HIWORD(wParam)) {//���� �ڵ� �˻�

			case LBN_SELCHANGE:
				//����ڿ� ���� �׸��� ����Ǿ�����
				i = SendMessage(g_hList, LB_GETCURSEL, 0, 0);
				SendMessage(g_hList, LB_GETTEXT, i, (LPARAM)strList);//�ε�����° �ؽ�Ʈ�� �����ͼ� ��Ʈ�� ����Ʈ�� ����
				SetWindowText(hwnd, strList);						//������ �ؽ�Ʈ ����
				break;

			}
			return 0;

		case IDC_EDIT:
			switch (HIWORD(wParam)) {//���� �ڵ� �˻�

			case EN_CHANGE: //����Ʈ�� ���ڿ��� ����Ǿ��ٸ�
				GetWindowText(g_hEdit, str, 128);
				SetWindowText(hwnd, str);
				break;
			}
			break;

		}
		return 0;
		//�����츦 �����Ϸ��� �Ѵٸ�
	case WM_HSCROLL:
		//���� �����ǰ��� ����
		if ((HWND)lParam == g_hRed) tempPos = iRed;
		if ((HWND)lParam == g_hGreen) tempPos = iGreen;
		if ((HWND)lParam == g_hBlue) tempPos = iBlue;

		//�̺�Ʈó��
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
		//�����ǰ����� ��ũ�� ��ġ ����
		SetScrollPos((HWND)lParam, SB_CTL, tempPos, TRUE);
		InvalidateRect(hwnd, NULL, FALSE);

		//ó���� �����ǰ� ����
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
		//WM_QUIT �޼����� �߼�
		PostQuitMessage(0);
		return 0;
	}

	//�� ���� �޼����� �����쿡�� �˾Ƽ� ó���ϵ��� ����
	return DefWindowProc(hwnd, msg, wParam, lParam);
}
