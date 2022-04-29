#include "draw.h"
#include "functions.h"
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