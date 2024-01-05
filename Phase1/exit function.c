#include <stdio.h>
#include <conio.h>

void exitButton() {
    printf("\n");
    char ch;
    printf("please press Esc button for exit:\n");
    do{
        ch=getch();
    } while (ch !=27);
}