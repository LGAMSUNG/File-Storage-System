// ���� ����� ���� ������Ʈ 
// ���߱Ⱓ : 2019.01.05 ~ 

// ��� : (* ���� �Ϸ�) 
// ���� ����*, �б�*, ����, ����

// ���� �޸�
/**
1. ���� �ʱ�ȭ �ϱ�
2. �ڵ����� .txt�� ��ȯ
		���̰� �ʹ� ����� ����� �ϼ�
			�� ini���� ���
3. ���� / ���� ����
		������ ����
4. �����
10. ���� �ý����� ���ڷ� �޴°� �ƴ϶� Ű����� �ޱ�
		�� ���θ޴�, ���� ����(�Լ��� ���� �ϳ��ϳ� ������ ��;),


***hangaram.s180003@ggm.goe.go.kr***
**/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>


#define MAX_STR_SIZE 256

#define UP 72
#define DOWN 80
#define SUBMIT 32

#define FIRST_FILE 0
#define SECOND_FILE 1
#define THIRTH_FILE 2
#define FOURTH_FILE 3
#define FIVTH_FILE 4
#define EXIT 5

//------------------------------------------------------------ variable

FILE* fp;

int i, j;
int choice_work;	// ��� ����
int choice_file;	// ���� ����
int file_true_flag[5] = { 0,0,0,0,0 };	// �� ����� ���� ����

char* inside_data[256];		// �߰� ���� ���� 
char* fname[50];			// ���� �̸�
char* file_name[5][20] = { NULL };		// ���� �̸� 2���� �迭
char str_read[MAX_STR_SIZE];

//------------------------------------------------------------- funsion

// �Լ� ����
void init();
int KeyControl();
void titleDraw();
int menuDraw();
void ListDraw();
int ListCtrl();
void gotoxy(int x, int y);
int Create_File(choice_file_num);

// �ܼ�â ũ��, �̸�
void init() {
	system("mode con cols=110 lines=30 | title ���������");
}

// ���� ��Ʈ�� �Լ�
int KeyControl() {
	if (_kbhit()) {
		char temp = _getch();
		if (temp == 224 || temp == 0) {
			temp = _getch();
			if (temp == UP) return UP;
			else if (temp == DOWN) return DOWN;
			else if (temp == ' ') return SUBMIT;
		}
	}
}

// �� �׸���
void tipDraw() {
	gotoxy(47, 2);
	printf("______________________T I P________________________");
	gotoxy(45, 4);
	printf("�� ���α׷��� ���� ����, ���, ������ ���� �ý��۵Ǿ��ֽ��ϴ�.");
	gotoxy(45, 6);
	printf("���ϴ� ������ �����Ͻð� �װ��� ������ ����,���,������");
	gotoxy(45, 7);
	printf("�Ͻ� �� �ֽ��ϴ�.");
}

// ���� �׸���
void titleDraw() {
	printf("");
	printf(" ######      ######      ######\n");
	printf(" #          #           #\n");
	printf(" #####       #####       #####\n");
	printf(" #                #           #\n");
	printf(" #          ######      ######\n\n");
	printf("   File Storage System\n");
}

// ���� ����Ʈ �׸���
void ListDraw() {
	int x = 2;
	int y = 12;
	printf_s("\n\n ��������������������������������������������������\n");
	printf_s("|  NUM |  NAME             |\n");
	gotoxy(x - 2, y);
	printf_s("> 1.     %s", file_name[0]);
	gotoxy(x, y + 1);
	printf_s("2.     %s", file_name[1]);
	gotoxy(x, y + 2);
	printf_s("3.     %s", file_name[2]);
	gotoxy(x, y + 3);
	printf_s("4.     %s", file_name[3]);
	gotoxy(x, y + 4);
	printf_s("5.     %s", file_name[4]);
	gotoxy(x, y + 5);
	printf_s("         EXIT\n");
	printf_s("��������������������������������������������������");

	gotoxy(2, 21);
	printf_s("[ SYS LOG ]\n");
}

// ���� ����Ʈ ��Ʈ�� �Լ�
int ListCtrl() {
	int x = 2;
	int y = 12;

	ListDraw();

	while (1) {

		int n = KeyControl();
		switch (n) {
		case UP:
			if (y > 12) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
				break;
			}

		case DOWN:
			if (y < 17) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
				break;
			}

		case SUBMIT:
			return y-12;
		}
	}
}

// �ܼ� �� Ŀ�� �̵� �Լ�
void gotoxy(x,y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

// ���� ����
int Create_File(choice_file_num) {

	gotoxy(50,2);
	printf("��������������������������������������������������\n");
	gotoxy(50, 3);
	printf("���� �̸� �Է� (.txt�� �� �����ּ���.)\n");
	gotoxy(50, 4);
	printf("  >> ");
	scanf("%s", fname, sizeof(fname));
	memcpy(file_name[choice_file_num], fname, sizeof(fname));
	file_true_flag[choice_file_num] = 1;

	gotoxy(50, 5);
	printf("��������������������������������������������������\n");
	fp = fopen(fname, "w");
	
	gotoxy(50, 6);
	printf("�����͸� �Է����ּ���.\n");
	gotoxy(50, 7);
	printf(">>  ");
	scanf("%s", inside_data);

	fprintf(fp, inside_data);

	gotoxy(1, 22);
	printf(". ");
	Sleep(500);
	printf(". ");
	Sleep(500);
	printf(". ");

	printf(" �Է¿Ϸ�");
	Sleep(1000);

	system("cls");
	fclose(fp);
}

// ���� ���
int Output_File(choice_file_num) {
	fp = fopen(file_name[choice_file_num], "r");

	fgets(str_read, MAX_STR_SIZE, fp);

	gotoxy(50, 2);
	printf("________________________________________________________");
	gotoxy(50, 3);
	printf("���� %s�� �����Դϴ�...",file_name[choice_file_num]);
	gotoxy(50, 5);
	printf("________________________________________________________");
	gotoxy(50, 6);
	printf("%s", str_read);
	
	gotoxy(50, 8);
	printf("���ư����� �ƹ� Ű�� �Է�...");
	_getch();
}

void main() {
	init();

	while (1) {
		system("cls");

		gotoxy(70, 25);
		printf("��2020. ����. All rights reserved");
		gotoxy(0, 0);

		// �⺻ ȭ�� ���
		titleDraw();
		tipDraw();
		int fileCode = ListCtrl();
		
		// ���� ���� ��, �ش� ��Ͽ��� �����
		// ��� ����
		gotoxy(2, 19);
		printf("����� ���񽺸� �������ּ��� (1 : ������2 : ��¦�3 : ����)  >> ");
		scanf("%d", &choice_work);

		if (choice_work == 1) {					//����
			if (file_true_flag[fileCode] == 0) {		//�ش� ��� ���� ���� üũ
				system("cls");
				gotoxy(70, 25);
				printf("��2020. ����. All rights reserved");
				gotoxy(0, 0);
				titleDraw();
				ListDraw();

				Create_File(fileCode);
			}
			else {										//�ش� ��Ͽ� ������ ���� ��
				gotoxy(2, 22);
				printf("[error] �ش� ��ġ���� ������ �̹� �ֽ��ϴ�.");
				Sleep(1000);
				continue;
			}
		}

		else if (choice_work == 2) {			//����
			if (file_true_flag[fileCode] == 1) {		//�ش� ��� ���� ���� üũ
				system("cls");
				gotoxy(70, 25);
				printf("��2020. ����. All rights reserved");
				gotoxy(0, 0);
				titleDraw();
				ListDraw();
				Output_File(fileCode);
			}
			else {										//�ش� ��Ͽ� ������ ���� ��
				gotoxy(2, 22);
				printf("[error] �ش� ��ġ���� ������ �����ϴ�.");
				Sleep(1000);
				continue;
			}
		}
	}
	return 0;
}