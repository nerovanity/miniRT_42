/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessoufi <oessoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:38:01 by ihamani           #+#    #+#             */
/*   Updated: 2025/10/13 14:28:52 by oessoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65307)
		free_data_andexit(data, NULL, NULL);
	return (0);
}

int	close_win(t_data *data)
{
	free_data_andexit(data, NULL, NULL);
	return (0);
}
