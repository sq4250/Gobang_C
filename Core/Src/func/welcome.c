#include "Inc.h"

void welcome(_32bit *chessman)
{
    printf("\033[?25l");
    int i = 0, ch;
    while (1)
    {
        B:
        system("clear");
        switch (i){
        case 0:
            printf("|   Gobang by BUGKNIFEDOGE  |\n");
            printf("|                           |\n");
            printf("|          \x1b[33mNew Game\x1b[0m         |\n");
            printf("|          Load Game        |\n");
            printf("|            Exit           |\n");
            printf("|                           |\n");
            break;
        case 1:
            printf("|   Gobang by BUGKNIFEDOGE  |\n");
            printf("|                           |\n");
            printf("|          New Game         |\n");
            printf("|          \x1b[33mLoad Game\x1b[0m        |\n");
            printf("|            Exit           |\n");
            printf("|                           |\n");
            break;
        case 2:
            printf("|   Gobang by BUGKNIFEDOGE  |\n");
            printf("|                           |\n");
            printf("|          New Game         |\n");
            printf("|          Load Game        |\n");
            printf("|            \x1b[33mExit\x1b[0m           |\n");
            printf("|                           |\n");
            break;
        }
        ch = getch();
        switch (ch){
        case 'w': if (i == 0) i = 2; else i--;break;
        case 's': if (i == 2) i = 0; else i++;break;
        case ' ': goto A;               
        }        
    }
    A:
    switch (i){
    case 0:     
        break;
    case 1:
        FILE *fp = NULL;
    if (fopen(".data.txt","r") != NULL){
        fp = fopen(".data.txt","r");
        for (int j = 0; j < 16; j++)
            fscanf(fp, "%x\n", chessman + j);
        fclose(fp);
        break;
    }
    else {
        printf("file don't exist!\n");
        getch();
        goto B;
    }
    case 2:
        exit(0);
    }
}
