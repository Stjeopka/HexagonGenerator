#include <stdio.h>
#include <stdlib.h>
#define ANZAHL 10
#define BACKGROUND 255 //Backgroundcolor: 0 for Black and 255 for White
#define X_PIXEL 2000 // Ihre Bildbreite
#define Y_PIXEL 2000 // Ihre Bildhöhe
#define MYFILENAME "testimage.ppm" // Ihr Filename
int cor[X_PIXEL][Y_PIXEL];


//goes through the whole array and sets the Backgroundcolor
void setbackground(){
    for(int y=0; y < Y_PIXEL;y++){
        for (int x=0; x < X_PIXEL; x++){
            cor[x][y] = BACKGROUND;
        }
    }
}

void findcenter(int middle[]){
    middle[0]= X_PIXEL/2;
    middle[1]= Y_PIXEL/2;
}

int drawpoint(int A[]){
    cor[A[0]][A[1]]=0;
}

int drawline(int A[], int B[]){
    int Start_X=A[0];
    int Start_Y=A[1];
    int End_X=B[0];
    int End_Y=B[1];
    int lineColor = (BACKGROUND == 255) ? 0 : 255;

    int dx =  abs(End_X - Start_X);
    int sx = Start_X < End_X ? 1 : -1;
    int dy = -abs(End_Y - Start_Y);
    int sy = Start_Y < End_Y ? 1 : -1;
    int err = dx + dy; /* error value e_xy */
    int e2;

    while (1) {
        cor[Start_X][Start_Y]=lineColor;
        if (Start_X == End_X && Start_Y == End_Y) break;
        e2 = 2 * err;
        if (e2 > dy){ /* e_xy+e_x > 0 */
            err += dy;
            Start_X += sx;
        }
        if(e2 < dx){ /* e_xy+e_y < 0 */
            err += dx;
            Start_Y += sy;
        }
    }

}


void draw(int middle[], int count){
    drawpoint(middle);
    int maxsize = (X_PIXEL <= Y_PIXEL) ? X_PIXEL :Y_PIXEL;
    maxsize = maxsize/2* 0.98;
    int dist = maxsize/count;
    dist >= 150 ? 150 : dist;
    dist <= 50 ? 50 : dist;
    //Will set every corner piece
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
    int middle[2];//middle[0] = X Coordinate //middle[1] = Y Coordinate
    setbackground();
    findcenter(middle);
    draw(middle, ANZAHL);
    create_ppm();
    return 0;
}