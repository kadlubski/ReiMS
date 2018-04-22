#include "ReiMS.h"



void reduzier (struct bruch *b)
{
    long long z1 = 0;
    long long z2 = 0;

    if (b->divident > b->divisor)
    {
        z1 = b->divident;
        z2 = b->divisor;
    }
    else if (b->divident == b->divisor)
    {
        b->divident = 1;
        b->divisor = 1;
        return;
    }
    else
    {
        z2 = b->divident;
        z1 = b->divisor;
    }
    if (z1 == 0 || z2 == 0)
    {
        return;
    }
    int r = 1;

    while (r != 0)
    {
        r = z1 % z2;
        z1 = z2;
        z2 = r;
    }

    b->divident = (b->divident)/z1;
    b->divisor = (b->divisor)/z1;

    return;
}

int strToInt (char *arg)
{
    int out = 0;
    for (int i = 0;arg[i]!= '\0';i++)
    {

        out *= 10;
        out += arg[i] - 48;
    }
    return (out);
}

struct zahl strToZahl (char *arg)
{
    struct zahl out;
    _Bool ima = 0;
    _Bool durch = 0;
    _Bool negativ = 0;
    long long p1 = 0;
    long long p2 = 0;
    out.re.divident = 0;
    out.re.divisor = 1;
    out.re.neg = 0;
    out.im.divident = 0;
    out.im.divisor = 1;
    out.im.neg = 0;

    for (int i = 0; arg[i] != '\0';i++)
    {
        if (arg[i] == '+' || arg[i] == '-')
        {
            if (i == 0 && arg[i] == '-')
            {
                negativ = 1;
            }
            else if (arg[i] == '-')
            {
                out.re.divident = p1;
                if (p2 == 0)
                {
                    p2 = 1;
                }
                else
                {
                    out.re.divisor = p2;
                }
                out.re.neg = negativ;
                p1 = 0;
                p2 = 0;
                durch = 0;
                negativ = 1;
            }
            else
            {
                out.re.divident = p1;
                if (p2 == 0)
                {
                    p2 = 1;
                }
                else
                {
                    out.re.divisor = p2;
                }
                out.re.neg = negativ;
                p1 = 0;
                p2 = 0;
                durch = 0;
                negativ = 0;
            }
        }
        else if (arg[i] >= '0' && arg[i] <= '9')
        {
            if (!durch)
            {
                p1 *= 10;
                p1 += arg[i] - 48;
            }
            else
            {
                p2 *= 10;
                p2 += arg[i] - 48;
            }

        }
        else if (arg[i] == 'i' || arg[i] == 'j')
        {
            ima =  1;
        }
        else if (arg[i] == '/')
        {
            durch = 1;
        }
    }
    if (ima)
    {
        if (p1 == 0)
        {
            p1 = 1;
            out.im.divident = p1;
        }
        else
        {
            out.im.divident = p1;
        }
        if (p2 == 0)
        {
            p2 = 1;
            out.im.divisor = p2;
        }
        else
        {
            out.im.divisor = p2;
        }
        out.im.neg = negativ;
    }
    else
    {
        out.re.divident = p1;
        if (p2 == 0)
        {
            p2 = 1;
        }
        else
        {
            out.re.divisor = p2;
        }
        out.re.neg = negativ;
    }
    return (out);
}

struct bruch invSigne (struct bruch b1)
{
    struct bruch out;
    out = b1;
    if (b1.neg == 0)
    {
        out.neg = 1;
    }
    else
    {
        out.neg = 0;
    }
    return (out);
}

struct bruch addBruch (struct bruch b1, struct bruch b2)
{
    struct bruch out;

    //Berechnung für Divident
    if (b1.neg & !(b2.neg))
    {
        out.divident = ((b2.divident)*(b1.divisor))-((b1.divident)*(b2.divisor));
    }
    else if (!(b1.neg) & b2.neg)
    {
        out.divident = ((b1.divident)*(b2.divisor))-((b2.divident)*(b1.divisor));
    }
    else
    {
        out.divident = ((b1.divident)*(b2.divisor))+((b2.divident)*(b1.divisor));
    }

    //Berechnung für divisor
    out.divisor = (b1.divisor)*(b2.divisor);

    //Signe
    if (b1.neg & b2.neg)
    {
        out.neg = 1;
    }
    else if (out.divident < 0)
    {
        out.divident *= -1;
        out.neg = 1;
    }
    else
    {
        out.neg = 0;
    }

    reduzier(&out);

    return (out);
}

struct bruch subBruch (struct bruch b1, struct bruch b2)
{
    struct bruch out;
    struct bruch invB = invSigne(b2);

    //Berechnung für Divident
    if (b1.neg & !(invB.neg))
    {
        out.divident = ((invB.divident)*(b1.divisor))-((b1.divident)*(invB.divisor));
    }
    else if (!(b1.neg) & invB.neg)
    {
        out.divident = ((b1.divident)*(invB.divisor))-((b2.divident)*(b1.divisor));
    }
    else
    {
        out.divident = ((b1.divident)*(invB.divisor))+((b2.divident)*(b1.divisor));
    }

    //Berechnung für divisor
    out.divisor = (b1.divisor)*(invB.divisor);

    //Signe
    if (b1.neg & invB.neg)
    {
        out.neg = 1;
    }
    else if (out.divident < 0)
    {
        out.divident *= -1;
        out.neg = 1;
    }
    else
    {
        out.neg = 0;
    }

    reduzier(&out);

    return (out);
}

struct bruch multBruch (struct bruch b1, struct bruch b2)
{
    struct bruch out;

    out.divident = (b1.divident) * (b2.divident);
    out.divisor = (b1.divisor) * (b2.divisor);

    if (b1.neg ^ b2.neg)
    {
        out.neg = 1;
    }
    else
    {
        out.neg = 0;
    }

    reduzier(&out);
    return (out);
}

struct bruch divBruch (struct bruch b1, struct bruch b2)
{
    struct bruch out;
    struct bruch invB2;
    invB2.divident = b2.divisor;
    invB2.divisor = b2.divident;
    invB2.neg = b2.neg;
    out = multBruch(b1, invB2);
    return (out);
}

struct zahl addZahl (struct zahl z1, struct zahl z2)
{
    struct zahl out;
    out.re = addBruch(z1.re, z2.re);
    out.im = addBruch(z1.im, z2.im);
    return (out);
}

struct zahl subZahl (struct zahl z1, struct zahl z2)
{
    struct zahl out;
    out.re = subBruch(z1.re, z2.re);
    out.im = subBruch(z1.im, z2.im);
    return (out);
}

struct zahl divZahl (struct zahl z1, struct zahl z2)
{
    struct zahl out;
    struct bruch divi;
    struct bruch a1;
    struct bruch a2;

    struct bruch invZ2Im = invSigne(z2.im);

    a1 = multBruch(z2.re, z2.re);
    a2 = multBruch(z2.im, z2.im);
    divi = addBruch(a1, a2);

    a1 = multBruch(z1.re, z2.re);
    a2 = multBruch(z1.im, invZ2Im);
    a1 = subBruch(a1, a2);
    out.re = divBruch(a1, divi);

    a1 = multBruch(z1.re, invZ2Im);
    a2 = multBruch(z1.im, z2.re);
    a1 = addBruch(a1, a2);
    out.im = divBruch(a1, divi);
    return (out);
}

struct zahl multZahl (struct zahl z1, struct zahl z2)
{
    struct zahl out;
    struct bruch a1;
    struct bruch a2;

    a1 = multBruch(z1.re, z2.re);
    a2 = multBruch(z1.im, z2.im);
    out.re = subBruch(a1, a2);

    a1 = multBruch(z1.re, z2.im);
    a2 = multBruch(z1.im, z2.re);
    out.im = addBruch(a1, a2);

    return (out);
}

struct bruch wurzBruch (struct bruch b1)
{
    struct bruch out;
    struct bruch halb;
    halb.divident = 1;
    halb.divisor = 2;
    int n = 3;
    out.divident = b1.divident + 1;
    out.divisor = b1.divisor * 2;

    for (int i = 0;i<n;i++)
    {
        out = multBruch(halb, addBruch(out, divBruch(b1, out)));
    }

    return (out);
}
