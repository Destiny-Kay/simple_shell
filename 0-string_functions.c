#include "main.h"
#include <stdio.h>
/**
* _strcmp- compares two strings
* @s1: string one
* @s2: string two
* Return: difference between the strings
*/
int _strcmp(char *s1, char *s2)
{
while (*s1 && *s2 && (*s1 == *s2))
{
s1++;
s2++;
}
return (*s1 - *s2);
}


/**
* _strlen- finds length of a string
* @str: A string
* Return: the length of a string
*/
size_t _strlen(const char *str)
{
size_t len = 0;


while (*str++)
{
len++;
}
return (len);
}


/**
* _strncmp- compares the first n chars of 2 strings
* @str1: string1
* @str2: string2
* @n: number of integers to be compared
* Return: the n-difference between two strings
*/
int _strncmp(const char *str1, const char *str2, size_t n)
{
size_t i;


for (i = 0; i < n; i++)
{
char c1 = str1[i];
char c2 = str2[i];


if (c1 == '\0' || c1 != c2)
{
return (c1 - c2);
}
}
return (0);
}


/**
* _strcpy- copies a string from src to dest
* @dest: the destination
* @src: source value
* Return: the pointer to destination string
*/
char *_strcpy(char *dest, char *src)
{
int i;


for (i = 0; src[i] != '\0'; i++)
{
dest[i] = src[i];
}
dest[i++] = '\0';
return (dest);
}


/**
* _strdup- duplicates string
* @str: the string to be duplicated
* Return: pointer to duplicated string
*/
char *_strdup(char *str)
{
size_t len;
char *duplicate;


if (str == NULL)
return (NULL);


len = _strlen(str) + 1;
duplicate = (char *)malloc(len);
if (duplicate == NULL)
{
perror("Memory allocation error");
exit(EXIT_FAILURE);
}
return (_strcpy(duplicate, str));
}

