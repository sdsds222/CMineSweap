#ifndef _UTILS_H
#define _UTILS_H
int getRand(int min, int max);
int getMineNum(int *map, int w, int h);
void getLocation(int *block, int i, int j);
void fillBlank(int *map, int w, int h, int x, int y);
void clean0(int *showMap, int *map, int w, int h, int x, int y);
int clean(int *showMap, int *map, int w, int h, int x, int y, int mode);
void print(int *showMap, int *map, int mw, int mh);
#endif