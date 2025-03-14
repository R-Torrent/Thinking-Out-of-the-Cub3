#include "../inc/game.h"

static unsigned int	count_int_length(long long n)
{
	unsigned int	i;

	i = 0;
	if (n < 0)
	{
		n *= (-1);
		i++;
	}
	if (n == 0)
		i++;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_intstr(char *str, int n)
{
	long long		nbr;
	unsigned int	nbr_len;
	unsigned int	i;

	nbr = n;
	nbr_len = count_int_length(nbr);
	str[nbr_len] = '\0';
	i = 0;
	if (nbr == 0)
	{
		str[i] = '0';
		return ;
	}
	if (nbr < 0)
	{
		str[i] = '-';
		nbr *= (-1);
	}
	while (i < nbr_len && nbr > 0)
	{
		str[nbr_len - 1 - i] = nbr % 10 + '0';
		nbr /= 10;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nbr_len;

	nbr_len = count_int_length((long long)n);
	str = (char *) malloc (nbr_len + 1);
	if (str == NULL)
		return (NULL);
	ft_intstr(str, n);
	return (str);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *) malloc (len + 1);
	if (str == NULL)
		return (NULL);
	i = 0 ;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char *ft_ftoa(float n, int precision)
{
    int int_part = (int)n;  // Extract the integer part
    float decimal_part = n - int_part;  // Extract the decimal part
    int i = 0, digit;
    char *str;

    // Allocate enough memory for the result string
    // Worst case: integer part + '.' + precision digits for the fractional part + null terminator
    str = (char *)malloc(50 * sizeof(char));  
    if (!str)
        return NULL;

    // Handle the integer part (negative or positive)
    if (int_part < 0)
    {
        str[i++] = '-';  // Add the minus sign for negative numbers
        int_part = -int_part;  // Work with positive integer part for easier handling
    }

    // Convert the integer part to string (reverse order)
    int temp_int_part = int_part;
    int num_digits = 0;
    while (temp_int_part > 0)
    {
        num_digits++;
        temp_int_part /= 10;
    }

    // If the integer part is 0, we still need to handle it
    if (num_digits == 0)
        str[i++] = '0';

    for (int j = 0; j < num_digits; j++)
    {
        str[i + num_digits - 1 - j] = (int_part % 10) + '0';  // Get last digit
        int_part /= 10;
    }
    i += num_digits;

    // Add the decimal point
    str[i++] = '.';

    // Handle the fractional part (multiply by 10 to extract digits)
    for (int j = 0; j < precision; j++)
    {
        decimal_part *= 10;
        digit = (int)decimal_part;
        str[i++] = digit + '0';  // Convert digit to char
        decimal_part -= digit;  // Remove the integer part from decimal part
    }

    // Null-terminate the string
    str[i] = '\0';

    return str;
}

void	ft_swap_ptrs(void **ptr1, void **ptr2)
{
	void	*temp;

	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}
