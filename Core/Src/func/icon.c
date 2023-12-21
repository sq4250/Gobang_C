#include "Inc.h"
void print(_32bit *chessman, int a, int b, int k){
    _32bit *control = (_32bit *)calloc(16, 4);
    for (int i = 0; i < 16; i++)
        control[i] = chessman[i];
    control[a] |= (0xC0000000 >> (b * 2));
    system("clear");
    for (int i = 0; i < 16; i++){
        for (int j = 0; j < 17; j++)
            printf("┼    ");
        printf("\n");
        for (int j = 0; j < 16; j++){
            switch ((control[i] & (0xC0000000 >> (j * 2))) >> (30 - j * 2)){
            case 0: printf("     ");
                break;
            case 1: printf("  ●  ");
                break;
            case 2: printf("  ○  ");
                break;
            case 3: printf("  ¤  ");
                break;
            }
        }
        printf("\n");
    }
    free(control);
    for (int i = 0; i < 17; i++) printf("┼    ");
    printf("\n");
    if (k == 1) printf("●'s turn\n");
    else if (k == -1) printf("○'s turn\n");
}
void icon(_32bit *chessman){
    int ch, i = 7, j = 7, k = 1;
    while (1){
        A:
        print(chessman, i, j, k);
        if(check(chessman)) break;
        while (1){
            ch = getch();
            switch (ch){
            case 'w': if (i == 0) i = 15; else i--;
                goto A;
            case 'a': if (j == 0) j = 15; else j--; 
                goto A;
            case 's': if (i == 15) i = 0; else i++;
                goto A;
            case 'd': if (j == 15) j = 0; else j++;
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
            }
        }

    }
}

