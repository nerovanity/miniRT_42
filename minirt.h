/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihamani <ihamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:55:25 by oessoufi          #+#    #+#             */
/*   Updated: 2025/10/16 10:45:16 by ihamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define EPS 1e-6

# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_vec
{
	double				x;
	double				y;
	double				z;
}						t_vec;

typedef struct s_camera
{
	t_vec				cord;
	t_vec				dir;
	t_vec				up;
	t_vec				forward;
	t_vec				right;
	int					fov;
	double				aspect;
	double				vpw;
	double				vph;
}						t_camera;

typedef struct s_ray
{
	t_vec				orig;
	t_vec				dir;
}						t_ray;

typedef enum e_object
{
	SPHERE,
	PLANE,
	CYLINDER
}						t_object;

typedef enum e_mandatory
{
	CAMERA,
	LIGHT,
	A_LIGHT
}						t_mandatory;

typedef struct s_objects
{
	t_object			type;
	t_vec				cord;
	t_vec				n_cord;
	int					rgb;
	t_vec				rgbs;
	double				diameter;
	double				height;
	struct s_objects	*next;
}						t_objects;

typedef struct s_light
{
	t_vec				cord;
	double				brightness;
	t_vec				rgb;
}						t_light;

typedef struct s_alight
{
	double				ratio;
	t_vec				rgb;
}						t_alight;

typedef struct s_img
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
	double				aspect_ratio;
}						t_img;

typedef struct s_mlx
{
	void				*mlx;
	void				*mlx_win;
}						t_mlx;

typedef struct s_data
{
	t_camera			camera;
	t_objects			*parse_obj;
	t_objects			**objects;
	t_light				light;
	t_alight			ambient_light;
	int					num_objects;
	int					fd;
	int					flags[3];
	int					color;
	t_img				img;
	t_mlx				mlx;
}						t_data;

typedef struct s_cord
{
	double				x;
	double				y;
}						t_cord;

typedef struct s_cy
{
	t_vec				oc;
	t_vec				d_perp;
	t_vec				oc_perp;
	double				a;
	double				b;
	double				c;
	double				discr;
	double				t1;
	double				t2;
	double				d_dot_axis;
	double				oc_dot_axis;
	t_vec				d_proj;
	t_vec				oc_proj;
	t_vec				hit_point;
}						t_cy;

typedef struct s_cy_top
{
	double				denom;
	double				t_plane;
	t_vec				hit_point;
	t_vec				to_hit;
	double				dist_sq;
	t_vec				to_cap;
}						t_cy_top;

typedef struct s_cy_data
{
	t_cy				vars;
	double				t_body;
	double				t_top;
	double				t_bottom;
	bool				hit_body;
	bool				hit_top;
	bool				hit_bottom;
	double				t_min;
	t_vec				top_center;
	t_vec				bottom_center;
	t_vec				bottom_normal;
	double				r;
}						t_cy_data;

typedef struct s_sp
{
	t_vec				oc;
	double				radius;
	double				b;
	double				c;
	double				discriminant;
	double				t0;
	double				t1;
}						t_sp;

char					*ft_strchr(const char *s, int c);
void					free_split(char **strs);
double					ft_atof(char *str, int *error);
int						ft_atoi(const char *str, int *error);
char					*ft_strjoin(char const *s1, char const *s2);
void					error(char *error);
void					parse_camera(char *line, t_data *data);
void					parse_sphere(char *line, t_data *data);
int						valid_diameter(char *str, double *diameter);
t_objects				*allocate_object(t_data *data);
int						valid_rgb(char *str, t_vec *rgb);
int						correct_commas(char *str);
int						valid_ncords(char *str, double *cords, t_vec *vec);
int						valid_cords(char *str, double *cords, t_vec *vec);
char					*ft_strdup(const char *s1);
void					ft_strlcpy(char *dest, const char *src, size_t dstsize);
char					*ft_strtrim(char const *s1);
void					check_scene(t_data *data);
size_t					ft_strlen(const char *str);
void					error(char *error);
int						file_check(char *file_name);
void					initialize_data(t_data *data, char **argv);
char					*get_next_line(int fd);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strchr(const char *s, int c);
char					**ft_split(char const *s, char sep);
void					free_data_andexit(t_data *data, char *line, char *msg);
void					parse_plane(char *line, t_data *data);
void					parse_cylinder(char *line, t_data *data);
void					parse_ambient_light(char *line, t_data *date);
void					parse_light(char *line, t_data *data);
bool					cylinder_intersect(t_ray *ray, t_objects *object,
							double *t);
void					camera(t_data *data);
t_vec					vec_mul(t_vec a, t_vec b);
int						count_elements(char **elements);
void					handle_op(int *i, int *sign, char c);
void					cy_projections(t_cy *vars, t_ray *ray,
							t_objects *object);
bool					check_t(t_cy *vars, t_ray *ray, t_objects *object,
							double *t);
double					closest(t_cy_data *data);
bool					inter_top_cap(t_ray *ray, t_cy_data *data, t_vec axis,
							double *t);
bool					inter_bottom_cap(t_ray *ray, t_cy_data *data,
							t_vec axis, double *t);
bool					is_within_height(t_objects *object, t_vec point);
double					plane_inter(t_ray *ray, t_objects *plan,
							double *current);
int						key_hook(int keycode, t_data *data);
int						close_win(t_data *data);
t_vec					vec_sub(t_vec v1, t_vec v2);
t_vec					vec_add(t_vec v1, t_vec v2);
t_vec					vec_cross(t_vec v1, t_vec v2);
t_vec					vec_scalar(t_vec v, double s);
double					vec_dot(t_vec v1, t_vec v2);
double					veclen(t_vec v);
t_vec					vec_norm(t_vec v);
bool					vec_equal(t_vec v1, t_vec v2);
t_vec					new_vec(double x, double y, double z);
t_vec					light_object(t_data *data, t_ray *camera_ray,
							int object_index, double closest);
int						obj_intersect(t_ray *camera_ray, t_objects *object,
							double *current);
void					ray_tracing(t_data *data);
int						get_rgb(t_vec color);
int						sphere(t_ray *camera_ray, t_objects *sphere,
							double *current);
void					my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif