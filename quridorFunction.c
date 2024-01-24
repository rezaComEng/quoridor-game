#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

#define Length 9;

struct Players {
    char type[10];
    char Name[20];
    char Shape;
    int NumOfWall;
    int x,y;
};

struct DataGame{
    int Turn ;
    int NumOfPlayers ;
    char map[19][19] ;
    struct Players list[4];
//    char filename[20];
};

void deleteFromFile(size_t size, int organ, FILE* filename) {
    FILE* tempfile = fopen("temp.dat", "w+b");
    if (!tempfile) {
        printf("Failed to open temporary file.\n");
        return;
    }
    char *temp = (char*)malloc(size);
    if (!temp) {
        printf("Memory allocation failed.\n");
        fclose(tempfile);
        return;
    }
    fseek(filename,0,SEEK_SET);
    fread((void *)temp,size,1,filename);
    for (int i=0 ; i<organ-1 && !feof(filename) ; i++) {
        fwrite((void *)temp,size,1,tempfile);
        fread((void *)temp,size,1,filename);
    }
    fread((void *)temp,size,1,filename);
    while ( !feof(filename) ) {
        fwrite((void *)temp,size,1,tempfile);
        fread((void *)temp,size,1,filename);
    }
    free(temp);
    fclose(filename);
    fclose(tempfile);

    rename(tempfile, filename);
    remove(filename);
}

void emptymap(int length,struct DataGame *data){
    for (int i=0 ; i<2 * length +1 ; i++){
        for (int j = 0; j < 2 * length +1; j++) {
            if (i%2==0 && j%2==1) data->map[i][j] = 196;
            else if (i % 2 == 1 && j % 2 == 0) data->map[i][j] =179;
            else if (i % 2 == 1 && j % 2 == 1) data->map[i][j] =' ';
            else if (i % 2 == 0 && j % 2 == 0) {
                if(i==0 && j==0) data->map[i][j]=218;
                else if (i==0 && j==2 * length) data->map[i][j]=191;
                else if (i==2 * length && j==0) data->map[i][j]=192;
                else if (i==2 * length && j==2 * length) data->map[i][j]=217;
                else if (j==0 && i%2==0) data->map[i][j]=179;
                else if (i==0 && j%2==0) data->map[i][j]=196;
                else if (j==2 * length && i%2==0) data->map[i][j]=179;
                else if (i==2 * length && j%2==0) data->map[i][j]=196;
                else data->map[i][j]=197;
            }
        }
    }
}

void InitializeData (struct DataGame *data) {
    int Request, sw=0;
    while (sw == 0) {
        system("cls");
        printf("1) NewGame\n2) LoadGame\n") ;
        while (1) {
            scanf ( "%d" , &Request ) ;
            if (Request==1 || Request==2) break;
        }
        switch (Request) {
            case 1 :{
//                strcpy(data->filename,"empty");
                data->Turn = 1;
                printf("chose number of players (2 or 4):\n");
                while (1) {
                    scanf("%d",&data->NumOfPlayers);
                    if (data->NumOfPlayers==2 || data->NumOfPlayers==4) break;
                }
                printf("please enter number of walls:\n");
                int numWalls,length=Length;
                emptymap(length,data);
                scanf("%d",&numWalls);
                for (int i=0 ; i<data->NumOfPlayers ; i++){
                    data->list[i].NumOfWall = numWalls;
                }
                for (int i=0 ; i<data->NumOfPlayers ; i++){
                    switch (i) {
                        case 0 :{
                            data->list[i].x = 2*length -1;
                            data->list[i].y = length;
                            data->list[i].Shape = 147;
                            printf("enter the type of the players(1. human & 2. bot ):\n");
                            while (1) {
                                int order;
                                scanf("%d",&order);
                                if (order == 1) {
                                    strcpy(data->list[i].type,"human");
                                    printf("enter name of the player:\n");
                                    scanf("%s",data->list[i].Name);
                                    break;
                                }
                                else if (order == 2) {
                                    strcpy(data->list[i].type, "random");
                                    strcpy(data->list[i].Name, "bot1");
                                    break;
                                }
                            }
                            break;
                        }
                        case 1 :{
                            data->list[i].x = 1;
                            data->list[i].y = length;
                            data->list[i].Shape = 36;
                            printf("enter the type of the players(1. human & 2. bot ):\n");
                            while (1) {
                                int order;
                                scanf("%d",&order);
                                if (order == 1) {
                                    strcpy(data->list[i].type,"human");
                                    printf("enter name of the player:\n");
                                    scanf("%s",data->list[i].Name);
                                    break;
                                }
                                else if (order == 2) {
                                    strcpy(data->list[i].type, "random");
                                    strcpy(data->list[i].Name, "bot2");
                                    break;
                                }
                            }
                            break;
                        }
                        case 2 :{
                            data->list[i].x = length;
                            data->list[i].y = 1;
                            data->list[i].Shape = 35;
                            printf("enter the type of the players(1. human & 2. bot ):\n");
                            while (1) {
                                int order;
                                scanf("%d",&order);
                                if (order == 1) {
                                    strcpy(data->list[i].type,"human");
                                    printf("enter name of the player:\n");
                                    scanf("%s",data->list[i].Name);
                                    break;
                                }
                                else if (order == 2) {
                                    strcpy(data->list[i].type, "random");
                                    strcpy(data->list[i].Name, "bot3");
                                    break;
                                }
                            }
                            break;
                        }
                        case 3 :{
                            data->list[i].x = length;
                            data->list[i].y = 2*length -1;
                            data->list[i].Shape = 42;
                            printf("enter the type of the players(1. human & 2. bot ):\n");
                            while (1) {
                                int order;
                                scanf("%d",&order);
                                if (order == 1) {
                                    strcpy(data->list[i].type,"human");
                                    printf("enter name of the player:\n");
                                    scanf("%s",data->list[i].Name);
                                    break;
                                }
                                else if (order == 2) {
                                    strcpy(data->list[i].type, "random");
                                    strcpy(data->list[i].Name, "bot4");
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    data->map[data->list[i].x][data->list[i].y] = data->list[i].Shape;
                }
                sw=1;
                break;
            }
            case 2 :{
                FILE* filenames = fopen("filenames","r+b");
                if (!filenames){
                    remove(filenames);
                    printf("there isn`t any game to load.(press 1 to play a nuw game).\n");
                }
                else {
                    int i=0;
                    char name[20];
                    fread(name,sizeof(name),1,filenames);
                    while ( !feof(filenames) ) {
                        i++;
                        printf("%d. %s\n",i,name);
                        fread(name,sizeof(name),1,filenames);
                    }
                    printf("enter num of file that you want:\n");
                    int order;
                    while(1){
                        scanf("%d",&order);
                        if (order>0 && order<=i) break;
                    }
                    fseek(filenames,(order-1) * sizeof(name),SEEK_SET);
                    fread(name,sizeof(name),1,filenames);
                    fclose(filenames);
                    FILE* fileData = fopen(name,"rb");
                    if (!fileData){
                        printf("there isn`t that file.\n");
                        deleteFromFile(sizeof(name),order,filenames);
                        sleep(1);
                    } else {
                        fread(data,sizeof(*data),1,fileData);
                        sw=1;
                    }
                }
                break;
            }
        }
    }
}

int getRandomNumber(int lower, int upper) {
    int range = upper - lower + 1;
    int randomNumber = rand();
    int scaledNumber = (randomNumber / (RAND_MAX + 1.0)) * range;
    return scaledNumber + lower;
}

void setTextColor(int textColor, int backColor) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = backColor << 4 | textColor;
    SetConsoleTextAttribute(consoleHandle , colorAttribute);
}

void printMap(int length , struct DataGame data){
    printf("\n");
    for (int i=-1 ; i<2*length+1 ; i++) {
        for (int j=-1 ; j<2*length+1 ; j++) {
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
                if (i==0 || j==0 || i==2*length || j==2*length ) {
                    setTextColor(7,0);
                    printf(" %c ",data.map[i][j]);
                }
                else if (i%2==0 || j%2==0) {
                    setTextColor(5,0);
                    if (data.map[i][j]=='=' || data.map[i][j]==':') setTextColor(4,0);
                    printf(" %c ",data.map[i][j]);
                }
                else {
                    setTextColor(0,8);
                    printf(" %c ",data.map[i][j]);
                }
            }
        }
        printf("\n");
    }
    setTextColor(7,0);
    printf("\n");
}

void printinformation(const struct DataGame data) {
    for (int i = 0; i < data.NumOfPlayers; i++) {
        setTextColor(1,0);
        printf("player %d information: \n",i+1);
        setTextColor(2,0);
        printf("player`s name: ");
        setTextColor(4,0);
        printf("%s \n",data.list[i].Name);
        setTextColor(2,0);
        printf("shape of the player: ");
        setTextColor(4,0);
        printf("%c \n",data.list[i].Shape);
        setTextColor(2,0);
        printf("number of Walls: ");
        setTextColor(4,0);
        printf("%d \n",data.list[i].NumOfWall);
        setTextColor(7,0);
    }
}

int choseMoveOrWall(const struct DataGame data){
    char selection;
    if ( strcmp(data.list[data.Turn-1].type,"random") == 0 ){
        sleep(1);
        int rand = getRandomNumber(1,4);
        if (rand == 1 || rand == 3) selection = 'm';
        else selection = 'w';
    }
    else {
        printf("for exit and save the game press Esc button.\n");
        printf("Specify your mode(m for move & w for wall).\n");
        while(1){
            selection = getche();
            if (selection!='m' && selection!='w' && selection!=27){
                fprintf(stderr, "wrong button!\n");
            } else break;
        }
    }
    if (selection == 27) {
        printf("eenter name of file:\n");
        char Fname[20];
//        if ( strcmp(data.filename,"empty") != 0 ){
//            strcpy(Fname , data.filename) ;
//        } else {
        scanf("%s",Fname);
//        }
//        strcpy(data.filename,Fname);
        FILE* filenames = fopen("filenames","ab");
        fwrite(Fname,sizeof(Fname),1,filenames);
        FILE* fileData = fopen(Fname,"wb");
        fwrite(&data,sizeof(data),1,fileData);
        fclose(filenames);
        fclose(fileData);
        exit(0);
    }
    else if (selection == 'm') return 1;
    else if (selection == 'w') return 2;
}

void DeepFirstSearch(int x,int y,struct DataGame data,int length,int visit[length][length]){
    int xv=(x-1)/2,yv=(y-1)/2;
    visit[xv][yv] = 1;
    if (xv<length-1 && data.map[x+1][y]!='=' && visit[xv+1][yv]!=1) DeepFirstSearch(x+1,y,data,length,visit);
    if (xv>0 && data.map[x-1][y]!='=' && visit[xv-1][yv]!=1) DeepFirstSearch(x-1,y,data,length,visit);
    if (yv<length-1 && data.map[x][y+1]!=':' && visit[xv][yv+1]!=1) DeepFirstSearch(x,y+1,data,length,visit);
    if (yv>0 && data.map[x][y-1]!=':' && visit[xv][yv-1]!=1) DeepFirstSearch(x,y-1,data,length,visit);
    return ;
}

int putWall(struct DataGame* data){
    int length = Length;
    int x,y;
    char type;
    if ( strcmp (data->list[data->Turn-1].type,"random") == 0) {
        int condition = getRandomNumber(1,4);
        if (condition == 1||condition == 3) {
            type = 'h';
            x = getRandomNumber(1,length-1);
            y = getRandomNumber(0,length-2);
        }
        else if(condition == 2 || condition == 4){
            type = 'v';
            x = getRandomNumber(0,length-2);
            y = getRandomNumber(1,length-1);
        }
    }
    else {
        printf("\nenter coordinates of the wall and type ('h' for horizontal & 'v' for vertical) (like this ==>3 4 h):");
        while (1){
            scanf("%d %d %c",&x,&y,&type);
            if (type == 'v' || type == 'h') break;
        }
    }
    int sw=1;
    if (type=='v'){
        if (y<=0 || y>=length  || x>=length-1 || data->map[2*x+3][2*y]==':' || data->map[2*x+1][2*y]==':'|| data->map[2*x+2][2*y]=='=') {
            sw=0;
        }
    }
    else if (type=='h') {
        if (x<=0 || x>=length || y>=length-1 || data->map[2*x][2*y+1]=='=' || data->map[2*x][2*y+3]=='='|| data->map[2*x][2*y+2]==':') {
            sw=0;
        }
    }
    if (sw==1) {
        if (type == 'v') {
            data->map[2 * x + 1][2 * y] = ':';
            data->map[2 * x + 2][2 * y] = ':';
            data->map[2 * x + 3][2 * y] = ':';
        } else if (type == 'h') {
            data->map[2 * x][2 * y + 1] = '=';
            data->map[2 * x][2 * y + 2] = '=';
            data->map[2 * x][2 * y + 3] = '=';
        }
    }
    int visit[length][length];
    int i;
    for (i=0 ; i<length ; i++)
        for (int j=0 ; j<length ; j++)
            visit[i][j]=0;
    DeepFirstSearch(data->list[0].x,data->list[0].y,*data,length,visit);
    for ( i=0 ; i<length ; i++)
        if (visit[0][i]==1) break;
    if (i>=length) sw=0;
    for ( i=0 ; i<length ; i++)
        for (int j=0 ; j<length ; j++)
            visit[i][j]=0;
    DeepFirstSearch(data->list[1].x,data->list[1].y,*data,length,visit);
    for ( i=0 ; i<length ; i++)
        if (visit[length-1][i]==1) break;
    if (i>=length) sw = 0 ;
    if (data->NumOfPlayers == 4) {
        for (i=0 ; i<length ; i++)
            for (int j=0 ; j<length ; j++)
                visit[i][j]=0;
        DeepFirstSearch(data->list[2].x,data->list[2].y,*data,length,visit);
        for ( i=0 ; i<length ; i++)
            if (visit[i][length]==1) break;
        if (i>=length) sw=0;
        for (i=0 ; i<length ; i++)
            for (int j=0 ; j<length ; j++)
                visit[i][j]=0;
        DeepFirstSearch(data->list[3].x,data->list[3].y,*data,length,visit);
        for ( i=0 ; i<length ; i++)
            if (visit[i][0]==1) break;
        if (i>=length) sw=0;
    }
    if (sw==0) {
        if (type=='v'){
            data->map[2*x+1][2*y]= 179;
            data->map[2*x+2][2*y]= 197;
            data->map[2*x+3][2*y]=  179;
        }
        else if (type=='h'){
            data->map[2*x][2*y+1]= 196;
            data->map[2*x][2*y+2]= 197;
            data->map[2*x][2*y+3]= 196;
        }
    }
    if (sw==1) data->list[data->Turn-1].NumOfWall -- ;
    return sw;
}

int playersMovement(struct DataGame *data){
    int length= Length;
    int sw=0;
    char button;
    if ( strcmp (data->list[data->Turn-1].type,"random") == 0){
            int state = getRandomNumber(1,4);
            switch (state) {
                case 1 : button = 72;
                    break;
                case 2 : button = 80;
                    break;
                case 3 : button = 77;
                    break;
                case 4 : button = 75;
            }
    }
    else while (1) {
        button = getch();
        if (button == 72 || button == 80 || button == 77 || button == 75 ) break;
    }
    if (button == 72) {
        if ( ( data->list[data->Turn-1].x!=1 && data->map[data->list[data->Turn-1].x-1][data->list[data->Turn-1].y]!='=') &&
        (data->map[(data->list[data->Turn-1].x)-2][data->list[data->Turn-1].y]==' ' || data->map[(data->list[data->Turn-1].x)-3][data->list[data->Turn-1].y]!='=') &&
                (data->map[(data->list[data->Turn-1].x)-2][data->list[data->Turn-1].y]==' ' || (data->list[data->Turn-1].x)-2!=1) ){
            data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y] = ' ';
            data->list[data->Turn-1].x -= 2;
            if (data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y]!=' '){
                data->list[data->Turn-1].x -= 2;
                if (data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y]==' ') sw=1;
            } else sw=1;
        }
        else {

        }
    }
    else if (button == 80) {
        if ((data->list[data->Turn-1].x!=2*length-1 && data->map[data->list[data->Turn-1].x+1][data->list[data->Turn-1].y]!='=') &&
        (data->map[(data->list[data->Turn-1].x)+2][data->list[data->Turn-1].y]==' ' || data->map[(data->list[data->Turn-1].x)+3][data->list[data->Turn-1].y]!='=') &&
        (data->map[(data->list[data->Turn-1].x)+2][data->list[data->Turn-1].y]==' ' || (data->list[data->Turn-1].x)+2!=2*length-1))
        {
            data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y]=' ';
            data->list[data->Turn-1].x += 2;
            if (data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y]!=' '){
                data->list[data->Turn-1].x += 2;
                if (data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y]==' ') {
                    sw=1;
                }
            }
            else {
                sw=1;
            }
        }
    }
    else if (button == 77) {
        if ( data->list[data->Turn-1].y!=2*length-1 && data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y+1]!=':' &&
        (data->map[data->list[data->Turn-1].x][(data->list[data->Turn-1].y)+2]==' ' || data->map[data->list[data->Turn-1].x][(data->list[data->Turn-1].y)+3]!=':') &&
        (data->map[data->list[data->Turn-1].x][(data->list[data->Turn-1].y)+2]==' ' || (data->list[data->Turn-1].y)+2!=2*length-1) )
        {
            data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y] = ' ';
            data->list[data->Turn-1].y += 2;
            if (data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y] != ' '){
                data->list[data->Turn-1].y += 2;
                if (data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y]==' ') {
                    sw=1;
                }
            }
            else {
                sw=1;
            }
        }
    }
    else if (button == 75) {
        if ( (data->list[data->Turn-1].y!=1 && data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y-1]!=':') &&
        (data->map[data->list[data->Turn-1].x][(data->list[data->Turn-1].y)-2]==' ' || data->map[data->list[data->Turn-1].x][(data->list[data->Turn-1].y)-3]!=':') &&
        (data->map[data->list[data->Turn-1].x][(data->list[data->Turn-1].y)-2]==' ' || (data->list[data->Turn-1].y)-2!=1) )
        {
            data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y]=' ';
            data->list[data->Turn-1].y -= 2;
            if (data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y]!=' '){
                data->list[data->Turn-1].y -= 2;
                if (data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y]==' ') {
                    sw=1;
                }
            }
            else {
                sw=1;
            }
        }
    }
    data->map[data->list[data->Turn-1].x][data->list[data->Turn-1].y]=data->list[data->Turn-1].Shape;
    if (sw==0) {
        playersMovement(data);
        return 0;
    }
    else return 1;
}

int iswinner(int length,struct DataGame data) {
    int locWin;
    switch (data.Turn) {
        case 1 : locWin = 1;
            break;
        case 2 : locWin = 2 * length - 1;
            break;
        case 3 : locWin = 2 * length -1;
            break;
        case 4 : locWin = 1;
    }
    int sw=0;
    switch (data.Turn) {
        case 1 : if (data.list[data.Turn-1].x==locWin) sw=1;
            break;
        case 2 : if (data.list[data.Turn-1].x==locWin) sw=1;
            break;
        case 3 : if (data.list[data.Turn-1].y==locWin) sw=1;
            break;
        case 4 : if (data.list[data.Turn-1].y==locWin) sw=1;
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

int magicBox(struct DataGame *data){
    int length = Length;
    int rand = getRandomNumber(1,2);
    switch(rand){
        case 1 :{
            rand = getRandomNumber(1 , 2);
            switch (rand) {
                case 1 :{
                    rand = getRandomNumber(1,3);
                    switch (rand) {
                        case 1:{
                            data->list[data->Turn-1].NumOfWall += 2;
                            printf("Two were added to your wall capacity.\n");
                            break;
                        }
                        case 2:{
                            data->list[data->Turn-1].NumOfWall += 3;
                            printf("Three were added to your wall capacity.\n");
                            break;
                        }
                        case 3:{
                            data->list[data->Turn-1].NumOfWall += 5;
                            printf("Five were added to your wall capacity.\n");
                            break;
                        }
                    }
                    break;
                }
                case 2 :{
                    rand = getRandomNumber(1,2);
                    switch (rand) {
                        case 1:{
                            for (int i=0 ; i<data->NumOfPlayers ; i++){
                                if (i+1 != data->Turn && data->list[i].NumOfWall>=1) data->list[i].NumOfWall --;
                            }
                            data->list[data->Turn].NumOfWall += 1;
                            printf("A wall has been added to you & a wall has been removed from your opponents.\n");
                            break;
                        }
                        case 2:{
                            for (int i=0 ; i<data->NumOfPlayers ; i++){
                                if ( i+1 != data->Turn ) {
                                    if ( data->list[i].NumOfWall > 1 ) data->list[i].NumOfWall -= 2;
                                    else data->list[i].NumOfWall = 0;
                                }
                            }
                            data->list[data->Turn].NumOfWall += 2;
                            printf("Two walls have been added to you & two walls have been removed from your opponents.\n"
                                   ""
                                   "");
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
        case 2:{
            rand = getRandomNumber(1,3 );
            switch (rand) {
                case 1 :{
                    for (int i=1 ; i<2*length ; i++){
                        for (int j = 1 ; j<2*length ; j++){
                            if (data->map[i][j] == ':') data->map[i][j] = 179;
                            if (data->map[i][j] == '=' && j%2==1) data->map[i][j] = 196;
                            if (data->map[i][j] == '=' && j%2==0) data->map[i][j] = 197;
                        }
                    }
                    printf("All Of Walls were removed.\n");
                    break;
                }
                case 2:{
                    rand = getRandomNumber(1,3);
                    switch (rand) {
                        case 1:{
                            if ( data->list[data->Turn-1].NumOfWall > 1) data->list[data->Turn-1].NumOfWall -=2;
                            else data->list[data->Turn-1].NumOfWall = 0;
                            break;
                            printf("Two Walls Were Decreased From You`r Wall Capacity.\n");
                        }
                        case 2:{
                            if ( data->list[data->Turn-1].NumOfWall > 2) data->list[data->Turn-1].NumOfWall -= 3;
                            else data->list[data->Turn-1].NumOfWall = 0;
                            printf("Three Walls Were Decreased From You`r Wall Capacity.\n");
                            break;
                        }
                        case 3:{
                            if ( data->list[data->Turn-1].NumOfWall > 4) data->list[data->Turn-1].NumOfWall -= 5;
                            else data->list[data->Turn-1].NumOfWall = 0;
                            printf("Five Walls Were Decreased From You`r Wall Capacity.\n");
                            break;
                        }
                    }
                    break;
                }
                case 3:{
                    rand = getRandomNumber(1,2);
                    switch (rand) {
                        case 1:{
                            return 1 ;
                            break;
                        }
                        case 2:{
                            return 2;
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
    return 0;
}

void playGame(struct DataGame* data){
    int length=Length;
    int block[4]={0,0,0,0};
    int lastTern = 0 , newTern = 2;
    while(1){
        newTern = data->Turn;
        system("cls");
        setTextColor(5,0);
        printf("The magic box chose this for you:\n");
        if (lastTern != newTern) {
            block[data->Turn-1] = magicBox(data);
            if (block[data->Turn-1] != 0) {
                block[data->Turn-1] -- ;
                data->Turn ++ ;
                if (data->Turn > data->NumOfPlayers) {
                    data->Turn -= data->NumOfPlayers;
                }
            }
        }
        lastTern = data->Turn ;
        setTextColor(7,0);
        printinformation(*data);
        for (int i=0 ; i<4 ; i++) {
            if (block[i] != 0 ){
                printf ("Player %d is blocked for the next %d rounds.\n",i+1,block[i]);
            }
        }
        printMap(length,*data);
        setTextColor(9,0);
        printf("It is player %d's turn.\n",data->Turn);
        setTextColor(7,0);
        if ( choseMoveOrWall(*data) == 2 && data->list[data->Turn-1].NumOfWall>0) {
            if ( !putWall(data) ) data->Turn --;
        } else {
            printf("\nenter button to move the player: ");
            if ( !playersMovement(data) ) data->Turn --;
        }
        if (iswinner(length,*data)) {
            system("cls");
            printinformation(*data);
            printMap(length,*data);
            setTextColor(9,0);
            printf("player #%d wins.\n",data->Turn);
            setTextColor(7,0);
            break;
        }
        data->Turn ++;
        if (data->Turn > data->NumOfPlayers) {
            data->Turn -= data->NumOfPlayers;
        }
    }
    exitButton();
}