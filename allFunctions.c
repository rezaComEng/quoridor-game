#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define Length 10;

int getRandomNumber(int lower, int upper) {

    int range = upper - lower + 1;

    int randomNumber = rand();

    int scaledNumber = (randomNumber / (RAND_MAX + 1.0)) * range;

    return scaledNumber + lower;
}

struct players {
    char type[10];
    char name[20];
    char shape;
    int numofwall;
    int x,y;
};

struct DataGame {
    int numofplayers;
    int turn;
    struct players list[4];
    char map[19][19];
};

void SaveGame(const char *fileName,const struct DateGame *dataname){
    FILE* file=fopen(fileName,"wb");
    if ( file != NULL ) {
        fwrite(dataname, sizeof(struct DataGame),1,file);
        fclose(file);
    }
}

void loadGame(const char *fileName,const struct DataGame *dataname) {
    FILE* file = fopen(fileName,"rb");
    if ( file != NULL ) {
        fread(dataname, sizeof(struct DataGame),1,file);
        fclose(file);
    }
}

void emptymap(int n,char mapArray[][n *2 -1]){
    for (int i=0 ; i<2 * n -1 ; i++){
        for (int j = 0; j < 2 * n -1; j++) {
            if (i%2==0 && j%2==1) mapArray[i][j] = 196;
            else if (i % 2 == 1 && j % 2 == 0) mapArray[i][j] =179;
            else if (i % 2 == 1 && j % 2 == 1) mapArray[i][j] =255;
            else if (i % 2 == 0 && j % 2 == 0) {
                if(i==0 && j==0) mapArray[i][j]=218;
                else if (i==0 && j==2 * n -2) mapArray[i][j]=191;
                else if (i==2 * n -2 && j==0) mapArray[i][j]=192;
                else if (i==2 * n -2 && j==2 * n -2) mapArray[i][j]=217;
                else if (j==0 && i%2==0) mapArray[i][j]=179;
                else if (i==0 && j%2==0) mapArray[i][j]=196;
                else if (j==2 * n -2 && i%2==0) mapArray[i][j]=179;
                else if (i==2 * n -2 && j%2==0) mapArray[i][j]=196;
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
                    setTextColor(0,8);
                    printf(" %c ",map[i][j]);
                }
            }
        }
        printf("\n");
    }
    setTextColor(7,0);
    printf("\n");
}

void printinformation(const struct players list[] , int numofplayers) {
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

void saveInformation(int turn,struct DataGame dataname,const struct players list[],const int map[][19]){
    dataname.turn = turn;
    for (int i=0 ; i<dataname.numofplayers ; i++)
        dataname.list[i] = list[i];
    for (int i=0 ; i<19 ; i++)
        for (int j=0 ; j<19 ; j++)
            dataname.map[i][j] = map[i][j];
}

void clearScreen() {
    system("cls");
}

int choseMoveOrWall(const struct DataGame dataname){
    char selection;
    selection = getche();
    if (selection == 27) {
        printf("\nenter name of file:");
        char filename[20];
        scanf("%s",filename);
        SaveGame(&filename,&dataname);
    }
    else if (selection == 'm') return 1;
    else if (selection == 'w') return 2;
    else choseMoveOrWall(dataname);
}

void DeepFirstSearch(int xpoint,int ypoint,int length,char map[][2*length-1],int visit[length-1][length-1]){
    int xv=(xpoint-1)/2,yv=(ypoint-1)/2;
    visit[xv][yv] = 1;
    if (xv<length-2 && map[xpoint+1][ypoint]!='=' && visit[xv+1][yv]!=1) DeepFirstSearch(xpoint+2,ypoint,length,map,visit);
    if (xv>0 && map[xpoint-1][ypoint]!='=' && visit[xv-1][yv]!=1) DeepFirstSearch(xpoint-2,ypoint,length,map,visit);
    if (yv<length-2 && map[xpoint][ypoint+1]!=':' && visit[xv][yv+1]!=1) DeepFirstSearch(xpoint,ypoint+2,length,map,visit);
    if (yv>0 && map[xpoint][ypoint-1]!=':' && visit[xv][yv-1]!=1) DeepFirstSearch(xpoint,ypoint-2,length,map,visit);
    return ;
}

int putWall(const struct DataGame dataname,int numofplayer,int turn ,struct players list[],int length,char map[][2*length-1]){
    int x,y;
    char type;
    printf("\nPlease enter the type ('h' for horizontal & 'v' for vertical) and coordinates of the wall(like this ==> h 3 4):");
    if ( strcmp (list[turn-1].type,"random") == 0) {
        int condition = getRandomNumber(1,4);
        if (condition == 1||condition == 3) {
            type = 'h';
            x = getRandomNumber(1,length-2);
            y = getRandomNumber(0,length-3);
        }
        else if(condition == 2 || condition == 4){
            type = 'v';
            x = getRandomNumber(0,length-3);
            y = getRandomNumber(1,length-2);
        }
    }
    else {
        type = getche();
        if (type == 27) {
            printf("\nenter name of file:");
            char filename[20];
            scanf("%s",filename);
            SaveGame(&filename,&dataname);
        }
        scanf("%d %d",&x,&y);
    }
    int sw=1;
    if (type=='v'){
        if (y<=0 || y>=length-1  || x>=length-2 || map[2*x+3][2*y]==':' || map[2*x+1][2*y]==':'|| map[2*x+2][2*y]=='=') {
            sw=0;
        }
    }
    else if (type=='h') {
        if (x<=0 || x>=length-1 || y>=length-2 || map[2*x][2*y+1]=='=' || map[2*x][2*y+3]=='='|| map[2*x][2*y+2]==':') {
            sw=0;
        }
    }
    if (sw==1) {
        if (type == 'v') {
            map[2 * x + 1][2 * y] = ':';
            map[2 * x + 2][2 * y] = ':';
            map[2 * x + 3][2 * y] = ':';
        } else if (type == 'h') {
            map[2 * x][2 * y + 1] = '=';
            map[2 * x][2 * y + 2] = '=';
            map[2 * x][2 * y + 3] = '=';
        }
    }
    int visit[length-1][length-1];
    int i;
    for (i=0 ; i<length-1 ; i++)
        for (int j=0 ; j<length-1 ; j++)
            visit[i][j]=0;
    DeepFirstSearch(list[0].x,list[0].y,length,map,visit);
    for ( i=0 ; i<length-1 ; i++)
        if (visit[0][i]==1) break;
    if (i>=length-1) sw=0;
    for ( i=0 ; i<length-1 ; i++)
        for (int j=0 ; j<length-1 ; j++)
            visit[i][j]=0;
    DeepFirstSearch(list[1].x,list[1].y,length,map,visit);
    for ( i=0 ; i<length-1 ; i++)
        if (visit[length-2][i]==1) break;
    if (i>=length-1) sw = 0 ;
    if (numofplayer == 4) {
        for (i=0 ; i<length-1 ; i++)
            for (int j=0 ; j<length-1 ; j++)
                visit[i][j]=0;
        DeepFirstSearch(list[2].x,list[2].y,length,map,visit);
        for ( i=0 ; i<length-1 ; i++)
            if (visit[i][length-1]==1) break;
        if (i>=length-1) sw=0;
        for (i=0 ; i<length-1 ; i++)
            for (int j=0 ; j<length-1 ; j++)
                visit[i][j]=0;
        DeepFirstSearch(list[3].x,list[3].y,length,map,visit);
        for ( i=0 ; i<length-1 ; i++)
            if (visit[i][0]==1) break;
        if (i>=length-1) sw=0;
    }
    if (sw==0) {
        sw=0;
        if (type=='v'){
            map[2*x+1][2*y]= 179;
            map[2*x+2][2*y]= 197;
            map[2*x+3][2*y]=  179;
        }
        else if (type=='h'){
            map[2*x][2*y+1]= 196;
            map[2*x][2*y+2]= 197;
            map[2*x][2*y+3]= 196;
        }
    }
    if (sw==1) list[turn-1].numofwall -- ;
    return sw;
}

int playersMovement(struct DataGame dataname,int length , char map[][2*length-1],int turn,struct players list[]){
    int turn2,sw=1,key=1;
    if (turn==1) turn2=2;
    else turn2=1;
    printf("\nenter button to move the player: ");
    char button;
    if ( strcmp (list[turn-1].type,"random") == 0){
        while(key==1){
              int state; state = getRandomNumber(1,4);
              switch (state) {
                 case 1 : button = 72;
                 break;
                 case 2 : button = 80;
                 break;
                 case 3 : button = 77;
                 break;
                 case 4 : button = 75;
              }
              if(button==72){
                  if( list[turn-1].x!=1 && map[(list[turn-1].x)-1][list[turn-1].y]!='=')
                      key=0;
              }
              else if(button==80){
                  if(list[turn-1].x!=(2*length)-3 && map[(list[turn-1].x)+1][list[turn-1].y]!='=')
                      key=0;
              }
              else if(button==77){
                  if(list[turn-1].y!=(2*length)-3 && map[list[turn-1].x][(list[turn-1].y)+1]!=':')
                      key=0;
              }
              else if(button==75){
                  if(list[turn-1].y!=1 && map[list[turn-1].x][(list[turn-1].y)-1]!=':')
                      key=0;
              }
        }
    }
    else button = getch();
    if (button == 27) {
        printf("\nenter name of file:");
        char filename[20];
        scanf("%s",filename);
        SaveGame(&filename,&dataname);
    }
      if (button == 72) {
        if ( list[turn-1].x==1 || map[list[turn-1].x-1][list[turn-1].y]=='=') return 0;
        else if(map[(list[turn-1].x)-2][list[turn-1].y]==list[turn2-1].shape && map[(list[turn-1].x)-3][list[turn-1].y]=='=')return 0;
        else if(map[(list[turn-1].x)-2][list[turn-1].y]==list[turn2-1].shape && list[turn2-1].x==1) return 0;
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
                sw=0;return 1;
            }
        }
    }
    else if (button == 80) {
        if (list[turn-1].x==2*length-3 || map[list[turn-1].x+1][list[turn-1].y]=='=') return 0;
        else if(map[(list[turn-1].x)+2][list[turn-1].y]==list[turn2-1].shape && map[(list[turn-1].x)+3][list[turn-1].y]=='=')return 0;
        else if(map[(list[turn-1].x)+2][list[turn-1].y]==list[turn2-1].shape && list[turn2-1].x==2*length-3) return 0;
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
                sw=0;return 1;
            }
        }
    }
    else if (button == 77) {
        if (list[turn-1].y==2*length-3 || map[list[turn-1].x][list[turn-1].y+1]==':') {sw=0;return 0;}
        else if(map[list[turn-1].x][(list[turn-1].y)+2]==list[turn2-1].shape && map[list[turn-1].x][(list[turn-1].y)+3]==':'){sw=0;return 0;}
        else if(map[list[turn-1].x][(list[turn-1].y)+2]==list[turn2-1].shape && list[turn2-1].y==2*length-3) return 0;
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
                sw=0;return 1;
            }
        }
    }
    else if (button == 75) {
        if (list[turn-1].y==1 || map[list[turn-1].x][list[turn-1].y-1]==':') return 0;
        else if(map[list[turn-1].x][(list[turn-1].y)-2]==list[turn2-1].shape && map[list[turn-1].x][(list[turn-1].y)-3]==':')return 0;
        else if(map[list[turn-1].x][(list[turn-1].y)-2]==list[turn2-1].shape && list[turn2-1].y==1) return 0;
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
                sw=0;return 1;
            }
        }
    }
    if (sw==1) playersMovement(dataname,length, map,turn,list);
}

void putplayer(int length , char map[][2*length-1] ,int x ,int y , char ch) {
    map[x][y] = ch;
}

int iswinner(int length,struct players list[],int turn) {
    int locWin;
    switch (turn) {
        case 1 : locWin = 1;
            break;
        case 2 : locWin = 2 * length - 3;
            break;
        case 3 : locWin = 2 * length -3;
            break;
        case 4 : locWin = 1;
    }
    int sw=0;
    switch (turn) {
        case 1 : if (list[turn-1].x==locWin) sw=1;
            break;
        case 2 : if (list[turn-1].x==locWin) sw=1;
            break;
        case 3 : if (list[turn-1].y==locWin) sw=1;
            break;
        case 4 : if (list[turn-1].y==locWin) sw=1;
    }
    return sw;
}

void exitButton() {
    printf("\n");
    char ch;
    printf("please press Esc button for exit:\n");
    do{
        ch=getch();
    } while (ch !=27);
}

void botplayer (struct DataGame dataname,int numofplayer ,int walls, int length,char map[][2*length-1],struct players list[],int turn) {
    int state; state= getRandomNumber(1,2);
    if (state== 1) {
        playersMovement(dataname,length,map,turn,list);
    }
    else if(state== 2) {
        if(list[turn-1].numofwall>0) putWall(dataname, numofplayer, turn, list, length, map);
        else playersMovement(dataname,length,map,turn,list);
    }
}