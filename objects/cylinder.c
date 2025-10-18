/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessoufi <oessoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 10:39:35 by ihamani           #+#    #+#             */
/*   Updated: 2025/10/13 14:28:52 by oessoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_within_height(t_objects *object, t_vec point)
{
	t_vec	to_point;
	double	proj;

	to_point = vec_sub(point, object->cord);
	proj = vec_dot(to_point, object->n_cord);
	return (proj >= -object->height / 2.0 && proj <= object->height / 2.0);
}

double	cl_discr(double a, double b, double c)
{
	return (b * b - 4.0 * a * c);
}

bool	intersect_cylinder_body(t_ray *ray, t_objects *object,
		t_cy_data *data, double *t)
{
	data->vars.oc = vec_sub(ray->orig, object->cord);
	cy_projections(&data->vars, ray, object);
	data->vars.a = vec_dot(data->vars.d_perp, data->vars.d_perp);
	data->vars.b = 2.0 * vec_dot(data->vars.d_perp, data->vars.oc_perp);
	data->vars.c = vec_dot(data->vars.oc_perp,
			data->vars.oc_perp) - data->r * data->r;
	if (fabs(data->vars.a) < EPS)
		return (false);
	data->vars.discr = cl_discr(data->vars.a, data->vars.b, data->vars.c);
	if (data->vars.discr < 0.0)
		return (false);
	data->vars.discr = sqrt(data->vars.discr);
	data->vars.t1 = (-data->vars.b - data->vars.discr) / (2.0 * data->vars.a);
	data->vars.t2 = (-data->vars.b + data->vars.discr) / (2.0 * data->vars.a);
	return (check_t(&data->vars, ray, object, t));
}

bool	cylinder_intersect(t_ray *ray, t_objects *object, double *t)
{
	t_cy_data	data;

	data.t_body = INFINITY;
	data.t_top = INFINITY;
	data.t_bottom = INFINITY;
	data.r = object->diameter / 2.0;
	data.hit_body = intersect_cylinder_body(ray, object, &data, &data.t_body);
	data.top_center = vec_add(object->cord,
			vec_scalar(object->n_cord, object->height / 2.0));
	data.bottom_center = vec_add(object->cord,
			vec_scalar(object->n_cord, -object->height / 2.0));
	data.hit_top = inter_top_cap(ray, &data, object->n_cord,
			&data.t_top);
	data.bottom_normal = vec_scalar(object->n_cord, -1.0);
	data.hit_bottom = inter_bottom_cap(ray, &data, data.bottom_normal,
			&data.t_bottom);
	if (!data.hit_body && !data.hit_top && !data.hit_bottom)
		return (false);
	*t = closest(&data);
	return (true);
}
