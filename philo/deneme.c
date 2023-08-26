#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
void put_string(char *str,int *length)
{
    if(!str)
        str = "(null)";
    while(*str)
        *length += write(1, str++,1);
}
 
void put_digit(long long int nbr, int str_base, int *length)
{
    char *hex = "0123456789abcdef";
    
    if(nbr < 0)
    {
        nbr *= -1;
        *length += write(1,"-",1);
    }
    else if(nbr >= str_base)
        put_digit((nbr / str_base), str_base, length);
    *length += write(1,&hex[nbr % str_base],1);
}
int ft_printf(const char *format, ...)
{
    int length = 0;
    
    va_list yahya;
    
    va_start(yahya,format);
    
    while(*format)
    {
        if(*format == '%' && (*(format + 1)))
        {
            format++;
            if(*format == 's')
                put_string(va_arg(yahya,char *), &length);
            else if(*format == 'd')
                put_digit((long long int)va_arg(yahya,int), 10, &length);
            else if(*format == 'x')
                put_digit((long long int)va_arg(yahya,unsigned int), 16, &length);
        }
        else
            length += write(1, format, 1);
        format++;
    }
    return(va_end(yahya), length);
}
int main()
{
    int len = 0;
    
    len = ft_printf("%d %s %x %o\n",12,"yahya",13 );
    printf("%d %s %x\n",12,"yahya",13);
    printf("%d",len);
    
    return(0);
}
