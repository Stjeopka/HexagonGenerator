#include "functions.h"

void drawpoint(int A[]){
    cor[A[0]][A[1]]=0;
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