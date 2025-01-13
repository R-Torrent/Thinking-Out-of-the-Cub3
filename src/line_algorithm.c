#include "../inc/game.h"

void bresenham_ray(t_game *game, t_pos start, t_pos end)
{
	int x = (int)round(start.x);
	int y = (int)round(start.y);
	int end_x = (int)round(end.x);
	int end_y = (int)round(end.y);
	int delta_x = (int)round(fabs(end.x - start.x));
	int delta_y = (int)round(fabs(end.y - start.y));
	int decision_variable;
    int distance;


	// Direction factors to ensure correct increments
	int step_x = 1;
	int step_y = 1;

	// Determine direction of x and y
	if (end_x < start.x)  // Moving left
		step_x = -1;
	if (end_y < start.y)  // Moving up
		step_y = -1;

	// Case 2: Positive slope (slope >= 0)
	if (delta_x >= delta_y)
	{
        //printf ("positive slope, \n");
		decision_variable = 2 * delta_y - delta_x;
		while (1)
		{

			if ((x == end_x && y == end_y) || x < X_START || x >= X_END || y < Y_START || y >= Y_END)
            {
                distance =  sqrt((x - start.x) * (x - start.x) + (y - start.y) * (y - start.y));
                //printf ("positive slope, distance is %d\n", distance);
                return;
            }
            distance =  sqrt((x - start.x) * (x - start.x) + (y - start.y) * (y - start.y));
            //printf ("negative slope, distance is %d\n", distance);
			mlx_put_pixel(game->rays, x, y, distance_to_color(distance));
			
			if (decision_variable >= 0)
			{
				decision_variable -= 2 * delta_x;
				y += step_y;
			}
			decision_variable += 2 * delta_y;
			x += step_x;
		}
	}
	// Case 3: Negative slope (slope < 0)
    
	else if (delta_y > delta_x)  //also includes nearly vertical (dx =71, dy =72 for example)
	{
        //printf ("3. dx is %d, dy is %d\n", delta_x, delta_y);
        //printf ("negative slope\n");
		decision_variable = 2 * delta_x - delta_y;
		while (1)
		{

			if ((x == end_x && y == end_y) || x < X_START || x >= X_END || y < Y_START || y >= Y_END)
            {
                // || (game->ray->found_vertical_first == 1 &&  x > X_END)
                // || (game->ray->found_vertical_first == 0 &&  y > Y_END))
                distance =  sqrt((x - start.x) * (x - start.x) + (y - start.y) * (y - start.y));
                //printf ("Negative slope, distance is %d\n", distance);
                return;
            }
				
			//int distance = get_distance(start, end);
            distance =  sqrt((x - start.x) * (x - start.x) + (y - start.y) * (y - start.y));
            //printf ("positive slope, distance is %d\n", distance);
			mlx_put_pixel(game->rays, x, y, distance_to_color(distance));
			
			if (decision_variable >= 0)
			{
				decision_variable -= 2 * delta_y;
				x += step_x;
			}
			decision_variable += 2 * delta_x;
			y += step_y;
		}
	}
		return;
}

void DDA_ray(t_game *game, t_pos start, t_pos end)
{
    double dx = end.x - start.x;
    double dy = end.y - start.y;
    double steps;

    if (fabs(dx) == fabs(dy))
        {
            printf ("!, \n");
        }
    // Determine the number of steps needed
    // if (fabs(dx) > fabs(dy))
    //     steps = fabs(dx);
    // else 
    //     steps = fabs(dy);
    steps = fmax(fabs(dx), fabs(dy));

    //printf ("steps is %f\n", steps);
    double x_increment = dx / steps;
    double y_increment = dy / steps;

    double x = start.x;
    double y = start.y;
    int step_count = 0;
	
    while (step_count <= steps) 
    {
        (void)game;
        
        double distance = get_distance(start, (t_pos){x, y});
        
        //printf("Distance at step %d: %f\n", step_count, distance);
        //mlx_put_pixel(game->rays, (int)round(x), (int)round(y), distance_to_color(distance));
        mlx_put_pixel(game->rays, (int)round(x) - X_START,  (int)round(y) - Y_START, distance_to_color(distance));
    
        x += x_increment;
        y += y_increment;
        step_count++;
    }
}

