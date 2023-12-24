#include "Inc.h"
#define DEPTH 3
#define AREA 3
typedef struct NODE{
    int i, j, sup, inf, depth;
    _32bit chessman[15];
    struct NODE *sibling;
    struct NODE *child;
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
    NODE *sibling = (NODE *)malloc(sizeof(NODE)), *head = sibling;
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            if (((node->chessman[i] & (0xC0000000 >> (j * 2))) >> (30 - j * 2)) != 0)
                for (int ii = area(i - AREA); ii <= area(i + AREA); i++)
                    for (int jj = area(j - AREA); jj <= area(j + AREA); j++)
                        if (((node->chessman[ii] & (0xC0000000 >> (jj * 2))) >> (30 - jj * 2)) == 0){
                            sibling->sibling = (NODE *)malloc(sizeof(NODE));
                            sibling->depth = node->depth + 1;
                            sibling->i = ii;
                            sibling->j = jj;
                            sibling->child = NULL;
                            if (sibling->depth % 2 == 0)
                                sibling->chessman[ii] |= (0x40000000 >> (jj * 2));
                            else if (sibling->depth % 2 == 1)
                                sibling->chessman[ii] |= (0x80000000 >> (jj * 2));
                            sibling = sibling->sibling;
                        }
    sibling->sibling = NULL;
    node->child = head->sibling;
    free(head);
}
void NLR(NODE *node, int i){
    if (node == NULL) return;
    else if (node->depth == i)
        search(node);
    NLR(node->sibling, i);
    NLR(node->child, i);
}
int ai(_32bit *chessman){
    NODE *root;
    root = (NODE *)malloc(sizeof(NODE));
    root->depth = 0;
    for (int i = 0; i < 15; i++)
        root->chessman[i] = chessman[i];
    for (int i =0; i < DEPTH; i++)
        NLR(root, i);
    return -1;
}