#include "functions.h"
#include "draw.h"
int cor[X_PIXEL][Y_PIXEL];

int main(){
    int middle[2];
    int amount;

    //User Input
    do{
        printf("Please enter your amount:");
    } while (scanf("%d", &amount) == 0);
    getchar();

    findcenter(middle);
    setbackground();
    draw(middle, amount);
    create_ppm();
    return 0;
}