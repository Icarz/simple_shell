#include "simple_shell.h"

/**
 * convert_string_to_int - Converts a string to an integer
 * @str: The string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *         -1 on error
 */
int convert_string_to_int(char *str)
{
int index = 0;
unsigned long int result = 0;
if (*str == '+')
str++;  /* Skip '+' sign */
for (index = 0;  str[index] != '\0'; index++)
{
if (str[index] >= '0' && str[index] <= '9')
{
result *= 10;
result += (str[index] - '0');
if (result > INT_MAX)
return (-1);
}
else
return (-1);
}
return (result);
}

/**
 * display_error - Prints an error message
 * @info: The parameter & return info struct
 * @error_msg: String containing the specified error type
 *
 * Return: Nothing
 */
void display_error(info_t *info, char *error_msg)
{
print_error_message(info->fname);
print_error_message(": ");
print_integer(info->line_count, STDERR_FILENO);
print_error_message(": ");
print_error_message(info->argv[0]);
print_error_message(": ");
print_error_message(error_msg);
}

/**
 * print_integer - Prints a decimal (integer) number (base 10)
 * @number: The number to print
 * @fd: The file descriptor to write to
 *
 * Return: Number of characters printed
 */
int print_integer(int number, int fd)
{
int (*print_char)(char) = write_char_to_stderr;
int index, count = 0;
unsigned int absolute_value, current;
if (fd == STDERR_FILENO)
print_char = write_char_to_stderr;
if (number < 0)
{
absolute_value = -number;
print_char('-');
count++;
}
else
absolute_value = number;
current = absolute_value;
for (index = 1000000000; index > 1; index /= 10)
{
if (absolute_value / index)
{
print_char('0' + current / index);
count++;
}
current %= index;
}
print_char('0' + current);
count++;
return (count);
}

/**
 * number_to_string - Converts a number to a string with specified base
 * @number: The number to convert
 * @base: The base to use for conversion
 * @flags: Conversion flags
 *
 * Return: The converted string
 */
char *number_to_string(long int number, int base, int flags)
{
static char *digits;
static char buffer[50];
char sign = 0;
char *ptr;
unsigned long num = number;
if (!(flags & CONVERT_UNSIGNED) && number < 0)
{
num = -number;
sign = '-';
}
digits = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
ptr = &buffer[49];
*ptr = '\0';
do {
*--ptr = digits[num % base];
num /= base;
} while
(num != 0);
if (sign)
{
*--ptr = sign;
return (ptr);
}

/**
 * strip_comments - Replaces the first instance of '#' with '\0'
 * @buffer: Address of the string to modify
 *
 * Return: Always 0
 */
void strip_comments(char *buffer)
{
int index;
for (index = 0; buffer[index] != '\0'; index++)
if (buffer[index] == '#' && (!index || buffer[index - 1] == ' '))
{
buffer[index] = '\0';
break;
}
}
