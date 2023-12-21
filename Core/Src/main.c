#include "Inc.h"



int main(){
    do{
    _32bit *chessman = (_32bit *)calloc(16, 4);
    welcome(chessman);
    icon(chessman);
    free(chessman);
    printf("\n>>> press any key...");
    getch();
    } while (1);
    return 0;
}
