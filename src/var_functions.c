/*
#include <stdio.h>
#include <stdlib.h>


enum bool
{
    false,
    true
};
enum mode
{
    gen,
    sol
};

void printHelp(FILE *stream, int exitCode)
{
    if (!exitCode)
    {
        fprintf(stream, "------------------------\n*\t SUDOKU \t*\n------------------------\n");
    }

    fprintf(stream, "\nUsage : sudoku [-a|-o FILE|-v|-V|-h]\n \tsudoku -g[SIZE] [-u|-o FILE|-v|-V|-h]\n"
                    "\nSolve or generate Sudoku grids of various sizes (1.4.9.16.25.36.49.64)\n");

    fprintf(stream, "\n-a,--all \t \t search for all possible solutions\n"
                    "-g[N],--generate[=N]\t generate a grid of size N x N (default : 9)\n"
                    "-o FILE, --output FILE\t write solution to FILE\n"
                    "-u,--unique \t \t generate a grid with unique solution\n"
                    "-v,-verbose \t \t verbose output\n"
                    "-V,-version \t \t display version and exit\n"
                    "-h,--help    \t \t display help\n");

    exit(exitCode);
}
*/