#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void EachLine(unsigned char *data, int nchars, FILE *ftpr);

int DumpHex()
{
    FILE *fptr;
    FILE *dmpptr;
    int nchars; // number of characters input
    char filename[50];
    unsigned char inputvals[16];
    // get the input file name
    printf("HexDump - Enter file name: ");
    scanf("%s", filename);

    // open the input file
    fptr = fopen(filename, "r");
    if (!fptr)
    {
        printf("file not found, cannot continue\n");
        return 0;
    }

    // read an input block of characters from fptr
    dmpptr = fopen("../output/hdp.txt", "w");
    do
    {
        nchars = fread(inputvals, sizeof(char), 16, fptr);
        if (nchars)
            EachLine(inputvals, nchars, dmpptr);
    } while (nchars);

    return 0;
}

void EachLine(unsigned char *data, int nchars, FILE *fptr)
{
    int i;
    char ctmp;
    static int address = 0;
    // print 16 bit address
    fprintf(fptr, "%04X : ", address);
    for (i = 0; i < nchars; i++)
    {
        // print each hex value
        fprintf(fptr, "%02X ", data[i]);
    }

    // print colon separator
    fprintf(fptr, " : ");

    // print characters
    for (i = 0; i < nchars; i++)
    {
        ctmp = data[i];
        // print each text value
        if (isprint(ctmp))
            fputc(ctmp, fptr);
        else
            fputc('.', fptr);
    }

    // print newline
    fprintf(fptr, "\n");

    address += nchars;
}