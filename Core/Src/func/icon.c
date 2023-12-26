#include "Inc.h"
void print(_32bit *chessman, int a, int b, int k){
    _32bit *control = (_32bit *)calloc(15, 4);
    for (int i = 0; i < 15; i++)
        control[i] = chessman[i];
    control[a] |= (0xC0000000 >> (b * 2));
    system("clear");
    printf("\x1b[47m\x1b[32m┌─");
    for (int j = 0; j < 15; j++)
        printf("─┬─");
    printf("─┐\n");
    for (int i = 0; i < 15; i++){
        printf("├─");
        for (int j = 0; j < 15; j++)
            switch ((control[i] & (0xC0000000 >> (j * 2))) >> (30 - j * 2)){
            case 0: printf("─┼─");
                break;
            case 1: printf("─⚪");
                break;
            case 2: printf("─⚫");
                break;
            case 3: printf("─\x1b[35m¤\x1b[32m─");
                break;
            }
        printf("─┤\n");
    }
    free(control);
    printf("└─");
    for (int i = 0; i < 15; i++) printf("─┴─");
    printf("─┘\x1b[0m\n");
    if (k == 1) printf("⚪'s turn\n");
    else if (k == -1) printf("⚫'s turn\n");
}
void icon(_32bit *chessman){
    int ch, i = 7, j = 7, k = 1, a = 1;
    while (1){
        A:
        print(chessman, i, j, k);
        if (check(chessman)) break;
        if (k == -1 && a == 1) k *= ai(chessman);
        while (1){
            ch = getch();
            switch (ch){
            case 'w': if (i == 0) i = 14; else i--;
                goto A;
            case 'a': if (j == 0) j = 14; else j--; 
                goto A;
            case 's': if (i == 14) i = 0; else i++;
                goto A;
            case 'd': if (j == 14) j = 0; else j++;
                goto A;
            case ' ':
                if ((chessman[i] & (0xC0000000 >> (j * 2))) == 0){
                    if (k == 1) chessman[i] |= (0x40000000 >> (j * 2));
                    else if (k == -1) chessman[i] |= (0x80000000 >> (j * 2));
                    k *= -1;
                    goto A;
                }
                else break;
            case '\x1b': menu(chessman);
                goto A;
            case '`': save(chessman);
                break;
            case 'i': a *= -1;
                break;
            }
        }

    }
}

