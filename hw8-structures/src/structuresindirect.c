/* Example: StructuresIndirect in CodeBlocks
structures as function arguments and return values
indirect instances using pointers */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct cplx
{
    double real; /* real part */
    double imag; /* imaginary part */
};

struct cplx addindirect(struct cplx *pa, struct cplx *pb); /* function prototype */

int structuresindirect(void)
{
    struct cplx z;
    time_t rawtime = time(NULL);

    struct cplx *px = malloc(sizeof(struct cplx));
    struct cplx *py = malloc(sizeof(struct cplx));

    px->real = 2.5;
    px->imag = 5.0;
    py->real = 3.2;
    py->imag = -1.7;

    z = addindirect(px, py);
    printf("Indirect Instance z = %4.2f + %4.2f j\n", z.real, z.imag);
    printf("Today is %s", ctime(&rawtime));

    return 0;
}

struct cplx addindirect(struct cplx *pa, struct cplx *pb)
{
    struct cplx c = *pa; /* can initialise an auto struct variable */

    c.real += pb->real;
    c.imag += pb->imag;
    return c; /* can return a struct value */
}
