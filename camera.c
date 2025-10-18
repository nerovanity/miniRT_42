/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessoufi <oessoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:30:31 by ihamani           #+#    #+#             */
/*   Updated: 2025/10/13 14:28:52 by oessoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_up(t_vec forward)
{
	if (vec_equal(forward, new_vec(0, 1, 0)))
		return (new_vec(0, 0, 1));
	else if (vec_equal(forward, new_vec(0, -1, 0)))
		return (new_vec(0, 0, -1));
	else
		return (new_vec(0, 1, 0));
}

void	camera(t_data *data)
{
	t_vec	tmp_a;
	t_vec	tmp_b;

	data->camera.aspect = data->img.aspect_ratio;
	data->camera.vpw = 2 * tan((data->camera.fov * M_PI / 180.0) / 2);
	data->camera.vph = data->camera.vpw / data->img.aspect_ratio;
	data->camera.forward = vec_norm(data->camera.dir);
	tmp_a = vec_cross(get_up(data->camera.forward), data->camera.forward);
	data->camera.right = vec_norm(tmp_a);
	tmp_b = vec_cross(data->camera.right, data->camera.forward);
	data->camera.up = vec_norm(tmp_b);
}
