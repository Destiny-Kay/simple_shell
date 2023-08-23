#include "main.h"


/**
* integer_to_string- converts an integer value toa string
* @number: the number to be converted
* Return: string equivalent of the number
*/
char *integer_tostring(int number)
{
char *string;
int len;
unsigned int n;


len = find_length(number);
string = malloc(sizeof(char) * (len + 1));
if (!string)
return (NULL);
string[len] = '\0';
if (number < 0)
{
n = number * -1;
string[0] = '-';
}
else
n = number;
len--;
do
{
string[len] = (n % 10) + '0';
n = n / 10;
len--;
}
while (n > 0);
return(string);


}
/**
* find_length- finds the length of an integer
* @n: the integer
* Return: length of int
*/
int find_length(int n)
{
int len;
unsigned int num;


len = 1;
if (n < 0)
{
len++;
num = n * -1;
}
else
num = n;
while (num > 9)
{
len++;
num /= 10;
}
return (len);
}




