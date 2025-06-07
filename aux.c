#include "philosopher.h"

int	ft_atoi(const char *str)
{
	int				i = 0;
	int				sign = 1;
	long long int	result = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if ((result * sign) > INT_MAX || (result * sign) < INT_MIN)
			return (-1);
		i++;
	}
	return ((int)(result * sign));
}

int	is_number(char *str)
{
	int	i = 0;

	if (!str || !str[0])
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

