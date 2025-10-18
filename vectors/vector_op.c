/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 09:42:25 by ihamani           #+#    #+#             */
/*   Updated: 2025/10/14 09:42:25 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec	vec_add(t_vec v1, t_vec v2)
{
	t_vec	tmp;

	tmp.x = v1.x + v2.x;
	tmp.y = v1.y + v2.y;
	tmp.z = v1.z + v2.z;
	return (tmp);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec	tmp;

	tmp.x = v1.x - v2.x;
	tmp.y = v1.y - v2.y;
	tmp.z = v1.z - v2.z;
	return (tmp);
}

t_vec	vec_scalar(t_vec v, double s)
{
	t_vec	tmp;

	tmp.x = v.x * s;
	tmp.y = v.y * s;
	tmp.z = v.z * s;
	return (tmp);
}

double	vec_dot(t_vec v1, t_vec v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

double	veclen(t_vec v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}
