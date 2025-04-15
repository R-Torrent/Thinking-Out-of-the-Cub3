#include "../inc/game.h"

void	determine_quad(double angle, int *quad)
{
	double	sin_a;
	double	cos_a;

	sin_a = sin(angle);
	cos_a = cos(angle);
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

void	normalize_angle_to_2pi(double *angle)
{
	*angle = fmod(*angle, 2.0 * M_PI);
	if (*angle < 0.0)
		*angle += (2.0 * M_PI);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
