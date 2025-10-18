/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:08:47 by oessoufi          #+#    #+#             */
/*   Updated: 2025/10/14 09:43:48 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

static int	ft_is_digit(int i)
{
	if (i >= '0' && i <= '9')
		return (1);
	return (0);
}

double	ft_atof(char *str, int *error)
{
	int		i;
	double	r;
	int		sign;
	double	div;

	i = 0;
	sign = 1;
	div = 0.1;
	r = 0;
	handle_op(&i, &sign, str[0]);
	while (str[i] && ft_is_digit(str[i]) && str[i] != '.')
		r = r * 10 + (str[i++] - '0');
	if (str[i] == '.')
		i++;
	while (str[i] && ft_is_digit(str[i]))
	{
		r = r + ((str[i] - '0') * div);
		div = div * 0.1;
		i++;
	}
	if (str[i] && !ft_is_digit(str[i]))
		*error = 1;
	return (r * sign);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	error(char *error)
{
	write(2, error, ft_strlen(error));
	exit(1);
}

int	count_elements(char **elements)
{
	int	i;

	if (elements == NULL)
		return (0);
	i = 0;
	while (elements[i])
		i++;
	return (i);
}
