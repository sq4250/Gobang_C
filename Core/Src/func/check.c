#include "Inc.h"
int checkchess(_32bit *a, int c){
    char (*p)[16][16] = (char (*)[16][16])calloc(4, 16 * 16);
    for (int i = 0; i < 16; i++){
        if (((a[0] & (0xC0000000 >> (i * 2))) >> (30 - i * 2)) == c){
            p[0][0][i] = 1;
            p[2][0][i] = 1;
        }
        if (((a[i] & 0xC0000000) >> 30) == c){
            p[1][i][0] = 1;
            p[2][i][0] = 1;
            p[3][i][0] = 1;
        }
        if (((a[15] & (0xC0000000 >> (i * 2))) >> (30 - i * 2)) == c)
            p[3][15][i] = 1;
    }
    
    for (int i = 1; i < 16; i++)
        for (int j = 0; j < 16; j++){
            if (((a[i] & (0xC0000000 >> (j * 2))) >> (30 - j * 2)) == c)
                p[0][i][j] = p[0][i - 1][j] + 1;
            else p[0][i][j] = 0;
        }
    
    for (int i = 0; i < 16; i++)
        for (int j = 1; j < 16; j++){
            if (((a[i] & (0xC0000000 >> (j * 2))) >> (30 - j * 2)) == c)
                p[1][i][j] = p[1][i][j - 1] + 1;
            else p[1][i][j] = 0;
        }
    
    for (int i = 1; i < 16; i++)
        for (int j = 1; j < 16; j++){
            if (((a[i] & (0xC0000000 >> (j * 2))) >> (30 - j * 2)) == c)
                p[2][i][j] = p[2][i - 1][j - 1] + 1;
            else p[2][i][j] = 0;
        }
    
    for (int i = 14; i >= 0; i--)
        for (int j = 1; j < 16; j++){
            if (((a[i] & (0xC0000000 >> (j * 2))) >> (30 - j * 2)) == c)
                p[3][i][j] = p[3][i + 1][j - 1] + 1;
            else p[3][i][j] = 0;
        }   
    
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 16; j++)
            for (int k = 0; k < 16; k++)
                if (p[i][j][k] == 5){
                    free(p);
                    return c;
                }
    free(p);
    return 0;
}
int check(_32bit *chessman){
    if(checkchess(chessman, 1) == 1){
        printf("\n");
        printf("|          Winner:          |\n");
        printf("|                           |\n");    
        printf("|           White           |\n");
        printf("|                           |\n");
        printf("|                           |\n");
        return 1;
    }
    else if(checkchess(chessman, 2) == 2){
        printf("\n\n");
        printf("|          Winner:          |\n");
        printf("|                           |\n");
        printf("|           Black           |\n");
        printf("|                           |\n");
        printf("|                           |\n");
        return 2;
    }
    return 0;
}
