#include "functions.h"
#define MYFILENAME "testimage.ppm" // Ihr Filename
int const X_PIXEL=2000;
int const Y_PIXEL=2000;
int cor[2000][2000];
int lineColor = 0;
int Background = 255;

/*
 * Every Point in this Algorithmen is represnted as an 1D-Array with 2 Indexes
 * The first index stores the X_Coordinate
 * The second index stores the Y_Coordinate
*/


//Goes through the whole array and sets the Backgroundcolor
void setbackground(){
    for(int y=0; y < Y_PIXEL;y++){
        for (int x=0; x < X_PIXEL; x++){
            cor[x][y] = Background;
        }
    }
}

//Just finds the Center of the given Array
void findcenter(int middle[]){
    middle[0]= abs(X_PIXEL/2);
    middle[1]= abs(Y_PIXEL/2);
}

void draw(int middle[], int count){
    if (count<=0)
        return;
    //Calculating the Distance between the Points with reference to the ArraySize
    int maxsize = (X_PIXEL <= Y_PIXEL) ? X_PIXEL :Y_PIXEL;
    maxsize = abs(maxsize/2* 0.98);
    int dist = abs(maxsize/count);
    dist >= 150 ? 150 : dist;
    dist <= 50 ? 50 : dist;

    //Every Point in the Hexagon will now be determined
    for (int i=1; i<=count; i++){
        int UpperPoint[] = {middle[0], middle[1]- (i*dist)};
        int UpperRightPoint[] = {middle[0]+ (i*dist), middle[1]- (i*(dist/2))};
        int UpperLeftPoint[] = {middle[0] - (i*dist), middle[1]- (i*(dist/2))};
        int LowerPoint[] = {middle[0], middle[1]+ (i*dist)};
        int LowerRightPoint[] = {middle[0] + (i*dist), middle[1]+ (i*(dist/2))};
        int LowerLeftPoint[] = {middle[0] - (i*dist), middle[1]+ (i*(dist/2))};

        drawline(UpperPoint,UpperRightPoint);
        drawline(UpperRightPoint,LowerRightPoint);
        drawline(LowerRightPoint,LowerPoint);
        drawline(LowerPoint,LowerLeftPoint);
        drawline(LowerLeftPoint,UpperLeftPoint);
        drawline(UpperLeftPoint,UpperPoint);
    }
    //Draws now all the lines going from the Middle
    int MaxUpperRightPoint[] = {middle[0]+ (count*dist), middle[1]- (count*(dist/2))};
    int MaxUpperLeftPoint[] = {middle[0] - (count*dist), middle[1]- (count*(dist/2))};
    int MaxLowerPoint[] = {middle[0], middle[1]+ (count*dist)};

    drawline(middle,MaxUpperRightPoint);
    drawline(middle,MaxUpperLeftPoint);
    drawline(middle,MaxLowerPoint);
}


//Creates the file and sets the corresponding values from the array into the ppm file
void create_ppm(){
    FILE *p_file;
    p_file = fopen(MYFILENAME,"w");
    if (p_file){
        fprintf (p_file, "P3\n%d %d\n 255\n", X_PIXEL, Y_PIXEL);
        for(int y=0; y < Y_PIXEL;y++){
            for (int x=0; x < X_PIXEL; x++){
                int current = cor[x][y];
                fprintf (p_file, "%d %d %d ",current, current, current);
            }
            fprintf(p_file, "\n");
        }
    }
}

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