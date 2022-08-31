#pragma once

int strnlen(char *s, int maxsize);
int putchar(char c);
char getch();
void getn(char *buf, int n);
int puts(const char *buf);
int puts_nonl(const char *buf);
int printf(const char *fmt, ...);
int strlen(char *s);
int streq(char *s1, char *s2);
int strcmp(char *s1, char *s2);

void *memcpy(void *dest, void *src, unsigned int n);
