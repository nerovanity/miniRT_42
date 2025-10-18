/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:38:28 by oessoufi          #+#    #+#             */
/*   Updated: 2025/10/14 11:07:41 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	sphere(t_ray *camera_ray, t_objects *sphere, double *current)
{
	t_sp	var;

	var.oc = vec_sub(camera_ray->orig, sphere->cord);
	var.radius = sphere->diameter * 0.5f;
	var.b = 2 * vec_dot(camera_ray->dir, var.oc);
	var.c = vec_dot(var.oc, var.oc) - var.radius * var.radius;
	var.discriminant = var.b * var.b - 4.0f * var.c;
	if (var.discriminant < EPS)
		return (0);
	var.discriminant = sqrtf(var.discriminant);
	var.t0 = (-var.b - var.discriminant) / (2.0f);
	var.t1 = (-var.b + var.discriminant) / (2.0f);
	if (var.t0 > EPS)
		*current = var.t0;
	else if (var.t1 > EPS)
		*current = var.t1;
	else
		return (0);
	return (1);
}
