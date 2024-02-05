#include <time.h>
#include "quridorFunction.c"


int main() {

    srand(time(NULL));
    int i, j, k, n, m, choice;
    struct DataGame *data;

    data = malloc(sizeof (struct DataGame));

    InitializeData (data);

    printf("1. Play game\n2. Quit\n");
    printf("Enter your choice:\n");
    while (1) {
        scanf("%d", &choice);
        if (choice!=1 && choice!=2) {
            perror("\nwrong choice.\n");
        } else break;
    }
    switch (choice) {
        case 1:
            playGame(data);
            break;
        case 2:
            free(data);
            return 0;
    }
    free(data);
    return 0;
}