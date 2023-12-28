//print map whit color

#include <stdio.h>
#include <windows.h>
#include "EmptyMap.c"

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
                setTextColor(0,1);
                printf(" %c ",map[i][j]);
            }
            else if (i%2==0 || j%2==0) {
                setTextColor(5,1);
                if (map[i][j]==215 || map[i][j]==205 || map[i][j]==216 || map[i][j]==186) setTextColor(4,4);
                printf(" %c ",map[i][j]);
            }
            else {
                setTextColor(15,3);
                printf(" %c ",map[i][j]);
            }
        }
        printf("\n");
    }
    setTextColor(7,0);
    printf("\n");
}