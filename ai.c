#include "Inc.h"
#define DEPTH 2
#define AREA 2
typedef struct NODE{
    int i, sup, inf, depth;
    _32bit chessman[15];
    struct NODE *parent, *sibling, *child;
} NODE;
int area(int a){
    if (a < 0) return 0;
    else if (a > 14) return 14;
    else return a;
}
int score(int a){
    switch (a){
        case 0x200:
        case 0x80:
        case 0x20:
        case 0x8:
        case 0x2:
            return 1;
        case 0x280:
        case 0xA0:
        case 0x28:
        case 0xA:
        case 0x202:
        case 0x82:
        case 0x22:
        case 0x208:
        case 0x88:
        case 0x220:
            return 10;
        case 0xA8:
        case 0x228:
        case 0x288:
        case 0x2A0:
        case 0xA2:
        case 0x222:
        case 0x282:
        case 0x8A:
        case 0x20A:
        case 0x2A:
            return 100;
        case 0xAA:
        case 0x2A8:
        case 0x2A2:
        case 0x28A:
        case 0x22A:
            return 1000;
        case 0x2AA:
            return 10000;
        case 0x100:
        case 0x40:
        case 0x10:
        case 0x4:
        case 0x1:
            return -1;
        case 0x5:
        case 0x11:
        case 0x41:
        case 0x101:
        case 0x104:
        case 0x44:
        case 0x14:
        case 0x110:
        case 0x50:
        case 0x140:
            return -10;
        case 0x54:
            return -200;
        case 0x114:
        case 0x144:
        case 0x150:
        case 0x51:
        case 0x111:
        case 0x141:
        case 0x45:
        case 0x105:
        case 0x15:
            return -100;
        case 0x154:
        case 0x55:
        case 0x151:
        case 0x145:
        case 0x115:
            return -1000;
        case 0x155:
            return -10000;
        default :
            return 0; 
    }
}
int add(NODE *node){
    int m = 0;
    _32bit a = 0xC0000000, b = 0x3FF00000, s;
    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 15; j++){
            s =   (((node->chessman[i + 0] & (a >> j * 2)) >> (30 - j * 2)) << 8)
                + (((node->chessman[i + 1] & (a >> j * 2)) >> (30 - j * 2)) << 6)
                + (((node->chessman[i + 2] & (a >> j * 2)) >> (30 - j * 2)) << 4)
                + (((node->chessman[i + 3] & (a >> j * 2)) >> (30 - j * 2)) << 2)
                + (((node->chessman[i + 4] & (a >> j * 2)) >> (30 - j * 2)) << 0);
            m += score(s);
        }
    
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 11; j++){
            s = ((node->chessman[i] & (b >> j * 2)) >> (20 - j * 2));
            m += score(s);
        }

    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++){
            s =   (((node->chessman[i + 0] & (a >> j * 2 + 0)) >> (30 - j * 2 - 0)) << 8)
                + (((node->chessman[i + 1] & (a >> j * 2 + 2)) >> (30 - j * 2 - 2)) << 6)
                + (((node->chessman[i + 2] & (a >> j * 2 + 4)) >> (30 - j * 2 - 4)) << 4)
                + (((node->chessman[i + 3] & (a >> j * 2 + 6)) >> (30 - j * 2 - 6)) << 2)
                + (((node->chessman[i + 4] & (a >> j * 2 + 8)) >> (30 - j * 2 - 8)) << 0);
            m += score(s);
        }

    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++){
            s =   (((node->chessman[i + 0] & (a >> j * 2 + 8)) >> (30 - j * 2 - 8)) << 8)
                + (((node->chessman[i + 1] & (a >> j * 2 + 6)) >> (30 - j * 2 - 6)) << 6)
                + (((node->chessman[i + 2] & (a >> j * 2 + 4)) >> (30 - j * 2 - 4)) << 4)
                + (((node->chessman[i + 3] & (a >> j * 2 + 2)) >> (30 - j * 2 - 2)) << 2)
                + (((node->chessman[i + 4] & (a >> j * 2 + 0)) >> (30 - j * 2 - 0)) << 0);
            m += score(s);
        }
    
    return m;
}


void search(NODE *node){
    NODE *sibling = (NODE *)malloc(sizeof(NODE)), *head = sibling;
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            if (((node->chessman[i] & (0xC0000000 >> j * 2)) >> (30 - j * 2)) != 0)
                for (int ii = area(i - AREA); ii <= area(i + AREA); ii++)
                    for (int jj = area(j - AREA); jj <= area(j + AREA); jj++)
                        if (((node->chessman[ii] & (0xC0000000 >> (jj * 2))) >> (30 - jj * 2)) == 0){
                            sibling->sibling = (NODE *)malloc(sizeof(NODE));
                            sibling = sibling->sibling;
                            sibling->depth = node->depth + 1;
                            sibling->i = ii;
                            sibling->child = NULL;
                            for (int i = 0; i < 15; i++)
                                sibling->chessman[i] = node->chessman[i];
                            if (sibling->depth % 2 == 0)
                                sibling->chessman[ii] |= (0x40000000 >> (jj * 2));
                            else if (sibling->depth % 2 == 1)
                                sibling->chessman[ii] |= (0x80000000 >> (jj * 2));
                        }
    sibling->sibling = NULL;
    node->child = head->sibling;
    free(head);
}
void nodes(NODE *node, int depth){
    if (node != NULL){
        if (node->depth == depth)
            search(node);
        nodes(node->sibling, depth);
        if (node->depth < depth)
            nodes(node->child, depth);
    } 
}
void parent(NODE *node){
    if (node != NULL){
        if (node->child != NULL) node->child->parent = node;
        if (node->sibling != NULL) node->sibling->parent = node->parent;
        parent(node->child);
        parent(node->sibling);
    }
}
void evaluate(NODE *node){
    if (node != NULL){
        if (node->depth == DEPTH)
            node->inf = node->sup = add(node);
        evaluate(node->sibling);
        evaluate(node->child);
    }
}
void find(NODE *node){
    if (node != NULL){
        if (node->depth != DEPTH && node->depth != 0){
            node->inf = node->parent->inf;
            node->sup = node->parent->sup;
        }
        find(node->child);
        if (node->depth != 0){
            if (node->depth % 2 == 0 && node->inf < node->parent->sup)node->parent->sup = node->inf;
            else if (node->depth % 2 == 1 && node->sup > node->parent->inf)node->parent->inf = node->sup;
            if (node->parent->sup > node->parent->inf) find(node->sibling);
        }
    }
}
void free_tree(NODE *node){
    if (node != NULL){
        if (node->child != NULL){
            free_tree(node->child);
            node->child = NULL;
        }
        if (node->sibling != NULL){
            free_tree(node->sibling);
            node->sibling = NULL;
        }
        free(node);
    }
}
int ai(_32bit *chessman){
    NODE *root = (NODE *)malloc(sizeof(NODE));
    root->depth = 0;
    root->parent = root->sibling = root->child = NULL;
    root->inf = 0x80000000;
    root->sup = 0x7fffffff;
    for (int i = 0; i < 15; i++)
        root->chessman[i] = chessman[i];
    for (int i = 0; i < DEPTH; i++)
        nodes(root, i);
    parent(root);
    evaluate(root);
    find(root);
    for (NODE *sibling = root->child; sibling != NULL; sibling = sibling->sibling)
        if (sibling->sup == root->inf){
            chessman[sibling->i] = sibling->chessman[sibling->i];
            break;
        }
    free_tree(root);
    return -1;
}