/* Example: StructuresDirect in CodeBlocks
 structures as function arguments and return values
 Direct instances using names */

#include <stdio.h>
#include <time.h>

struct cplx
{
    double real; /* real part */
    double imag; /* imaginary part */
};

struct cplx add(struct cplx a, struct cplx b); /* function prototype */

int structuresdirect(void)
{
    struct cplx x, y, z;
    time_t rawtime = time(NULL);

    x.real = 2.5;
    x.imag = 5.0;
    y.real = 3.2;
    y.imag = -1.7;

    z = add(x, y);
    printf("Direct Instance z = %4.2f + %4.2f j\n", z.real, z.imag);
    printf("Today is %s", ctime(&rawtime));
    return 0;
}

struct cplx add(struct cplx a, struct cplx b)
{
    struct cplx c = a; /* can initialise an auto struct variable */

    c.real += b.real;
    c.imag += b.imag;
    return c; /* can return a struct value */
}
