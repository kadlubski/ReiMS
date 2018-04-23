#include <stdio.h>
#include "ReiMS.h"



int main(int argc, char *argv[])
{
    struct zahl bla;
    struct zahl bli;

    if (argc >= 3)
    {
        bla = strToZahl(argv[1]);
        bli = strToZahl(argv[2]);
    }
    else
    {
        printf("Zu wenig Argumente\n");
        return (0);
    }

    bla = multZahl(bla, bli);

    if (bla.re.divident != 0)
    {
        if (bla.re.neg)
        {
            printf("-");
        }
        if (bla.re.divisor == 1)
        {
            printf("%lld ", bla.re.divident);
        }
        else
        {
            printf("%lld/%lld ", bla.re.divident, bla.re.divisor);
        }
    }
    if (bla.im.divident != 0)
    {
        if (bla.re.neg)
        {
            printf("- ");
        }
        else
        {
            printf("+ ");
        }
        if (bla.im.divisor == 1)
        {
            printf("%lld ", bla.im.divident);
        }
        else
        {
            printf("%lld/%lld i", bla.im.divident, bla.im.divisor);
        }
    }
    printf("\n");

    return 0;
}




