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
    for (int i=-1 ; i<2*n-1 ; i++) {
        for (int j=-1 ; j<2*n-1 ; j++) {
            if ((i==-1 || j==-1) ) {
                if ((i+2)%2==0 && (j+2)%2==1){
                    setTextColor(9,0);
                    printf("%2d",(i)*(j+2)/2);
                }
                else if((i+2)%2==1 && (j+2)%2==0) {
                    setTextColor(9,0);
                    printf("%2d  ",(i+2)*(j)/2);
                }
                else {
                    printf("  ");
                }
            }
            else {
                if (i==0 || j==0 || i==2*n-2 || j==2*n-2 ) {
                    setTextColor(7,0);
                    printf(" %c ",map[i][j]);
                }
                else if (i%2==0 || j%2==0) {
                    setTextColor(5,0);
                    if (map[i][j]=='=' || map[i][j]==':') setTextColor(4,0);
                    printf(" %c ",map[i][j]);
                }
                else {
                    setTextColor(15,8);
                    printf(" %c ",map[i][j]);
                }
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

void DeepFirstSearch(int xpoint,int ypoint,int side,char map[][2*side-1],int visit[side-1][side-1]){
    int xv=(xpoint-1)/2,yv=(ypoint-1)/2;
    visit[xv][yv] = 1;
    if (xv<side-2 && map[xpoint+1][ypoint]!='=' && visit[xv+1][yv]!=1) DeepFirstSearch(xpoint+2,ypoint,side,map,visit);
    if (xv>0 && map[xpoint-1][ypoint]!='=' && visit[xv-1][yv]!=1) DeepFirstSearch(xpoint-2,ypoint,side,map,visit);
    if (yv<side-2 && map[xpoint][ypoint+1]!=':' && visit[xv][yv+1]!=1) DeepFirstSearch(xpoint,ypoint+2,side,map,visit);
    if (yv>0 && map[xpoint][ypoint-1]!=':' && visit[xv][yv-1]!=1) DeepFirstSearch(xpoint,ypoint-2,side,map,visit);
    return ;
}

int putWall(struct players list[],int side,char map[][2*side-1]){
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
            map[2*x+1][2*y]= ':';
            map[2*x+3][2*y]=  ':';
        }
        else if (type=='h'){
            map[2*x][2*y+1]= '=';
            map[2*x][2*y+3]= '=';
        }
        int sw2=0,sw3=0;
        int visit[side-1][side-1];
        for (int i=0 ; i<side-1 ; i++)
            for (int j=0 ; j<side-1 ; j++)
                visit[i][j]=0;
        DeepFirstSearch(list[0].x,list[0].y,side,map,visit);
        for (int i=0 ; i<side-1 ; i++)
            if (visit[0][i]==1) sw2=1;
        for (int i=0 ; i<side-1 ; i++)
            for (int j=0 ; j<side-1 ; j++)
                visit[i][j]=0;
        DeepFirstSearch(list[1].x,list[1].y,side,map,visit);
        for (int i=0 ; i<side-1 ; i++)
            if (visit[side-2][i]==1) sw3=1;
        if (sw2==0 || sw3==0) {
            sw=0;
            if (type=='v'){
                map[2*x+1][2*y]= 179;
                map[2*x+3][2*y]=  179;
            }
            else if (type=='h'){
                map[2*x][2*y+1]= 196;
                map[2*x][2*y+3]= 196;
            }
        }
    }
    return sw;
}

int playersMovement(int side , char map[][2*side-1],int turn,struct players list[]){
    int turn2,sw=1;
    if (turn==1) turn2=2;
    else turn2=1;
    printf("enter button to move the player: ");
    char button = getch();
    if (button == 72) {
        if ( list[turn-1].x==1 || map[list[turn-1].x-1][list[turn-1].y]=='=') return 0;
        else {
            map[list[turn-1].x][list[turn-1].y] = ' ';
            list[turn-1].x -= 2;
            if (map[list[turn-1].x][list[turn-1].y]==list[turn2-1].shape){
                list[turn-1].x -= 2;
                map[list[turn-1].x][list[turn-1].y] = list[turn-1].shape;
                sw=0;
            }
            else {
                map[list[turn-1].x][list[turn-1].y] = list[turn-1].shape;
                return 1;
            }
        }
    }
    else if (button == 80) {
        if (list[turn-1].x==2*side-3 || map[list[turn-1].x+1][list[turn-1].y]=='=') return 0;
        else {
            map[list[turn-1].x][list[turn-1].y]=' ';
            list[turn-1].x += 2;
            if (map[list[turn-1].x][list[turn-1].y]==list[turn2-1].shape){
                list[turn-1].x += 2;
                map[list[turn-1].x][list[turn-1].y] = list[turn-1].shape;
                sw=0;
            }
            else {
                map[list[turn-1].x][list[turn-1].y]=list[turn-1].shape;
                return 1;
            }
        }
    }
    else if (button == 77) {
        if (list[turn-1].y==2*side-3 || map[list[turn-1].x][list[turn-1].y+1]=='!') return 0;
        else {
            map[list[turn-1].x][list[turn-1].y]=' ';
            list[turn-1].y += 2;
            if (map[list[turn-1].x][list[turn-1].y]==list[turn2-1].shape){
                list[turn-1].y += 2;
                map[list[turn-1].x][list[turn-1].y] = list[turn-1].shape;
                sw=0;
            }
            else {
                map[list[turn-1].x][list[turn-1].y]=list[turn-1].shape;
                return 1;
            }
        }
    }
    else if (button == 75) {
        if (list[turn-1].y==1 || map[list[turn-1].x][list[turn-1].y-1]=='!') return 0;
        else {
            map[list[turn-1].x][list[turn-1].y]=' ';
            list[turn-1].y -= 2;
            if (map[list[turn-1].x][list[turn-1].y]==list[turn2-1].shape){
                list[turn-1].y -= 2;
                map[list[turn-1].x][list[turn-1].y] = list[turn-1].shape;
                sw=0;
            }
            else {
                map[list[turn-1].x][list[turn-1].y]=list[turn-1].shape;
                return 1;
            }
        }
    }
    if (sw==1) playersMovement(side, map,turn,list);
}

void putplayer(int length , char map[][2*length-1] ,int x ,int y , char ch) {
    map[x][y] = ch;
}

int iswinner(int locWin,const struct players new) {
    if (new.x==locWin) return 1;
    else return 0;
}

void exitButton() {
    printf("\n");
    char ch;
    printf("please press Esc button for exit:\n");
    do{
        ch=getch();
    } while (ch !=27);
}