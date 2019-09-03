/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 09:58:12 by tbondare          #+#    #+#             */
/*   Updated: 2018/08/04 20:33:46 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_atoi(const char *str)
{
	unsigned long int	num;
	int					a;

	num = 0;
	a = 1;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			a = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		num = (*str - 48) + num * 10;
		str++;
	}
	if (a == 1 && num > 9223372036854775807)
		return (-1);
	if (a == -1 && num > 9223372036854775807)
		return (0);
	return (num * a);
}
