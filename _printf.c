#include "main.h"

/**
 * _printf - produces output according to a format
 * @format: The specified format
 *
 * Return: The number of characters that were printed
 */
int _printf(const char *format, ...)
{
int i = 0, char_count = 0;
char processing_escape = FALSE;
fmt_info_t fmt_info;
va_list args;

va_start(args, format);
write_buffer(0, -1);
if (!format || (format[0] == '%' && format[1] == '\0'))
return (-1);
for (i = 0; format && *(format + i) != '\0'; i++)
{
if (processing_escape)
{
i += ABS(read_format_info(format + i, args, &fmt_info));
processing_escape = FALSE;
if (is_specifier(fmt_info.spec))
{
char_count += write_format(&args, &fmt_info);
}
else
{
i--;
_putchar('%');
_putchar(*(format + i));
char_count += 2;
}
}
else
{
if (*(format + i) == '%')
processing_escape = TRUE;
else
_putchar(*(format + i)), char_count++;
}
}
write_buffer(0, 1);
va_end(args);
return (char_count);
}
/**
 * write_format - Writes data formatted against some parameters
 * @args_list: The arguments list
 * @fmt_info: The format info parameters that were read
 *
 * Return: The number of characters written
 */
int write_format(va_list *args_list, fmt_info_t *fmt_info)
{
int chars_written = 0;
int i;
spec_printer_t spec_printers[] = {
{'%', convert_fmt_percent},
{'p', convert_fmt_p},
{'c', convert_fmt_c},
{'s', convert_fmt_s},
{'d', convert_fmt_di},
{'i', convert_fmt_di},
/* {'F', convert_fmt_fF}, */
/* {'f', convert_fmt_fF}, */
{'X', convert_fmt_xX},
{'x', convert_fmt_xX},
{'o', convert_fmt_o},
{'u', convert_fmt_u},
/* #begin custom specifiers */
{'b', convert_fmt_b},
{'R', convert_fmt_R},
{'r', convert_fmt_r},
{'S', convert_fmt_S},
/* #end */
};

for (i = 0; i < 23 && spec_printers[i].spec != '\0'; i++)
{
if (fmt_info->spec == spec_printers[i].spec)
{
chars_written = spec_printers[i].print_arg(args_list, fmt_info);
break;
}
}
return (chars_written);
}

/**
 * _putstr - writes the given string to the buffer
 * @str: The string to write
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putstr(char *str)
{
int i, out;

for (i = 0; str && *(str + i) != 0; i++)
out = _putchar(*(str + i));
return (out);
}


/**
 * write_to_buffer - Writes a char to the buffer based on an action code
 * @c: The character to write
 * @action: The action to perform (
 * -1-> reset the static variables
 * 0-> write char to buffer
 * 1-> don't write character to buffer but empty buffer onto stdout)
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_buffer(char c, char action)
{
static int i;
static char buffer[1024];
char out = 1;

if (i < 1024 && action == 0)
{
buffer[i] = c;
i++;
}
if (i >= 1024 || action == 1)
{
out = write(1, buffer, i);
i = 0;
mem_set(buffer, 1024, 0);
}
if (action == -1)
{
i = 0;
mem_set(buffer, 1024, 0);
}
return (out);
}


