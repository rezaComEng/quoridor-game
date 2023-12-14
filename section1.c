
#include <stdio.h>
#include <stdlib.h>
#include "EmptyMap.c"

int main(){
    int side;
    int x1,y1,x2,y2;
    int numofwall1,numofwall2;
    scanf ("%d",&side);
    int map[2*side-1][2*side-1];
    emptymap(side,map);
    scanf ("%d %d",&x1,&y1);
    map[2*x1-1][2*y1-1]='*';
    scanf ("%d %d",&x2,&y2);
    map[2*x2-1][2*y2-1]='@';
    scanf ("%d",&numofwall1);
    for (int i=0 ; i<numofwall1 ; i++){
        int xwall,ywall;
        char typewall;
        scanf ("%d %d %c",&xwall,&ywall,&typewall);

    }
    scanf ("%d",&numofwall1);
    for (int i=0 ; i<numofwall2 ; i++){
        int xwall,ywall;
        char typewall;
        scanf ("%d %d %c",&xwall,&ywall,&typewall);
    }
    for (int i=0 ; i<side*2-1 ; i++) {
        for (int j = 0; j < 2 * side - 1; j++)
            printf("%c  ", map);
        printf("\n");
    }
    return 0;
}