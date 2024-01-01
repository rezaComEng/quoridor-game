#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

int isblock(int x, int y,int side,char map[][2*side-1]);

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
                setTextColor(7,0);
                printf(" %c ",map[i][j]);
            }
            else if (i%2==0 || j%2==0) {
                setTextColor(5,0);
                if (map[i][j]==215 || map[i][j]==205 || map[i][j]==216 || map[i][j]==186) setTextColor(4,4);
                printf(" %c ",map[i][j]);
            }
            else {
                setTextColor(15,8);
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
    char selection;
    scanf("%c",&selection);
    if (selection=='m') return 1;
    else if (selection=='w') return 2;
    else choseMoveOrWall();
}

int putWall(int side,char map[][2*side-1]){
    int x,y;
    char type;
    printf("\nPlease enter the coordinates and type ('h' for horizontal & 'v' for vertical) of the wall(like this ==> 3 4 h):");
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
            map[2*x+1][2*y]= '!';
            map[2*x+3][2*y]=  '!';
        }
        else if (type=='h'){
            map[2*x][2*y+1]= '=';
            map[2*x][2*y+3]= '=';
        }
    }
    return sw;
}

int playersMovement(int side , char map[][2*side-1],struct players *p){
    printf("enter button to move the player: ");
    char button = getch();
//    int dx=0,dy=0;
//
//    if (button == 72) dx -= 2;
//    else if (button == 80) dx += 2;
//    else if (button == 77) dy += 2;
//    else if (button == 75) dy -= 2;
//
//    if ( p->x+dx<1 || p->x+dx>2*side-3 || p->y+dy<1 || p->y+dy>2*side-3 || isblock(p->x+(dx/2),p->y+(dy/2),side,map)) {
//        playersMovement(side, map, p);
//        return 0;
//    }
//    map[p->x][p->y]=' ';
//    p->x += dx;
//    p->y += dy;
//    map[p->x][p->y]=p->shape;
//    return 1;
    if (button == 72) {
        if ( p->x==1 || map[p->x-1][p->y]=='=') return 0;
        else {
            map[p->x][p->y] = ' ';
            p->x -= 2;
            map[p->x][p->y] = p->shape;
            return 1;
        }
    }
    else if (button == 80) {
        if (p->x==2*side-3 || map[p->x-1][p->y]=='=') return 0;
        else {
            map[p->x][p->y]=' ';
            p->x += 2;
            map[p->x][p->y]=p->shape;
            return 1;
        }
    }
    else if (button == 77) {
        if (p->y==2*side-3 || map[p->x][p->y+1]=='!') return 0;
        else {
            map[p->x][p->y]=' ';
            p->y += 2;
            map[p->x][p->y]=p->shape;
            return 1;
        }
    }
    else if (button == 75) {
        if (p->y==1 || map[p->x][p->y-1]=='!') return 0;
        else {
            map[p->x][p->y]=' ';
            p->y -= 2;
            map[p->x][p->y]=p->shape;
            return 1;
        }
    }
    playersMovement(side, map, p);
}

//int playersMovement(int side, char map[][2*side-1], struct players *p) {
//    printf("enter button to move the player: ");
//    char button = getch();
//    int dx = 0, dy = 0;
//    switch (button) {
//        case 72: dx = -2; break; // UP
//        case 80: dx = 2; break;  // DOWN
//        case 77: dy = 2; break;  // RIGHT
//        case 75: dy = -2; break; // LEFT
//    }
//    int newX = p->x + dx;
//    int newY = p->y + dy;
//
//    int wallx = p->x + dx/2;
//    int wally = p->y + dy/2;
//
//    if (newX < 0 || newY < 0 || newX > 2*side-3 || newY > 2*side-3 || isblock(wallx, wally, side, map)) {
//        return 0;
//    } else {
//        map[p->x][p->y]=' ';
//        p->x = newX;
//        p->y = newY;
//        map[p->x][p->y]=p->shape;
//        return 1;
//    }
//}

void putplayer(int length , char map[][2*length-1] ,int x ,int y , char ch) {
    map[x][y] = ch;
}

int iswinner(int locWin,const struct players new) {
    if (new.x==locWin) return 1;
    else return 0;
}

int isblock(int x, int y,int side,char map[][2*side-1]){
    if (map[x][y] == 205 || map[x][y] == 186) return 1;
    return 0;
}

void exitButton() {
    printf("\n");
    char ch;
    printf("please press Esc button for exit:\n");
    do{
        ch=getch();
    } while (ch !=27);
}