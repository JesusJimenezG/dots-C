//dots
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define UP '\x48'
#define DOWN '\x50'
#define LEFT '\x4b'
#define RIGHT '\x4d'
#define ENTER '\x0D'
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define EXIT '\x81'
#define RESET '\x52'

void menu();
void game();
void background();
void draw();
void move();
void dots(int y, int x);
int end();
void restart();
void gotoxy(int x, int y);
typedef struct{
	int board[20][36];
	int x,y;
	char player1[200],player2[200];
	int score1,score2;
	int statement;
	int on;
}resources;
resources res;

int main(){
	res.on=5;
	menu();
	return 0;
}
void menu(){
	while(res.on!=0){
		printf("Bienvenido a dots.\n1)Jugar.\n2)Salir.\n\nIngrese una opcion: ");
		scanf("%d",&res.on);
		if (res.on==1){
			system ("cls");
			printf("Ingrese el nombre del jugador 1: ");
			scanf("%s",&res.player1);
			system ("cls");
			printf("Ingrese el nombre del jugador 2: ");
			scanf("%s",&res.player2);
			system ("cls");
			game();
		}	else if(res.on!=2){
			printf("Opcion incorrecta. Intente de nuevo.\n");
			system("pause");
			system ("cls");
		}	else{
			system("cls");
			printf("Hasta luego.");
			res.on=0;
		}
	}
}
void game(){
	res.statement=1;
	res.y=8;	res.x=14;
	background();	
	do{
		draw();
		move();
		//status*=-1;
		system("cls");
		end();	
	}while(res.on!=0);
	
}
void background(){
	int i,j;
	
	for(i=0;i<=16;i++){
		for(j=0;j<=32;j++){
			res.board[i][j]=0;
		}
	}
}
void draw(){
	int i,j;
	for(i=1;i<=16;i++){
		if(i%2!=0){
			for(j=1;j<=33;j++){
				if(j%2==0){
					printf("%c",/*res.board[i][j]*/250);
				}else{
					if(res.board[i][j]==1){
						printf("%c",/*res.board[i][j]*/196);
					}else{
						printf(" ");
					}
					
				}
			}
			printf("\n");	
		}else{
			for(j=1;j<=33;j++){
				if(res.board[i][j]==1){
						printf("%c",/*res.board[i][j]*/124);
					}else if(res.board[i][j]==5){
						printf(ANSI_COLOR_GREEN"X"ANSI_COLOR_RESET/*,res.board[i][j]*//*124*/);
					}else if(res.board[i][j]==6){
						printf(ANSI_COLOR_RED"O"ANSI_COLOR_RESET/*,res.board[i][j]*//*124*/);
					}
					
					
					
					else{
						printf(" ");
					}
			}
			printf("\n");
		}
	}
	if(res.on==0){
		if(res.score1>res.score2){
			printf ("\n\nGanador: "ANSI_COLOR_GREEN"%s"ANSI_COLOR_RESET"\tPuntuacion: "ANSI_COLOR_GREEN"%d"ANSI_COLOR_RESET"\n\n",res.player1,res.score1);
			system("pause");
		}else{
			printf ("\n\nGanador: "ANSI_COLOR_RED"%s"ANSI_COLOR_RESET"\tPuntuacion: "ANSI_COLOR_RED"%d"ANSI_COLOR_RESET".\n\n",res.player2,res.score2);
			system("pause");
		}
	}else{
		if(res.statement==1){
			printf ("\nTurno del jugador: "ANSI_COLOR_GREEN"%s"ANSI_COLOR_RESET,res.player1);
		}else{
			printf ("\nTurno del jugador: "ANSI_COLOR_RED"%s"ANSI_COLOR_RESET,res.player2);
		}
		printf("\n\nPuntaje %s: "ANSI_COLOR_GREEN"%d"ANSI_COLOR_RESET".\tPuntaje %s: "ANSI_COLOR_RED"%d."ANSI_COLOR_RESET"",res.player1,res.score1,res.player2,res.score2);
		printf("\nMovimiento:\tFlecha arriba: %c ; Flecha abajo: %c ; Flecha izquierda: %c ; Flecha derecha: %c\nRestart: R(beta).",94,118,60,62);
	}
}
void move(){
	int key,x,y,placed=0;
	gotoxy(res.x,res.y);
	
	do{
		key=getch();
		key=toupper(key);
		if(key == UP){	
			if(res.y>0&&res.y<=14){
				if(res.y!=0){
					res.y-=1;
				}
				if(res.x==1){
					res.x+=1;
				}else if(res.x==31||res.x==2){
					res.x-=1;
				}else{
					res.x+=1;
				}
			}	
		}
		if(key == DOWN){
			if(res.y>=0&&res.y<14){
				if(res.y!=14){
					res.y+=1;
				}
				if(res.x==1){
					res.x+=1;
				}else if(res.x==31||res.x==2){
					res.x-=1;
				}else{
					res.x+=1;
				}
			}
		}
		if(key == LEFT){
			if(res.x>=1&&res.x<=31){
				if(res.x>1&&res.x!=2){
					res.x-=2;
				}		
			}
		}
		if(key == RIGHT){
			if(res.x>=1&&res.x<=30){
				if(res.x<30&&res.x!=30){
					res.x+=2;
				}		
			}
		}
		if(key == EXIT){
			exit(0);
		}
		if(key == RESET){
			restart();
		}
		gotoxy(res.x,res.y);
		//printf("\n\n\n\n\n\n\n\n\n\nWatch de Y: %d. Watch de X: %d.",res.y,res.x);
		//gotoxy(res.x,res.y);
		if(key == ENTER){
			x=res.x+1;	y=res.y+1;
			if(res.board[res.y+1][res.x+1]==0){
				res.board[res.y+1][res.x+1]=1;
				placed=1;	
			}else{
				system("cls");
				printf("Posicion invalida. Intente de nuevo.\n");
				system ("pause");
				system("cls");
				draw();
				gotoxy(res.x,res.y);
			}
			res.y=res.y;	res.x=res.x;	
		}
	}while(placed!=1);	
	dots(y,x);
}
void dots(int y,int x){
	int count,i,j,ii,jj,scored=0;	
	if(y%2!=0){
		res.board[y][x+1]=1;	
		res.board[y][x-1]=1;
	}else{
		res.board[y+1][x]=1;	
		res.board[y-1][x]=1;
	}
	for(i=0;i<16;i++){
		for(j=0;j<32;j++){
			if(res.board[i][j]==1){
				count=0;
				for(ii=i;ii<i+3;ii++){
					for(jj=j;jj<j+3;jj++){
						if(res.board[ii][jj]==1){
							count++;	
						}
					}
				}
				if(count==8){
					if(res.board[i+1][j+1]==0){
						if(res.statement==1){
							res.board[i+1][j+1]=5;
							res.score1+=1;
							scored=1;
						}else{
							res.board[i+1][j+1]=6;
							res.score2+=1;
							scored=1;
						}
					}
				}
			}
		}
	}
	if(scored==0&&res.statement!=2){
		res.statement*=-1;
	}
}
int end(){
	int i,j,check=0;
	for (i=1;i<=15;i++){
		for(j=2;j<=32;j++){
			if(res.board[i][j]==0){
				check+=1;
			}
		}
	}
	if (check<1){
		res.on=0;
		system ("cls");
		draw();
	}
	return 0; 	
}
void restart(){
	res.score1=0;
	res.score2=0;
	res.x=0;
	res.y=0;
	fflush(stdin);
	system("cls");
	printf ("Restart\n");
	system ("pause");
	system ("cls");
	menu();
}
void gotoxy(int x, int y){	//controlador de movimiento de la consola de windows.
    HANDLE hCon;
    COORD dwPos;
	dwPos.X = x;
    dwPos.Y = y;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);
}
