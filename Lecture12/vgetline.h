#ifndef VGETLINE_H
#define VGETLINE_H

#include <stdio.h>

#define GETLINE_CAPACITY_DEFAULT    120
#define GETLINE_CAPACITY_INCREASE   2

int vgetline(char **buffer, int *n, FILE *f);

#endif // VGETLINE_H