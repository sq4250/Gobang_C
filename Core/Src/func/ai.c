#include "Inc.h"
#define DEPTH 3
#define AREA 3
typedef struct NODE{
    int i, j, sup, inf, depth;
    _32bit chessman[15];
    struct NODE *sibling;
} NODE;
int area(int a){
    if (a < 0) return 0;
    else if (a > 14) return 14;
    else return a;
}
void evaluate(NODE *node);
void cut();
void update();
void search(NODE *node){

}
int ai(_32bit *chessman){
    NODE *root;
    root = (NODE *)malloc(sizeof(NODE));
    root->depth = 0;
    for (int i = 0; i < 15; i++)
        root->chessman[i] = chessman[i];
    return -1;
}