#include <stdio.h>
#include "allFunctions.c"


int main () {
    printf("Please enter the length of the game map (must be even and between 4 and 20!!!): ");
    int length;
    scanf("%d", &length);
    int side = 2* length -1;
    char map[side][side];
    emptymap(length,map);
    int numofplayers = 2;
    printf ("please enter number of the players(2 or 4):");
    do {
        if (numofplayers != 2 && numofplayers != 4) {
            printf ("error it`s wrong button!\n");
        }
        scanf ("%d",&numofplayers);
    } while (numofplayers != 2 && numofplayers != 4);
    printf("Enter the number of allowed walls:");
    int walls;
    scanf("%d", &walls);
    struct players list[numofplayers];
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
                list[i].x = side - 2, list[i].y = side / 2;
                break;
            }
            case 1 : {
                list[i].shape = '*';
                list[i].x = 1, list[i].y = side / 2;
                break;
            }
            case 2 : {
                list[i].shape = '&';
                list[i].x = side / 2, list[i].y = 1;
                break;
            }
            case 3 : {
                list[i].shape = '@';
                list[i].x = side / 2, list[i].y = side - 2;
            }
        }
        putplayer(length,map,list[i].x,list[i].y,list[i].shape);
    }
    int turn,i=0;
    int areiswin=0;
    do {
        turn = (i%numofplayers) + 1 ;
        clearScreen();
        printinformation(list, numofplayers);
        printf("it`s player %s`s turn.",list[turn-1].name);
        printMap(length, map);
        if ( strcmp ( list[turn-1].type , "random") == 0){
            botplayer(length,map,list,turn);
        }
        else {
            printf("Press 'm' to move or 'w' to place the wall:");
            int resulte = choseMoveOrWall();
            if (resulte==1) {
                int a = playersMovement(length,map,turn,list);
                if (a == 0) i--;
            }
            else if (resulte == 2) {
                if (list[turn-1].numofwall==0) i--;
                else {
                    if (putWall(turn,list,length, map) == 1) {
                        list[turn - 1].numofwall -- ;
                    }
                    else i--;
                }
            }
        }
        if (iswinner(length,list,turn)==1) areiswin=1;
        i++;
    } while (!areiswin);
    clearScreen();
    printinformation(list, numofplayers);
    printMap(length, map);
    printf("%s is winner.",list[turn-1].name);
    exitButton();
    return 0;
}