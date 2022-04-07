#include <stdio.h>
#include <stdlib.h>
#define ANZAHL 3
#define BACKGROUND 255 //Backgroundcolor: 0 for Black and 255 for White
#define MYFILENAME "testimage.ppm" // Ihr Filename
#define X_PIXEL 2000 // Ihre Bildbreite
#define Y_PIXEL 2000 // Ihre Bildhöhe
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
    //int mirror_H=1;
    //int mirror_45=0;
    /*
    //Swap the Start and the End
    if(End_X < Start_X){
        int tmp_X=Start_X;
        int tmp_Y=Start_Y;
        int Start_X = End_X;
        int Start_Y = End_Y;
        int End_X = tmp_X;
        int End_Y = tmp_Y;
    }

    //Check if the line goes down. If true mirror the Y coordinate.
    if(End_Y > Start_Y){
        mirror_H=-1;
        Start_Y = Start_Y*mirror_H;
        End_Y = End_Y*mirror_H;
    }

    //Check if the line goes over a 45 degree angle
    if((End_X - Start_X) < (Start_Y - End_Y)){
        int mirror_45 =1;

        //Swap Start X and Y
        int tmp_Start = Start_X;
        Start_X = Start_Y;
        Start_Y = Start_X;

        //Swap End X and Y
        int tmp_End = End_X;
        End_X = End_Y;
        End_Y = End_X;
    }*/

    int dx =  abs(End_X - Start_X), sx = Start_X < End_X ? 1 : -1;
    int dy = -abs(End_Y - Start_Y), sy = Start_Y < End_Y ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while (1) {
        cor[Start_X][Start_Y]=0;
        if (Start_X == End_X && Start_Y == End_Y) break;
        e2 = 2 * err;
        if (e2 > dy) { err += dy; Start_X += sx; } /* e_xy+e_x > 0 */
        if (e2 < dx) { err += dx; Start_Y += sy; } /* e_xy+e_y < 0 */
    }

}


void draw(int middle[], int n, int l){
    drawpoint(middle);
    //Will set every corner piece
    for (int i=1; i<=n; i++){
        int UpperPoint[] = {middle[0], middle[1]- (i*l)};
        int UpperRightPoint[] = {middle[0]+ (i*l), middle[1]- (i*(l/2))};
        int UpperLeftPoint[] = {middle[0] - (i*l), middle[1]- (i*(l/2))};
        int LowerPoint[] = {middle[0], middle[1]+ (i*l)};
        int LowerRightPoint[] = {middle[0] + (i*l), middle[1]+ (i*(l/2))};
        int LowerLeftPoint[] = {middle[0] - (i*l), middle[1]+ (i*(l/2))};

        drawline(UpperPoint,UpperRightPoint);
        drawline(UpperRightPoint,LowerRightPoint);
        drawline(LowerRightPoint,LowerPoint);
        drawline(LowerPoint,LowerLeftPoint);
        drawline(LowerLeftPoint,UpperLeftPoint);
        drawline(UpperLeftPoint,UpperPoint);
    }
    int MaxUpperRightPoint[] = {middle[0]+ (n*l), middle[1]- (n*(l/2))};
    int MaxUpperLeftPoint[] = {middle[0] - (n*l), middle[1]- (n*(l/2))};
    int MaxLowerPoint[] = {middle[0], middle[1]+ (n*l)};

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
    int n = 7;//n how many hexagons
    int l = 129;//l distance between the corner and the middle
    setbackground();
    findcenter(middle);
    draw(middle, n, l);
    create_ppm();
    return 0;
}