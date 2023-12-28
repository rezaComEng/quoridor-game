#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void emptymap(int n,char mapArray[][n *2 -1]){
    int side=2*n-1;
    for (int i = 0; i < side; i++){
        for (int j = 0; j < side; j++) {
            if (i%2==0 && j%2==1) mapArray[i][j] = 196;
            else if (i % 2 == 1 && j % 2 == 0) mapArray[i][j] =179;
            else if (i % 2 == 1 && j % 2 == 1) mapArray[i][j] =255;
            else if (i % 2 == 0 && j % 2 == 0) {
                if(i==0 && j==0) mapArray[i][j]=218;
                else if (i==0 && j==side-1) mapArray[i][j]=191;
                else if (i==side-1 && j==0) mapArray[i][j]=192;
                else if (i==side-1 && j==side-1) mapArray[i][j]=217;
                else if (j==0 && i%2==0) mapArray[i][j]=179;
                else if (i==0 && j%2==0) mapArray[i][j]=196;
                else if (j==side-1 && i%2==0) mapArray[i][j]=179;
                else if (i==side-1 && j%2==0) mapArray[i][j]=196;
                else mapArray[i][j]=197;
            }
        }
    }
}

//int main () {
//    printf("please enter a number between 2 and 20:\n");
//    int n ;
//    scanf("%d",&n);
//    int map[2*n-1][2*n-1];
//    emptymap(n,map);
//    for (int i=0 ; i<2*n-1 ; i++){
//        for (int j=0 ; j<2*n-1 ; j++){
//            printf("%c  ",map[i][j]);
//        }
//        printf("\n");
//    }
//    char ch;
//    printf("please press Esc button for exit:\n");
//    do{
//        ch=getch();
//        printf("wrong button!\n");
//    } while (ch !=27);
//    return 0;
//}