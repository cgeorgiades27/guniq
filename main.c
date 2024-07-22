#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
    The uniq utility reads the specified input_file comparing adjacent lines, and
    writes a copy of each unique input line to the output_file.  If input_file is a
    single dash (‘-’) or absent, the standard input is read.  If output_file is
    absent, standard output is used for output.  The second and succeeding copies
    of identical adjacent input lines are not written.  Repeated lines in the input
    will not be detected if they are not adjacent, so it may be necessary to sort
    the files first.
 */

#define MAX_BUFFER_SIZE 256

int main(int argc, char *argv[])
{
    int c, count;
    FILE *input_file = NULL;

    while ((c = getopt(argc, argv, "-c")) != -1)
    {
        switch (c)
        {
        case '-':
            input_file = stdin;
            break;
        case 'c':
            count = 1;
            break;
        case '?':
            printf("illegal option: %c\n", optopt);
        default:
            break;
        }
    }

    if (optind < argc)
    {
        if (input_file != NULL)
        {
            printf("error: cannot read from both stdin and file\n");
            return 1;
        }
        input_file = fopen(argv[optind], "r");
        if (input_file == NULL)
        {
            perror("unable to open file");
            exit(-1);
        }
    }
    else
        input_file = stdin;

    char buffer_prev[MAX_BUFFER_SIZE];
    char buffer_curr[MAX_BUFFER_SIZE];
    int dupe_count = 1;

    fgets(buffer_prev, MAX_BUFFER_SIZE, input_file);
    while (fgets(buffer_curr, MAX_BUFFER_SIZE, input_file) != NULL)
    {
        if (strcmp(buffer_prev, buffer_curr) != 0)
        {
            count ? printf("%d %s", dupe_count, buffer_prev) : printf("%s", buffer_prev);
            dupe_count = 1;
        }
        else
            dupe_count++;

        strcpy(buffer_prev, buffer_curr);
    }

    if (dupe_count > 1)
        count ? printf("%d %s", dupe_count, buffer_prev) : printf("%s", buffer_prev);

    if (input_file != NULL)
        fclose(input_file);
}