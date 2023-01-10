
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchompoo <jchompoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:17:03 by root              #+#    #+#             */
/*   Updated: 2023/01/06 08:14:44 by jchompoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../libft/libft.h"

int convert_int(int c);
int ft_putchar(int c);
int check_type(int c, va_list);
int ft_putstr(char* str);
int convert_x(unsigned int c, int f);
int x_len(unsigned int c, int base);
int convert_u(unsigned int c);

int	ft_printf(const char *str, ...)
{
    int len;
	va_list args;
	va_start(args, str);

     if (str == NULL)
         return (0);
    len = 0;
	while (*str != '\0')
	{
		if (*str == '%')
		{
		 	len += check_type(*(str + 1), args);
            str++;
		}
	    else
		    len += ft_putchar(*str);
	    str++;
	}
    va_end(args);
    return(len);
}

int check_type(int c, va_list args)
{
    int len;

    len = 0;
    if (c == 'd' || c == 'i')
		len += convert_int(va_arg(args, int));
	else if (c == 's')
		len += ft_putstr(va_arg(args, char*));
    else if (c == 'c')
       len +=  ft_putchar(va_arg(args, int));
    else if (c == 'p')
        ft_putchar_fd('p', 1);
    else if (c == 'u')
        len += convert_u(va_arg(args, unsigned int));
    else if (c == 'x')
        len += convert_x(va_arg(args, unsigned int), 'x');
    else if (c == 'X')
        len += convert_x(va_arg(args, unsigned int), 'X');
    else if (c == '%')
        len += ft_putchar('%');
    return(len);
}

int convert_int(int c)
{
    int i;
    i = ft_putstr(ft_itoa(c));
    return (i);
}

int ft_putchar(int c)
{
    write(1, &c, 1);
    return (1);
}

int convert_x(unsigned int c, int f)
{ 
    if (c >= 16)
    {
        convert_x(c / 16, f);
        convert_x(c % 16, f);
    }
    else if (c <= 9)
        ft_putchar(c + '0');
    else
    {
        if (f == 'x')
            ft_putchar(c - 10 + 'a');
        else
            ft_putchar(c - 10 + 'A');
    }
    return (x_len(c,16));
}

int convert_u(unsigned int c)
{
    if (c >= 10)
    {
        convert_u(c / 10);
        convert_u(c % 10);
    }
    else
        ft_putchar(c + '0');
    //ft_printf("The c is %i\n", c);
    return (x_len(c, 10));
}

int ft_putstr(char* str)
{
    int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
    return (i);
}

int x_len(unsigned int c, int base)
{
    int i;

    if (c == 0)
        return (1);
    i = 0;
    while (c != 0)
    {
        i++;
        c /= base;
    }
    return (i);
}