#include "../inc/game.h"

void	absolute(int *d, int *i)
{
	if (*d < 0)
	{
		*i = -1;
		*d = -(*d);
	}
}

void determine_quad(double angle, int *quad)
{
    double cos_a = cos(angle);
    double sin_a = sin(angle);

    if (cos_a > 0 && sin_a > 0)
        *quad = 1;
    else if (cos_a < 0 && sin_a > 0)
        *quad = 2;
    else if (cos_a < 0 && sin_a < 0)
        *quad = 3;
    else if (cos_a > 0 && sin_a < 0)
        *quad = 4;
    else if (cos_a == 1 && sin_a == 0)
        *quad = 1;
    else if (cos_a == 0 && sin_a == 1)
        *quad = 2;
    else if (cos_a == -1 && sin_a == 0)
        *quad = 3;
    else if (cos_a == 0 && sin_a == -1)
        *quad = 4;
}


void	safe_put_pixel(t_game *game, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= SCREEN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= SCREEN_HEIGHT)
		return ;
	
	mlx_put_pixel(game->scene, x, y, color);
}

void	normalize_angle_to_2pi(float *angle)
{
	if (*angle < 0)
		*angle += (2 * M_PI);
	if (*angle > 2 * M_PI)
		*angle -= (2 * M_PI);
	
}