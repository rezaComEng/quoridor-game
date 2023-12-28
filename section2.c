#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "printMap.c"
#pragma "EmptyMap.c"
#include "exit function.c"

void putplayer(int length , char map[][2*length-1] ,int x ,int y , char ch);
void gotoxy(int x , int y);
void clearScreen();
void putWall(int side,char map[][2*side-1]);
int ChoseMoveOrWall();

const struct players {
    char name[20];
    char shape;
    int numofwall;
    int x,y;
};

void playersmovement(int side , char map[][2*side-1],struct players p){
    printf("enter button to move the player: ");
    char button;
    do {
        button=getch();
    } while (button==224);
    if (button==72) {
        map[p.x][p.y]=' ';
        p.x -= 2;
        map[p.x][p.y]=p.shape;
    }
    else if (button==80) {
        map[p.x][p.y]=' ';
        p.x += 2;
        map[p.x][p.y]=p.shape;
    }
    else if (button==77) {
        map[p.x][p.y]=' ';
        p.y += 2;
        map[p.x][p.y]=p.shape;
    }
    else if (button==75) {
        map[p.x][p.y]=' ';
        p.y -= 2;
        map[p.x][p.y]=p.shape;
    }
    else {
        clearScreen();
        printmap(side,map);
        printf("wrong button!!!\n");
        playersmovement(side,map,p);
    }
}

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
    int x,y;
    char type;
    printf("Please enter the coordinates and type ('h' for horizontal & 'v' for vertical) of the wall(like this ==> 3 4 h):");
    scanf("%d %d %c",&x,&y,&type);
    int sw=0;
    if (type=='v'){
        if (y==0 || y==side-1) {
            clearScreen();
            printmap(side,map);
            printf("\nwrong cordinates!!!\n");
            putWall(side,map);
            sw=1;
        }
        else if (x>=side-1) {
            clearScreen();
            printmap(side,map);
            printf("\nwrong cordinates!!!\n");
            putWall(side,map);
            sw=1;
        }
    }
    else if (type=='h') {
        if (x==0 || x==side-1) {
            clearScreen();
            printmap(side,map);
            printf("\nwrong cordinates!!!\n");
            putWall(side,map);
            sw=1;
        }
        else if (y>=side-1) {
            clearScreen();
            printmap(side,map);
            printf("\nwrong cordinates!!!\n");
            putWall(side,map);
            sw=1;
        }
    }
    if (sw==0) {
        if (type=='v'){
            map[2*x+1][2*y]= 186;
            map[2*x+2][2*y]= 215;
            map[2*x+3][2*y]= 186;
        }
        else if (type=='h'){
            map[2*x][2*y+1]= 205;
            map[2*x][2*y+2]= 216;
            map[2*x][2*y+3]= 205;
        }
        clearScreen();
        printmap(side,map);
    }
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
    struct players p1,p2;
    int walls;
    printf("\nEnter the number of allowed walls!!!:");
    scanf("%d",&walls);
    p2.numofwall=p1.numofwall=walls;
    p1.y=p2.y=((2*side-1)/2);
    p1.x=2*side-3;
    p2.x=1;
    char nameFP[20],nameSP[20];
    printf("\nEnter the first player's name:");
    scanf("%s",nameFP);
    strcpy(p1.name,nameFP);
    printf("\nEnter the name of the second player:");
    scanf("%s",nameSP);
    strcpy(p2.name,nameSP);
    p1.shape='*';
    p2.shape='o';
    char map[2*side-1][2*side-1];
    emptymap(side , map);
    putplayer(side , map ,p2.x , p2.y , p2.shape);
    putplayer(side , map ,p1.x , p1.y  , p1.shape);
    printmap(side,map);
    printf("Press 'm' to move or 'w' to place the wall:");
    int resulte=ChoseMoveOrWall();
    if (resulte==2) {
        putWall(side,map);
    }
    else if (resulte==1) {
        playersmovement(side,map,p1);
    }
    exitButton();
    return 0;
}