/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 09:41:49 by ihamani           #+#    #+#             */
/*   Updated: 2025/10/14 09:42:15 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec	vec_norm(t_vec v)
{
	t_vec	tmp;
	double	len;

	len = veclen(v);
	if (len == 0)
		return ((t_vec){0, 0, 0});
	tmp.x = v.x / len;
	tmp.y = v.y / len;
	tmp.z = v.z / len;
	return (tmp);
}

t_vec	vec_cross(t_vec v1, t_vec v2)
{
	t_vec	tmp;

	tmp.x = v1.y * v2.z - v1.z * v2.y;
	tmp.y = v1.z * v2.x - v1.x * v2.z;
	tmp.z = v1.x * v2.y - v1.y * v2.x;
	return (tmp);
}

bool	vec_equal(t_vec v1, t_vec v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return (true);
	return (false);
}

t_vec	new_vec(double x, double y, double z)
{
	t_vec	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec	vec_mul(t_vec a, t_vec b)
{
	t_vec	tmp;

	tmp.x = a.x * b.x;
	tmp.y = a.y * b.y;
	tmp.z = a.z * b.z;
	return (tmp);
}
