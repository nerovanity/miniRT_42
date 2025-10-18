/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:55:56 by oessoufi          #+#    #+#             */
/*   Updated: 2025/10/16 10:54:55 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_rgb(t_vec color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;

	a = 255;
	r = (unsigned char)(color.x * 255.0f);
	g = (unsigned char)(color.y * 255.0f);
	b = (unsigned char)(color.z * 255.0f);
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	initialize_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
	{
		free_data_andexit(data, NULL, "Error\n");
	}
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->img.width,
			data->img.height, "miniRT");
	if (data->mlx.mlx_win == NULL)
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		free_data_andexit(data, NULL, "Error\n");
	}
	data->img.img = mlx_new_image(data->mlx.mlx, data->img.width,
			data->img.height);
	if (data->img.img == NULL)
	{
		mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		free_data_andexit(data, NULL, "Error\n");
	}
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
}

void	initialize_data(t_data *data, char **argv)
{
	data->img.aspect_ratio = 16.0 / 9.0;
	data->img.width = 1200;
	data->img.height = data->img.width / data->img.aspect_ratio;
	data->flags[CAMERA] = 0;
	data->flags[LIGHT] = 0;
	data->flags[A_LIGHT] = 0;
	data->fd = -1;
	data->parse_obj = NULL;
	data->objects = NULL;
	data->num_objects = 0;
	data->fd = file_check(argv[1]);
	check_scene(data);
	camera(data);
	initialize_mlx(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error("Error\nUsage ./miniRT *.rt\n");
	initialize_data(&data, argv);
	ray_tracing(&data);
	mlx_put_image_to_window(data.mlx.mlx, data.mlx.mlx_win, data.img.img, 0, 0);
	mlx_key_hook(data.mlx.mlx_win, key_hook, &data);
	mlx_hook(data.mlx.mlx_win, 17, 1L, close_win, &data);
	mlx_loop(data.mlx.mlx);
	free_data_andexit(&data, NULL, NULL);
}
