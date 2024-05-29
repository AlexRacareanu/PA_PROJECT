#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int aux_end, aux_start, last_max_diff, nr_elem, *books, start[3], end[3];
bool change;

int sumPag(int start, int end)
{
    int sum = 0;
    for (int i = start; i <= end; i++)
        sum += *(books + i);
    return sum;
}

int minSum()
{
    int s1 = sumPag(start[0], end[0]);
    int s2 = sumPag(start[1], end[1]);
    int s3 = sumPag(start[2], end[2]);
    int min = s1;
    if (min > s2)
        min = s2;
    if (min > s3)
        min = s3;
    return min;
}

int maxSum()
{
    int s1 = sumPag(start[0], end[0]);
    int s2 = sumPag(start[1], end[1]);
    int s3 = sumPag(start[2], end[2]);
    int max = s1;
    if (max < s2)
        max = s2;
    if (max < s3)
        max = s3;
    return max;
}

int maxEmp()
{
    int s1 = sumPag(start[0], end[0]);
    int s2 = sumPag(start[1], end[1]);
    int s3 = sumPag(start[2], end[2]);
    int max = s1;
    if (max < s2)
        max = s2;
    if (max < s3)
        max = s3;
    if (max == s1)
        return 0;
    else if (max == s2)
        return 1;
    return 2;
}

int minEmp()
{
    int s1 = sumPag(start[0], end[0]);
    int s2 = sumPag(start[1], end[1]);
    int s3 = sumPag(start[2], end[2]);
    int min = s1;
    if (min > s2)
        min = s2;
    if (min > s3)
        min = s3;
    if (min == s1)
        return 0;
    else if (min == s2)
        return 1;
    return 2;
}

int maxDif()
{
    return maxSum(books, start, end) - minSum(books, start, end);
}

void init()
{
    time_t t;
    srand((unsigned)time(&t));
    for (int i = 0; i < nr_elem; i++)
    {
        *(books + i) = (int)rand() % 2000;
    }
    start[0] = 0;
    start[1] = nr_elem / 3;
    start[2] = (nr_elem / 3) * 2;
    end[0] = start[1] - 1;
    end[1] = start[2] - 1;
    end[2] = nr_elem - 1;
}

void solve()
{
    nr_elem_init();
    init();
    do
    {
        change = 0;
        switch (minEmp())
        {
        case 0:
            left_solve(0);
            break;
        case 1:
            // cauta stanga
            left_solve(1);
            // cauta dreapta
            right_solve(1);
            break;
        case 2:
            // cauta dreapta
            right_solve(2);
            break;
        default:
            break;
        }
        switch (maxEmp())
        {
        case 0:
            // la dreapta
            right_solve(1);
            break;
        case 1:
            // la stanga
            left_solve(0);
            // la dreapta
            right_solve(2);
            break;
        case 2:
            // la stanga
            left_solve(1);
            break;
        default:
            break;
        }
    } while (change);
    result();
}

void result()
{
    printf("random generated books: \n");
    for (int i = 0; i <= end[2]; i++)
    {
        printf("%d ", *(books + i));
    }
    printf("\nsolved:\n");

    for (int i = 0; i <= 2; i++)
    {
        for (int j = start[i]; j <= end[i]; j++)
            printf("%d ", *(books + j));
        printf("(sum:%d)   ", sumPag(start[i], end[i]));
    }
}

void nr_elem_init()
{
    nr_elem = ((int)rand() % 20) + 5;
    books = (int *)malloc(nr_elem * sizeof(int));
}

void left_solve(int emp)
{
    last_max_diff = maxDif();
    aux_end = end[emp];
    aux_start = start[emp + 1];
    end[emp]++;
    start[emp + 1]++;
    if (last_max_diff > maxDif())
    {
        change = 1;
    }
    else
    {
        end[emp] = aux_end;
        start[emp + 1] = aux_start;
    }
}

void right_solve(int emp)
{
    last_max_diff = maxDif();
    aux_end = end[emp - 1];
    aux_start = start[emp];
    end[emp - 1]--;
    start[emp]--;
    if (last_max_diff > maxDif())
    {
        change = 1;
    }
    else
    {
        end[emp - 1] = aux_end;
        start[emp] = aux_start;
    }
}
