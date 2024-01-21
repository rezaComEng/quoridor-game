#include <stdio.h>
#include "allFunctions.c"
#include <string.h>

int main () {
    srand(1000*time(NULL)) ;
    int length = Length ;
    int side = 2 * Length -1 ;
    char map[side][side];
    emptymap(length,map) ;
    struct DataGame datagame;
    char userAnswer[5];
    FILE* filecount = fopen("filecount.dat","r+b") ;
    FILE* filenames = fopen("filenames.dat","r+b") ;
    int numofplayers=2 , turn ;
    struct players list[4];
    printf ("Do you want to load one of your last games?(answer with yes or no) :");
    scanf("%s",userAnswer);
    int count;
    fseek(filecount,0,SEEK_SET);
    fread(&count,sizeof(int),1,filecount);
    if(strcmp(userAnswer,"yes")==0 && count!=0) {
        char name[20];
        int i=1;
        printf("list file names:\n");
        fread(name,sizeof(name),1,filenames);
        while( !feof(filenames) ) {
            printf("%d) %s\n",i,name);
            fread(name,sizeof(name),1,filenames);
            i++;
        }
        printf("which file do you want to load?(enter the number of file.):");
        int anser;
        scanf("%d",&anser);
        fseek(filenames,anser-1,SEEK_SET);
        fread(name, sizeof(name),1,filenames);
        loadGame(name,&datagame);
        receiveInformation(turn,datagame,list,map);
        fclose(filenames);
        fclose(filecount);
    }
    else {
        printf ("please enter number of the players(2 or 4):");
        do {
            if (numofplayers != 2 && numofplayers != 4) {
                printf ("error it`s wrong button!\n");
            }
            scanf ("%d",&numofplayers);
        } while (numofplayers != 2 && numofplayers != 4);
        datagame.numofplayers = numofplayers;
        printf("Enter the number of allowed walls:");
        int walls;
        scanf("%d", &walls);
        for (int i=0 ; i<numofplayers ; i++) {
            printf("choose human or random: ");
            scanf("%s", list[i].type);
            list[i].numofwall = walls;
            if (strcmp(list[i].type, "human") == 0) {
                printf("enter the name of the player: ");
                scanf("%s", list[i].name);
            } else strcpy(list[i].name, "random");
            switch (i) {
                case 0 : {
                    list[i].shape = '#';
                    list[i].x = side - 3, list[i].y = (side / 2) -1;
                    break;
                }
                case 1 : {
                    list[i].shape = '*';
                    list[i].x = 1, list[i].y = (side / 2)-1;
                    break;
                }
                case 2 : {
                    list[i].shape = '&';
                    list[i].x = (side / 2)-1, list[i].y = 1;
                    break;
                }
                case 3 : {
                    list[i].shape = '@';
                    list[i].x = (side / 2)-1, list[i].y = side - 3;
                }
            }
            putplayer(length,map,list[i].x,list[i].y,list[i].shape);
            turn=1;
        }
    }
    do {
        clearScreen();
        printinformation(list, numofplayers);
        printf("It is player %d's turn",turn);
        printMap(length, map);
        printf("for save the game press Esc button.\n");
        saveInformation(turn,datagame,list,map);
        if ( strcmp ( list[turn-1].type , "random") == 0){
            botplayer(filecount,filenames,datagame,numofplayers,length,map,list,turn);
        }
        else {
            printf("Press 'm' to move or 'w' to place the wall:");
            int resulte = choseMoveOrWall(filecount,filenames,datagame);
            if (resulte==1) {
                if ( playersMovement(filecount,filenames,datagame , length, map, turn,list)==0  ) turn-- ;
            }
            else if (resulte == 2) {
                if (list[turn-1].numofwall<=0) turn--;
                else {
                    if (putWall(filecount,filenames,datagame,numofplayers,turn,list,length, map) == 0) turn-- ;
                }
            }
        }
        if (iswinner(length,list,turn)==1) break;
        turn++;
        if ( turn>numofplayers ) turn = (turn%numofplayers);
    } while (1);
    clearScreen();
    printinformation(list, numofplayers);
    printMap(length, map);
    printf("player %d is winner.",turn);
    exitButton();
    return 0;
}
