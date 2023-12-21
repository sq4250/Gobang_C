#include "Inc.h"
void save(_32bit *chessman){
    FILE *fp = NULL;
    fp = fopen(".data.txt", "w");
    for (int i = 0; i < 16; i++)
        fprintf(fp, "%x\n", chessman[i]);
    fclose(fp);
}
