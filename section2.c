#include <stdio.h>
#include "allFunctions.c"

struct players;
void emptymap(int n,char mapArray[][n *2 -1]);
void setTextColor(int textColor, int backColor);
void printMap(int side, char map[][2*side-1]);
void printinformation(const struct players list[], int numofplayers);
void clearScreen();
int choseMoveOrWall();
int putWall(int side,char map[][2*side-1]);
int playersMovement(int side , char map[][2*side-1],int turn ,struct players *p);
void putplayer(int length , char map[][2*length-1] ,int x ,int y , char ch);
void exitButton();

int main () {
    printf("Please enter the length of the game map (must be even and between 4 and 20!!!): ");
    int side;
    scanf("%d", &side);
    int numofplayers = 2;
    printf("Enter the number of allowed walls:");
    int walls;
    scanf("%d", &walls);
    struct players list[numofplayers];
    list[0].x = 2 * side - 3, list[1].x = 1;
    list[0].y = list[1].y = ((2 * side - 1) / 2);
    list[0].shape = '*', list[1].shape = 'o';
    list[0].numofwall = list[1].numofwall = walls;
    printf("Enter the first player's name:");
    scanf("%s", list[0].name);
    printf("Enter the name of the second player:");
    scanf("%s", list[1].name);
    char map[2 * side - 1][2 * side - 1];
    emptymap(side, map);
    putplayer(side, map, list[0].x, list[0].y, list[0].shape);
    putplayer(side, map, list[1].x, list[1].y, list[1].shape);
    int i=0;
    while (!iswinner(1,list[0]) && !iswinner(2*side-3,list[1])){
        int turn = (i % 2) + 1;
        clearScreen();
        printinformation(list, numofplayers);
        printf("it`s player %d`s turn.", turn);
        printMap(side, map);
        printf("Press 'm' to move or 'w' to place the wall:");
        int result = choseMoveOrWall();
        if (result == 1) {
            int a= playersMovement(side,map,turn, list);
            if (a==0) i--;
        }
        else if (result == 2) {
            if (list[turn-1].numofwall==0) i--;
            else {
                if (putWall(side, map) == 1) {
                    list[turn - 1].numofwall--;
                }
                else i--;
            }
        }
        i++;
    }
    if (iswinner(1,list[0])) {
        clearScreen();
        printinformation(list, numofplayers);
        printf("player %s is winner.",list[0].name);
        printMap(side, map);
    }
    else {
        clearScreen();
        printinformation(list, numofplayers);
        printf("player %s is winner.",list[1].name);
        printMap(side, map);
    }
    exitButton();
    return 0;
}
