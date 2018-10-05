#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#define LENGTH 4
void textcolor(int blocknum);
void printBoard(int board[][4], int score);
int newPut(int board[][4], char overOrContinue);
boolean gravity(int upDown, int leftRight, int(*board)[4], int *score);
void cursor(int onoff){
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = onoff;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}
int main(){
    int newTile, i, j, score=0;
    int board[4][4]={0};
    int way=0, key=0;
    char overOrContinue='n';
    boolean moved=1, gameOver=0;
    FILE *FLOAD, *FSAVE;
    FLOAD=fopen("save.txt", "r");
    srand((int)time(NULL));
    system("mode con cols=30 lines=20");
    system("title 2048");
    textcolor(0);
    if(FLOAD!=NULL&&fscanf(FLOAD, "%d", &board[0][0])!= EOF){
        cursor(1);
        do{
            printf("저장된 데이터가 있습니다.\n불러오시겠습니까? (y / n) : ");
            key=_getche();
            Sleep(100);
            system("cls");
        }while(key!='y'&&key!='n');
        if(key=='y'){
            for(i=0;i<LENGTH;i++){
                for(j=0;j<LENGTH;j++){
					if (i == 0 && j == 0)continue;
                    fscanf(FLOAD, "%d", &board[i][j]);
                    if(board[i][j]>=2048)overOrContinue='y';
                }
            }
            fscanf(FLOAD, "%d", &score);
        }
        else{
            FSAVE=fopen("save.txt", "w");
            fclose(FSAVE);
        }
        fclose(FLOAD);
    }
    if(key!='y'){
		newTile=newPut(board, overOrContinue);
		if(newTile>=0)board[newTile/4][newTile%4]=(rand()%100 >= 90?4:2);
    }
    cursor(0);
    while(1){
        if(key!='y'&&key!='s'){
            newTile=newPut(board, overOrContinue);
            if(newTile==-1){
                gameOver=1;
                for(i=0;i<LENGTH&&gameOver==1;i++){
                    for(j=0;j<LENGTH&&gameOver==1;j++){
                        if(j<LENGTH-1&&board[i][j]==board[i][j+1])gameOver=0;
                        if(j>0&&board[i][j]==board[i][j-1])gameOver=0;
                        if(i<LENGTH-1&&board[i][j]==board[i+1][j])gameOver=0;
                        if(i>0&&board[i][j]==board[i+1][j])gameOver=0;
                    }
                }
                if(gameOver==1){
                    FSAVE=fopen("save.txt", "w");
                    fclose(FSAVE);
                    printBoard(board, score);
                    printf("Game Over!\n");
					Sleep(100);
					return 0;
                }
            }
            else if(newTile==-2&&overOrContinue=='n'){
                do{
                    printBoard(board,score);
                    printf("You win!\n");
                    cursor(1);
                    printf("Continue? (y / n) : ");
                    overOrContinue=_getche();
                    Sleep(100);
                    system("cls");
                }while(overOrContinue!='y'&&overOrContinue!='n');
                if(overOrContinue=='n'){
					return 0;
                }
                cursor(0);
            }
            if(moved==1)board[newTile/4][newTile%4]=(rand()%100 >= 90?4:2);
        }
        do{
            printBoard(board, score);
            printf("조작 : 방향키\n저장 : s\n종료 : x\n");
            key=_getch();
            way=0;
            if(key==224){
                way=_getch();
                switch(way){
                    case 72:moved=gravity(-1,0, board, &score);break; //위
                    case 80:moved=gravity(1,0, board, &score);break; //아래
                    case 75:moved=gravity(0,-1, board, &score);break; //왼쪽
                    case 77:moved=gravity(0,1, board, &score);break; //오른쪽
                    default:;
                }
            }
            else if(key=='s'||key=='x'){
                /*
                char SaveInput[100]={NULL};
                printf("저장 파일의 경로 : ");
                scanf("%[^\n]",SaveInput);
                strcat(SaveInput,"\\Save.txt");
                FSAVE=fopen(SaveInput, "w");
                */
                FSAVE=fopen("save.txt","w");
                for(i=0;i<LENGTH;i++){
                    for(j=0;j<LENGTH;j++){
                        fprintf(FSAVE, "%d ", board[i][j]);
                    }
                    fprintf(FSAVE, "\n");
                }
                fprintf(FSAVE, "%d", score);
                fclose(FSAVE);
                printf("저장 완료.\n");
                Sleep(100);
            }
            system("cls");
        }while(key!='x'&&key!=224&&way!=72&&way!=80&&way!=75&&way!=77);
        if(key=='x'){
            printf("Good Bye!\n");
			Sleep(100);
			return 0;
        }
    }
}
void textcolor(int blocknum) {
	int color;
	if (blocknum == 0)color = 15;
	else if (blocknum == 2)color = 15;    //글씨 흰색
	else if (blocknum == 4)color = 7;     //글씨 회색
	else if (blocknum == 8)color = 14;    //글씨 노랑색
	else if (blocknum == 16)color = 10;   //글씨 연두색
	else if (blocknum == 32)color = 13;   //글씨 자주색
	else if (blocknum == 64)color = 12;   //글씨 빨강색
	else if (blocknum == 128)color = 224; //바탕색 노랑색    글씨 검은색
	else if (blocknum == 256)color = 160; //바탕색 연두색    글씨 검은색
	else if (blocknum == 512)color = 208; //바탕색 자주색    글씨 검은색
	else if (blocknum == 1024)color = 192;//바탕색 빨강색    글씨 흰색
	else if (blocknum == 2048)color = 240;//바탕색 흰색      글씨 검은색
	else color = 176;              //바탕색 하늘색    글씨 검은색
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void printBoard(int board[][4], int score) {
	int i, j, maxTile = 0, k;
	for (i = 0; i<LENGTH; i++) {
		for (j = 0; j <= LENGTH * 6; j++) {
			printf("-");
		}
		printf("\n");
		for (j = 0; j<LENGTH; j++) {
			printf("|");
			if (board[i][j] == 0) {
				for (k = 0; k<5; k++) {
					printf(" ");
				}
			}
			else {
				textcolor(board[i][j]);
				printf("%5d", board[i][j]);
			}
			textcolor(0);
		}
		printf("|\n");
	}
	for (j = 0; j <= LENGTH * 6; j++) {
		printf("-");
	}
	printf("\n");
	printf("점수 : %d\n", score);
}
int newPut(int board[][4], char overOrContinue)
{
	int randTile, emptyRoom = 0, i, j;
	int empty[16] = { 0 };
	srand((int)time(NULL));
	for (i = 0; i<LENGTH; i++) {
		for (j = 0; j<LENGTH; j++) {
			if (board[i][j] == 0) {
				empty[emptyRoom] = i * LENGTH + j;
				emptyRoom++;
			}
			else if (board[i][j] >= 2048 && overOrContinue == 'n')return -2;
		}
	}
	if (emptyRoom <= 0)return -1;
	randTile = rand() % emptyRoom;
	return empty[randTile];
}
boolean gravity(int upDown, int leftRight, int(*board)[4], int *score) {
	int i, j, k;
	boolean added[16] = { 0 };
	boolean moved = 0;
	if (leftRight == 0) {
		for (j = 0; j<LENGTH; j++) {
			for (i = (LENGTH - 1)*(1 + upDown) / 2; i >= 0 && i<LENGTH; i -= upDown) {
				if (board[i][j] != 0) {
					for (k = 1; i + k * upDown >= 0 && i + k * upDown<LENGTH&&board[i + k * upDown][j] == 0; k++) {}
					if (i + k * upDown >= 0 && i + k * upDown<LENGTH&&board[i][j] == board[i + k * upDown][j] && !added[LENGTH*(i + k * upDown) + j]) {
						board[i + k * upDown][j] += board[i][j];
						*score += board[i][j];
						board[i][j] = 0;
						added[LENGTH*(i + k * upDown) + j] = 1;
						moved = 1;
					}
					else board[i + k * upDown - upDown][j] = board[i][j];
					if (k != 1) {
						board[i][j] = 0;
						moved = 1;
					}
				}
			}
		}
	}
	else {
		for (i = 0; i<LENGTH; i++) {
			for (j = (LENGTH - 1)*(1 + leftRight) / 2; j >= 0 && j<LENGTH; j -= leftRight) {
				if (board[i][j] != 0) {
					for (k = 1; j + k * leftRight >= 0 && j + k * leftRight<LENGTH&&board[i][j + k * leftRight] == 0; k++) {}
					if (j + k * leftRight >= 0 && j + k * leftRight<LENGTH&&board[i][j] == board[i][j + k * leftRight] && !added[LENGTH*i + k * leftRight + j]) {
						board[i][j + k * leftRight] += board[i][j];
						*score += board[i][j];
						board[i][j] = 0;
						added[LENGTH*i + k * leftRight + j] = 1;
						moved = 1;
					}
					else board[i][j + k * leftRight - leftRight ] = board[i][j];
					if (k != 1) {
						board[i][j] = 0;
						moved = 1;
					}
				}
			}
		}
	}
	return moved;
}
