// 파일 저장소 구현 프로젝트 
// 개발기간 : 2019.01.05 ~ 

// 기능 : (* 구현 완료) 
// 파일 저장*, 읽기*, 삭제, 수정

// 수정 메모
/**
1. 변수 초기화 하기
2. 자동으로 .txt로 변환
		ㄴ이거 너무 어려움 각잡고 하셈
			ㄴ ini파일 사용
3. 삭제 / 수정 구현
		ㄴ에바 ㄹㅇ
4. 덮어쓰기
10. 선택 시스템을 숫자로 받는게 아니라 키보드로 받기
		ㄴ 메인메뉴, 파일 선택(함수로 묶자 하나하나 복붙은 좀;),


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
int choice_work;	// 기능 선택
int choice_file;	// 파일 선택
int file_true_flag[5] = { 0,0,0,0,0 };	// 각 블록의 파일 유무

char* inside_data[256];		// 추가 파일 내용 
char* fname[50];			// 파일 이름
char* file_name[5][20] = { NULL };		// 파일 이름 2차원 배열
char str_read[MAX_STR_SIZE];

//------------------------------------------------------------- funsion

// 함수 선언
void init();
int KeyControl();
void titleDraw();
int menuDraw();
void ListDraw();
int ListCtrl();
void gotoxy(int x, int y);
int Create_File(choice_file_num);

// 콘솔창 크기, 이름
void init() {
	system("mode con cols=110 lines=30 | title 파일저장소");
}

// 선택 컨트롤 함수
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

// 팁 그리기
void tipDraw() {
	gotoxy(47, 2);
	printf("______________________T I P________________________");
	gotoxy(45, 4);
	printf("본 프로그램은 파일 생성, 출력, 삭제를 위해 시스템되어있습니다.");
	gotoxy(45, 6);
	printf("원하는 공간을 선택하시고 그곳에 파일을 생성,출력,삭제를");
	gotoxy(45, 7);
	printf("하실 수 있습니다.");
}

// 제목 그리기
void titleDraw() {
	printf("");
	printf(" ######      ######      ######\n");
	printf(" #          #           #\n");
	printf(" #####       #####       #####\n");
	printf(" #                #           #\n");
	printf(" #          ######      ######\n\n");
	printf("   File Storage System\n");
}

// 파일 리스트 그리기
void ListDraw() {
	int x = 2;
	int y = 12;
	printf_s("\n\n ─────────────────────────\n");
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
	printf_s("─────────────────────────");

	gotoxy(2, 21);
	printf_s("[ SYS LOG ]\n");
}

// 파일 리스트 컨트롤 함수
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

// 콘솔 내 커서 이동 함수
void gotoxy(x,y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

// 파일 생성
int Create_File(choice_file_num) {

	gotoxy(50,2);
	printf("─────────────────────────\n");
	gotoxy(50, 3);
	printf("파일 이름 입력 (.txt를 꼭 붙혀주세요.)\n");
	gotoxy(50, 4);
	printf("  >> ");
	scanf("%s", fname, sizeof(fname));
	memcpy(file_name[choice_file_num], fname, sizeof(fname));
	file_true_flag[choice_file_num] = 1;

	gotoxy(50, 5);
	printf("─────────────────────────\n");
	fp = fopen(fname, "w");
	
	gotoxy(50, 6);
	printf("데이터를 입력해주세요.\n");
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

	printf(" 입력완료");
	Sleep(1000);

	system("cls");
	fclose(fp);
}

// 파일 출력
int Output_File(choice_file_num) {
	fp = fopen(file_name[choice_file_num], "r");

	fgets(str_read, MAX_STR_SIZE, fp);

	gotoxy(50, 2);
	printf("________________________________________________________");
	gotoxy(50, 3);
	printf("파일 %s의 내용입니다...",file_name[choice_file_num]);
	gotoxy(50, 5);
	printf("________________________________________________________");
	gotoxy(50, 6);
	printf("%s", str_read);
	
	gotoxy(50, 8);
	printf("돌아갈려면 아무 키나 입력...");
	_getch();
}

void main() {
	init();

	while (1) {
		system("cls");

		gotoxy(70, 25);
		printf("ⓒ2020. 김명우. All rights reserved");
		gotoxy(0, 0);

		// 기본 화면 출력
		titleDraw();
		tipDraw();
		int fileCode = ListCtrl();
		
		// 파일 선택 후, 해당 블록에서 사용할
		// 기능 선택
		gotoxy(2, 19);
		printf("사용할 서비스를 선택해주세요 (1 : 생성│2 : 출력│3 : 삭제)  >> ");
		scanf("%d", &choice_work);

		if (choice_work == 1) {					//생성
			if (file_true_flag[fileCode] == 0) {		//해당 블록 파일 유무 체크
				system("cls");
				gotoxy(70, 25);
				printf("ⓒ2020. 김명우. All rights reserved");
				gotoxy(0, 0);
				titleDraw();
				ListDraw();

				Create_File(fileCode);
			}
			else {										//해당 블록에 파일이 있을 때
				gotoxy(2, 22);
				printf("[error] 해당 위치에는 파일이 이미 있습니다.");
				Sleep(1000);
				continue;
			}
		}

		else if (choice_work == 2) {			//삭제
			if (file_true_flag[fileCode] == 1) {		//해당 블록 파일 유무 체크
				system("cls");
				gotoxy(70, 25);
				printf("ⓒ2020. 김명우. All rights reserved");
				gotoxy(0, 0);
				titleDraw();
				ListDraw();
				Output_File(fileCode);
			}
			else {										//해당 블록에 파일이 없을 때
				gotoxy(2, 22);
				printf("[error] 해당 위치에는 파일이 없습니다.");
				Sleep(1000);
				continue;
			}
		}
	}
	return 0;
}