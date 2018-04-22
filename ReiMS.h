#ifndef DEF_REIMS
#define DEF_REIMS

#include <stdio.h>

struct bruch
{
    long long divident;
    long long divisor;
    _Bool neg;
};

struct zahl
{
    struct bruch re;
    struct bruch im;
};

struct matrix
{
    int x;
    int y;
    struct zahl **mat;
};

void reduzier (struct bruch *b);
int strToInt (char *arg);
struct zahl strToZahl (char *arg);
struct bruch invSigne (struct bruch b1);
struct bruch addBruch (struct bruch b1, struct bruch b2);
struct bruch subBruch (struct bruch b1, struct bruch b2);
struct bruch multBruch (struct bruch b1, struct bruch b2);
struct bruch divBruch (struct bruch b1, struct bruch b2);
struct bruch wurzBruch (struct bruch b1);
struct zahl addZahl (struct zahl z1, struct zahl z2);
struct zahl subZahl (struct zahl z1, struct zahl z2);
struct zahl divZahl (struct zahl z1, struct zahl z2);
struct zahl multZahl (struct zahl z1, struct zahl z2);

#endif
