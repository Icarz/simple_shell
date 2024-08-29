#include "shell.h"
#include "stdio.h"

/**
* main - program entry point
*
* Return: always 0 (success)
**/
int main(void)
{
	int number;

	number = 0;
	while (number < 30)
	{
		printf("%d", number);
		number++;
	}
	putchar('\n');
	return (0);
}
