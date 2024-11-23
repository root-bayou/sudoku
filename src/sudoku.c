#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include <unistd.h>
#include <getopt.h>
#include <err.h>
#include <string.h>

const int SIZE_OF_GRIDS[8] = {1, 4, 9, 16, 25, 36, 49, 64};
enum bool
{
    false,
    true
};
enum mode
{
    gen,
    sol,
    notSet
};

static enum mode whichMode = notSet;
static enum bool verbose = false;
static enum bool uniqueMode = false;

int main(int argc, char *argv[])
{
    FILE *defaultStream = stdout;
    if (argc == 1)
    {
        printf("error : no input grid given\n");
        printHelp(stdout, 1);
    }
    char *fileName = NULL;
    char *sizeOfGrid = NULL;
    const struct option long_opts[] = {
        {"help", 0, NULL, 'h'},
        {"output", 1, NULL, 'o'},
        {"verbose", 0, NULL, 'v'},
        {"version", 0, NULL, 'V'},
        {"unique", 0, NULL, 'u'},
        {"generate", 1, NULL, 'g'},
        {"all", 0, NULL, 'a'},
        {NULL, 0, NULL, 0}};
    int optc;
    while ((optc = getopt_long(argc, argv, "o:g:auvVh", long_opts, NULL)) != -1)
    {
        switch (optc)
        {
        case 'V':
            printf("%d.%d.%d \n", VERSION, SUBVERSION, REVISION);
            printf("Solve or generate Sudoku grids of various sizes (1.4.9.16.25.36.49.64)\n");
            exit(EXIT_SUCCESS);
            break;
        case 'h':
            printHelp(stdout, 0);
            break;
        case 'v':
            verbose = true;
            break;
        case 'o':
            if (optarg == NULL)
            {
                printHelp(stderr, 1);
            }
            else
            {
                fileName = optarg;
            }
            break;
        case 'g':
            if (optarg == NULL)
            {
                printHelp(stderr, 1);
            }
            else
            {
                sizeOfGrid = optarg;
                whichMode = gen;
            }

            break;
        case 'a':
            whichMode = sol;
            break;
        case 'u':
            uniqueMode = true;
            break;

        default:
            printHelp(stderr, 1);
            break;
        }
    }

    if (whichMode == sol && uniqueMode == true)
    {
        warnx("warning : option unique conflict with solver mode, disabling it \n");
        uniqueMode = false;
    }
    if (whichMode == sol && fopen(fileName, "r+") == NULL)
    {
        errx(1, "error : Unable to open the file or unspecified files use ( -o, --output FILE ) to specify a file");
    }

    if (sizeOfGrid != NULL && checkIfValide(sizeOfGrid))
    {
        printf("The size is valid \n");
    }
    else if (sizeOfGrid != NULL && !checkIfValide(sizeOfGrid))
    {
        errx(1, "error : the size is invalid");
    }
    if (whichMode == notSet && fileName != NULL)
    {
        errx(1, "error : You must specify an argument ( -a , --all ) for solver mode ( -g , --generete ) for generate mode.");
    }

    return (EXIT_SUCCESS);
}

void printHelp(FILE *stream, int exitCode)
{
    if (!exitCode)
    {
        fprintf(stream, "------------------------\n*\t SUDOKU \t*\n------------------------\n"
                        "Solve or generate Sudoku grids of various sizes (1.4.9.16.25.36.49.64)\n");
    }

    fprintf(stream, "\nUsage : sudoku [-a|-o FILE|-v|-V|-h]\n \tsudoku -g[SIZE] [-u|-o FILE|-v|-V|-h]\n");
    if (!exitCode)
    {

        fprintf(stream, "\n-a,--all \t \t search for all possible solutions\n"
                        "-g[N],--generate[=N]\t generate a grid of size N x N (default : 9)\n"
                        "-o FILE, --output FILE\t write solution to FILE\n"
                        "-u,--unique \t \t generate a grid with unique solution\n"
                        "-v,-verbose \t \t verbose output\n"
                        "-V,-version \t \t display version and exit\n"
                        "-h,--help    \t \t display help\n");
    }

    exit(exitCode);
}
enum bool checkIfValide(char *sizeGrid)
{
    int i;
    enum bool k;
    if (strlen(sizeGrid) <= 2)
    {

        if (strlen(sizeGrid) == 2)
        {
            i = (((int)sizeGrid[0] - 48) * 10) + ((int)sizeGrid[1] - 48);
        }
        else
        {
            i = (int)sizeGrid[0] - 48;
        }

        if (i > 0 && i <= 64)
        {

            for (size_t j = 0; j < 8; j++)
            {
                if (i == SIZE_OF_GRIDS[j])
                {

                    k = true;
                    break;
                }
                else
                {
                    k = false;
                }
            }
        }
        else
        {
            k = false;
        }
    }
    else
    {
        k = false;
    }
    return k;
}
