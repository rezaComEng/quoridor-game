#include <stdio.h>
#include "allFunctions.c"


int main () {
    srand(1000*time(NULL));
    int length=Length;
    int side = 2 * Length -1;
    char map[side][side];
    emptymap(length,map);
    char filename[]="information";
    struct DataGame datagame;
    int numofplayers=2 , turn ;
    printf ("please enter number of the players(2 or 4):");
    do {
        if (numofplayers != 2 && numofplayers != 4) {
            printf ("error it`s wrong button!\n");
        }
        scanf ("%d",&numofplayers);
    } while (numofplayers != 2 && numofplayers != 4);
    struct players list[numofplayers];
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
    do {
        clearScreen();
        printinformation(list, numofplayers);
        printf("It is player %d's turn",turn);
        printMap(length, map);
        printf("for save the game press Esc button.\n");
        saveInformation(turn,datagame,list,map);
        if ( strcmp ( list[turn-1].type , "random") == 0){
            botplayer(datagame,numofplayers,walls,length,map,list,turn);
        }
        else {
            printf("Press 'm' to move or 'w' to place the wall:");
            int resulte = choseMoveOrWall(datagame);
            if (resulte==1) {
                if ( playersMovement(datagame , length, map, turn,list)==0  ) turn-- ;
            }
            else if (resulte == 2) {
                if (list[turn-1].numofwall<=0) turn--;
                else {
                    if (putWall(datagame,numofplayers,turn,list,length, map) == 0) turn-- ;
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