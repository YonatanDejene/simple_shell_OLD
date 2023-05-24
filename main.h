#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int intractv(info_t *info);
int is_delim(char c, char *delim);
int is_alpha(int c);
int at(char *s);

//void prompt(char **ax, char **envi);
#endif
