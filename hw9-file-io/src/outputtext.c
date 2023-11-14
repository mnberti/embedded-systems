#include <stdio.h>
#include <time.h>
int OutputText()
{
    time_t rawtime = time(NULL);
    FILE *fp;
    fp = fopen("../output/test.txt", "w+");
    fprintf(fp, "This is testing for fprintf...\n");
    fputs("This is testing for fputs...\n", fp);

    int i;
    for (i = 3; i < 11; i++)
    {
        fprintf(fp, "This is string number %d\n", i);
    }
    fprintf(fp, "Run on this date %s", ctime(&rawtime));
    fclose(fp);
    return 0;
}