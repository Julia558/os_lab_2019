#include "swap.h"

void Swap(char *left, char *right)
{
    char dop;
    dop = *left;
    *left = *right;
    *right = dop;
}
