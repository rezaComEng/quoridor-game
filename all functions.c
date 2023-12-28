#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

struct players {
    char name[20];
    char shape;
    int numofwall;
    int x,y;
};

void emptymap(int n,char mapArray[][n *2 -1]){
    int side=2*n-1;
    for (int i = 0; i < side; i++){
        for (int j = 0; j < side; j++) {
            if (i%2==0 && j%2==1) mapArray[i][j] = 196;
            else if (i % 2 == 1 && j % 2 == 0) mapArray[i][j] =179;
            else if (i % 2 == 1 && j % 2 == 1) mapArray[i][j] =255;
            else if (i % 2 == 0 && j % 2 == 0) {
                if(i==0 && j==0) mapArray[i][j]=218;
                else if (i==0 && j==side-1) mapArray[i][j]=191;
                else if (i==side-1 && j==0) mapArray[i][j]=192;
                else if (i==side-1 && j==side-1) mapArray[i][j]=217;
                else if (j==0 && i%2==0) mapArray[i][j]=179;
                else if (i==0 && j%2==0) mapArray[i][j]=196;
                else if (j==side-1 && i%2==0) mapArray[i][j]=179;
                else if (i==side-1 && j%2==0) mapArray[i][j]=196;
                else mapArray[i][j]=197;
            }
        }
    }
}

void setTextColor(int textColor, int backColor) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = backColor << 4 | textColor;
    SetConsoleTextAttribute(consoleHandle , colorAttribute);
}

void printMap(int n , char map[][2*n-1]) {
    printf("\n");
    for (int i=0 ; i<2*n-1 ; i++) {
        for (int j=0 ; j<2*n-1 ; j++) {
            if (i==0 || j==0 || i==2*n-2 || j==2*n-2 ) {
                setTextColor(0,1);
                printf(" %c ",map[i][j]);
            }
            else if (i%2==0 || j%2==0) {
                setTextColor(5,1);
                if (map[i][j]==215 || map[i][j]==205 || map[i][j]==216 || map[i][j]==186) setTextColor(4,4);
                printf(" %c ",map[i][j]);
            }
            else {
                setTextColor(15,3);
                printf(" %c ",map[i][j]);
            }
        }
        printf("\n");
    }
    setTextColor(7,0);
    printf("\n");
}

void printinformation(const struct players list[], int numofplayers) {
    for (int i = 0; i < numofplayers; i++) {
        setTextColor(1,0);
        printf("player %d information: \n",i+1);
        setTextColor(2,0);
        printf("player`s name: %s \n",list[i].name);
        setTextColor(3,0);
        printf("shape of the player: %c \n",list[i].shape);
        setTextColor(4,0);
        printf("number of Walls: %d \n",list[i].numofwall);
        setTextColor(5,0);
    }
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

int choseMoveOrWall(){
    printf("Press 'm' to move or 'w' to place the wall:");
    char selection;
    scanf("%c",&selection);
    if (selection=='m') return 1;
    else if (selection=='w') return 2;
    else choseMoveOrWall();
}

int putWall(int side,char map[][2*side-1]){
    int x,y;
    char type;
    printf("Please enter the coordinates and type ('h' for horizontal & 'v' for vertical) of the wall(like this ==> 3 4 h):");
    scanf("%d %d %c",&x,&y,&type);
    int sw=1;
    if (type=='v'){
        if (y==0 || y==side-1  || x>=side-1) {
            sw=0;
        }
    }
    else if (type=='h') {
        if (x==0 || x==side-1 || y>=side-1) {
            sw=0;
        }
    }
    if (sw==1) {
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
    }
    return sw;
}

int playersMovement(int side , char map[][2*side-1],struct players *p){
    printf("enter button to move the player: ");
    char button = getch();
    if (button == 72) {
        map[p->x][p->y]=' ';
        p->x -= 2;
        map[p->x][p->y]=p->shape;
    }
    else if (button == 80) {
        map[p->x][p->y]=' ';
        p->x += 2;
        map[p->x][p->y]=p->shape;
    }
    else if (button == 77) {
        map[p->x][p->y]=' ';
        p->y += 2;
        map[p->x][p->y]=p->shape;
    }
    else if (button == 75) {
        map[p->x][p->y]=' ';
        p->y -= 2;
        map[p->x][p->y]=p->shape;
    }
    return 0;
}

void putplayer(int length , char map[][2*length-1] ,int x ,int y , char ch) {
    map[x][y] = ch;
}

void exitButton() {
    printf("\n");
    char ch;
    printf("please press Esc button for exit:\n");
    do{
        ch=getch();
    } while (ch !=27);
}