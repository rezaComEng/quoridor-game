
#include <stdio.h>
#include <conio.h>
#pragma "EmptyMap.c"
#include "printMap.c"
#include "exit function.c"


int main(){
    int side;
    int x1,y1,x2,y2;
    int numofwall1,numofwall2;
    printf ("enter the side size of the map:");
    scanf ("%d",&side);
    char map[2*side-1][2*side-1];
    emptymap(side,map);
    printf("enter the coordinates of the first point(like this:1 2):");
    scanf ("%d %d",&x1,&y1);
    map[2*x1+1][2*y1+1]='*';
    printf("enter the coordinates of the second point(like this:1 2):");
    scanf ("%d %d",&x2,&y2);
    map[2*x2+1][2*y2+1]='@';
    printf("Enter the number of walls for the first player:");
    scanf ("%d",&numofwall1);
    for (int i=0 ; i<numofwall1 ; i++) {
        int xwall,ywall;
        char typewall;
        printf("Enter the coordinates and type of wall %d(like this:1 1 H or 2 2 V):",i+1);
        scanf ("%d %d %c",&xwall,&ywall,&typewall);
        if (typewall=='H') {
            for(int j=2*ywall+1 ; j<=2*ywall+3 ; j++) {
                if (j%2==0) map[2*xwall][j]=216;
                else map[2*xwall][j]=205;
            }
        }
        else if (typewall=='V') {
            for(int k=2*xwall+1 ; k<=2*xwall+3 ; k++) {
                if (k%2==0) map[k][2*ywall]=215;
                else map[k][2*ywall]=186;
            }
        }
    }
    printf("Enter the number of walls for the second player:");
    scanf ("%d",&numofwall2);
    for (int i=0 ; i<numofwall2 ; i++){
        int xwall,ywall;
        char typewall;
        printf("Enter the coordinates and type of wall %d(like this:1 1 H or 2 2 V):",i+1);
        scanf ("%d %d %c",&xwall,&ywall,&typewall);
        if (typewall=='H') {
            for(int j=2*ywall+1 ; j<=2*ywall+3 ; j++) {
                if (j%2==0) map[2*xwall][j]=216;
                else map[2*xwall][j]=205;
            }
        }
        else if (typewall=='V') {
            for(int k=2*xwall+1 ; k<=2*xwall+3 ; k++) {
                if (k%2==0) map[k][2*ywall]=215;
                else map[k][2*ywall]=186;
            }
        }
    }
    printf("\n");
    printMap(side, map);
    exitButton();
    return 0;
}