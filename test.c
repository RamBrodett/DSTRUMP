#include <stdio.h>

void create_magic_square(int n, int magic_square[][n]);
void print_magic_square(int n, int magic_square[][n]);

int main()
{
    int n = 3;
    int magic_square[n][n];

    create_magic_square(n, magic_square);
    print_magic_square(n, magic_square);

    return 0;
}

void create_magic_square(int n, int magic_square[][n])
{
    int row = 0, col = n / 2, i, j;

    for (i = 1; i <= n * n; i++)
    {
        magic_square[row][col] = i;
        row--;
        col++;

        if (row < 0 && col > n - 1)
        {
            row += 2;
            col--;
        }
        else if (row < 0)
        {
            row = n - 1;
        }
        else if (col > n - 1)
        {
            col = 0;
        }
        else if (magic_square[row][col] != 0)
        {
            row += 2;
            col--;
        }
    }
}

void print_magic_square(int n, int magic_square[][n])
{
    int i, j;

    printf("Magic Square of size %d:\n\n", n);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d\t", magic_square[i][j]);
        }

        printf("\n");
    }
}
