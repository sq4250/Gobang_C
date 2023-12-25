#include "Inc.h"

int main(){
    _32bit *chessman = (_32bit *)calloc(16, 4);
    do{
        menu(chessman);
        icon(chessman);
        printf("\n>>> press any key...");
        getch();
    } while (1);
    return 0;
}
