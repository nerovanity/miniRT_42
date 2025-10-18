/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessoufi <oessoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:39:05 by ihamani           #+#    #+#             */
/*   Updated: 2025/10/13 14:28:52 by oessoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cy_projections(t_cy *vars, t_ray *ray, t_objects *object)
{
	vars->d_dot_axis = vec_dot(ray->dir, object->n_cord);
	vars->d_proj = vec_scalar(object->n_cord, vars->d_dot_axis);
	vars->d_perp = vec_sub(ray->dir, vars->d_proj);
	vars->oc_dot_axis = vec_dot(vars->oc, object->n_cord);
	vars->oc_proj = vec_scalar(object->n_cord, vars->oc_dot_axis);
	vars->oc_perp = vec_sub(vars->oc, vars->oc_proj);
}

bool	check_t(t_cy *vars, t_ray *ray, t_objects *object, double *t)
{
	if (vars->t1 > EPS)
	{
		vars->hit_point = vec_add(ray->orig, vec_scalar(ray->dir, vars->t1));
		if (is_within_height(object, vars->hit_point))
		{
			*t = vars->t1;
			return (true);
		}
	}
	if (vars->t2 > EPS)
	{
		vars->hit_point = vec_add(ray->orig, vec_scalar(ray->dir, vars->t2));
		if (is_within_height(object, vars->hit_point))
		{
			*t = vars->t2;
			return (true);
		}
	}
	return (false);
}

double	closest(t_cy_data *data)
{
	data->t_min = INFINITY;
	if (data->hit_body && data->t_body < data->t_min)
	{
		data->t_min = data->t_body;
	}
	if (data->hit_top && data->t_top < data->t_min)
	{
		data->t_min = data->t_top;
	}
	if (data->hit_bottom && data->t_bottom < data->t_min)
	{
		data->t_min = data->t_bottom;
	}
	return (data->t_min);
}

bool	inter_top_cap(t_ray *ray, t_cy_data *data, t_vec axis, double *t)
{
	t_cy_top	v;

	v.denom = vec_dot(ray->dir, axis);
	if (fabs(v.denom) < EPS)
		return (false);
	v.to_cap = vec_sub(data->top_center, ray->orig);
	v.t_plane = vec_dot(v.to_cap, axis) / v.denom;
	if (v.t_plane < EPS)
		return (false);
	v.hit_point = vec_add(ray->orig, vec_scalar(ray->dir, v.t_plane));
	v.to_hit = vec_sub(v.hit_point, data->top_center);
	v.dist_sq = vec_dot(v.to_hit, v.to_hit);
	if (v.dist_sq <= data->r * data->r)
	{
		*t = v.t_plane;
		return (true);
	}
	return (false);
}

bool	inter_bottom_cap(t_ray *ray, t_cy_data *data, t_vec axis, double *t)
{
	t_cy_top	v;

	v.denom = vec_dot(ray->dir, axis);
	if (fabs(v.denom) < EPS)
		return (false);
	v.to_cap = vec_sub(data->bottom_center, ray->orig);
	v.t_plane = vec_dot(v.to_cap, axis) / v.denom;
	if (v.t_plane < EPS)
		return (false);
	v.hit_point = vec_add(ray->orig, vec_scalar(ray->dir, v.t_plane));
	v.to_hit = vec_sub(v.hit_point, data->bottom_center);
	v.dist_sq = vec_dot(v.to_hit, v.to_hit);
	if (v.dist_sq <= data->r * data->r)
	{
		*t = v.t_plane;
		return (true);
	}
	return (false);
}
