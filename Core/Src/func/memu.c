#include "Inc.h"

void memu(_32bit *chessman)
{
    printf("\033[?25l");
    int i = 0, ch;
    while (1)
    {
        system("clear");
        switch (i){
        case 0:
            printf("|   Gobang by BUGKNIFEDOGE  |\n");
            printf("|                           |\n");
            printf("|          \x1b[33mNew Game\x1b[0m         |\n");
            printf("|          Continue         |\n");
            printf("|          Load Game        |\n");
            printf("|          Save Game        |\n");
            printf("|            Exit           |\n");
            printf("|                           |\n");
            break;
        case 1:
            printf("|   Gobang by BUGKNIFEDOGE  |\n");
            printf("|                           |\n");
            printf("|          New Game         |\n");
            printf("|          \x1b[33mContinue\x1b[0m         |\n");
            printf("|          Load Game        |\n");
            printf("|          Save Game        |\n");
            printf("|            Exit           |\n");
            printf("|                           |\n");
            break;
        case 2:
            printf("|   Gobang by BUGKNIFEDOGE  |\n");
            printf("|                           |\n");
            printf("|          New Game         |\n");
            printf("|          Continue         |\n");
            printf("|          \x1b[33mLoad Game\x1b[0m        |\n");
            printf("|          Save Game        |\n");
            printf("|            Exit           |\n");
            printf("|                           |\n");
            break;
        case 3:
            printf("|   Gobang by BUGKNIFEDOGE  |\n");
            printf("|                           |\n");
            printf("|          New Game         |\n");
            printf("|          Continue         |\n");
            printf("|          Load Game        |\n");
            printf("|          \x1b[33mSave Game\x1b[0m        |\n");
            printf("|            Exit           |\n");
            printf("|                           |\n");
            break;
        case 4:
            printf("|   Gobang by BUGKNIFEDOGE  |\n");
            printf("|                           |\n");
            printf("|          New Game         |\n");
            printf("|          Continue         |\n");
            printf("|          Load Game        |\n");
            printf("|          Save Game        |\n");
            printf("|            \x1b[33mExit\x1b[0m           |\n");
            printf("|                           |\n");
            break;
        }
        B:
        ch = getch();
        switch (ch){
        case 'w': if (i == 0) i = 4; else i--;break;
        case 's': if (i == 4) i = 0; else i++;break;
        case ' ': goto A;               
        }        
    }
    A:
    switch (i){
    case 0:
        for (int j = 0; j < 16; j++)
                chessman[j] = 0;
        break;
    case 1: break;
    case 2:
        FILE *fp = NULL;
    if (fopen(".data.txt", "r") != NULL){
        fp = fopen(".data.txt", "r");
        for (int j = 0; j < 16; j++)
            fscanf(fp, "%x\n", chessman + j);
        fclose(fp);
        break;
    }
    else {
        printf("file don't exist!\n");
        goto B;
    }
    case 3: save(chessman);
        break;
    case 4: free(chessman);
        exit(0);
    }
}
