#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "printMap.c"
#pragma "EmptyMap.c"
#include "exit function.c"

void putplayer(int length , char map[][2*length-1] ,int x ,int y , char ch) {
    map[x][y] = ch;
}

void gotoxy(int x , int y) {
    HANDLE cosoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cousorCoord;
    cousorCoord.X = y;
    cousorCoord.Y = x;
    SetConsoleCursorPosition(cosoleHandle, cousorCoord);
}

void clearScreen() {
    system("cls");
}

void putWall(int side,char map[][2*side-1]){
    char x,y,type;
    printf("Please enter the coordinates and type ('h' for horizontal & 'v' for vertical) of the wall(like this ==> 3 4 h):");
    scanf("%c %c %c",&x,&y,&type);
    if (type=='v'){
        map[x+1][y]= 186;
        map[x+2][y]= 215;
        map[x+3][y]= 186;
    }
    else if (type=='h'){
        map[x][y+1]= 205;
        map[x][y+2]= 216;
        map[x][y+3]= 205;
    }
    clearScreen();
    printmap(side,map);
}

int ChoseMoveOrWall(){
    char selection;
    scanf("%c",&selection);
    if (selection=='m') return 1;
    else if (selection=='w') return 2;
    else ChoseMoveOrWall();
}

int main () {
    int side;
    printf("Please enter the length of the game map (must be even and between 4 and 20!!!): ");
    scanf("%d",&side);
    int walls;
    printf("\nEnter the number of allowed walls!!!:");
    scanf("%d",&walls);
    char nameFP[20],nameSP[20];
    printf("\nEnter the first player's name:");
    scanf("%s",nameFP);
    printf("\nEnter the name of the second player:");
    scanf("%s",nameSP);
    char map[2*side-1][2*side-1];
    emptymap(side , map);
    putplayer(side , map ,1 , (2*side-1)/2 , '*');
    putplayer(side , map ,2*side-3 , (2*side-1)/2 , '@');
    printmap(side,map);
    printf("Press 'm' to move or 'w' to place the wall:");
    int resulte=ChoseMoveOrWall();
    if (resulte==2) {
        putWall(side,map);
    }
    exitButton();
    return 0;
}