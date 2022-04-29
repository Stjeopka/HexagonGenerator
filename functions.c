#include "functions.h"

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

//Goes through the whole array and sets the Backgroundcolor
void setbackground(){
    for(int y=0; y < Y_PIXEL;y++){
        for (int x=0; x < X_PIXEL; x++){
            cor[x][y] = BACKGROUND;
        }
    }
}

//Just finds the Center of the given Array
void findcenter(int middle[]){
    middle[0]= abs(X_PIXEL/2);
    middle[1]= abs(Y_PIXEL/2);
}

void drawline(int A[], int B[]){
    int Start_X=A[0];
    int Start_Y=A[1];
    int End_X=B[0];
    int End_Y=B[1];

    int dx =  abs(End_X - Start_X);
    int sx = Start_X < End_X ? 1 : -1;
    int dy = -abs(End_Y - Start_Y);
    int sy = Start_Y < End_Y ? 1 : -1;
    int err = dx + dy; /* error value e_xy */
    int e2;

    while (1) {
        cor[Start_X][Start_Y]=LINECOLOR;
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