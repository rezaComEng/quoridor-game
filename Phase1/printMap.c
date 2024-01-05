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
        printf("\n");
    }
    setTextColor(7,0);
    printf("\n");
}