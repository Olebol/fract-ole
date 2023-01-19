/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractals.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 17:40:20 by opelser       #+#    #+#                 */
/*   Updated: 2023/01/19 21:58:55 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		checkjulia(float x, float y, int max_iter)
{
	float	imaginary_x = x;
	float	imaginary_y = y;
	float	tmp;
	int		iterations = 0;
	float	cx = 0.150, cy = 0.635;

	while ((imaginary_x * imaginary_x + imaginary_y * imaginary_y) <= 4 && iterations < max_iter)
	{
		tmp = (imaginary_x * imaginary_x) - (imaginary_y * imaginary_y) + cx;
		imaginary_y = 2 * (imaginary_x * imaginary_y) + cy;
		imaginary_x = tmp;
		iterations++;
	}
	return (iterations);
}

float		checkmandelbrot(float x, float y, int max_iter)
{
	float	imaginary_x = x;
	float	imaginary_y = y;
	float	tmp;
	float	iterations = 0;

	while ((imaginary_x * imaginary_x + imaginary_y * imaginary_y) <= 4 && iterations < max_iter)
	{
		tmp = (imaginary_x * imaginary_x) - (imaginary_y * imaginary_y) + x;
		imaginary_y = 2 * (imaginary_x * imaginary_y) + y;
		imaginary_x = tmp;
		iterations++;
	}
	return (iterations);
}

uint32_t	get_rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void	mandelbrot(t_data *d)
{
	float		x;
	float		y;
	float		scaled[2];
	float		iter;
	int			colour;

	x = 0;
	y = 0;
	while (x < WIDTH)
	{
		scaled[0] = d->x[0] + (x / WIDTH) * (d->x[1] - d->x[0]);
		while (y < HEIGHT)
		{
			scaled[1] = d->y[0] + (y / HEIGHT) * (d->y[1] - d->y[0]);
			// iter = checkmandelbrot(scaled[0], scaled[1], d->iter);
			iter = checkjulia(scaled[0], scaled[1], d->iter);
			if (iter == d->iter)
				colour = 0xFF;
			else
				colour = get_rgba(0xFF, 0x00, 0xFF, (255 * iter / d->iter));
			mlx_put_pixel(d->img, x, y, colour);
			y++;
		}
		x++;
		y = 0;
	}
}
