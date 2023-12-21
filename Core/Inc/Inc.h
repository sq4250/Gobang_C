#include <stdio.h>
#include <stdlib.h>
typedef unsigned short _16bit;
typedef unsigned int _32bit;
int getch(void);
int kbhit(void);
void memu(_32bit *chessman);
int check(_32bit *chessman);
void icon(_32bit *chessman);
void save(_32bit *chessman);
