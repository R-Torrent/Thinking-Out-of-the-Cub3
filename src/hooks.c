#include "../inc/game.h"

void horiz_collision(t_game *game, t_pos new[])
{
	if (((game->player.angle_quad == 1 || game->player.angle_quad == 4)
			&& game->data->map[get_block_index2(game, &new[1], 0).index] != WALL
			&& game->data->map[get_block_index2(game, &new[3], 0).index] != WALL)
			|| ((game->player.angle_quad == 2 || game->player.angle_quad == 3)
			&& game->data->map[get_block_index2(game, &new[0], 0).index] != WALL
			&& game->data->map[get_block_index2(game, &new[2], 0).index] != WALL))
		game->player.p_pos.x = new->x;  // Move player horizontally
}

void vertical_collision(t_game *game, t_pos new[])
{
	if (((game->player.angle_quad == 1 || game->player.angle_quad == 2)
			&& game->data->map[get_block_index2(game, &new[0], 0).index] != WALL
			&& game->data->map[get_block_index2(game, &new[1], 0).index] != WALL)
			|| ((game->player.angle_quad == 3 || game->player.angle_quad == 4)
			&& game->data->map[get_block_index2(game, &new[2], 0).index] != WALL
			&& game->data->map[get_block_index2(game, &new[3], 0).index] != WALL))
		game->player.p_pos.y = new->y;  // Move player vertically
}

void check_collision(t_game *game, t_pos *new_pos) 
{
	t_pos	new_corners[4] = {
			*new_pos, // tl
			{new_pos->x + PLAYER_SIZE * CONST, new_pos->y}, // tr
			{new_pos->x, new_pos->y + PLAYER_SIZE * CONST}, // bl
			{new_pos->x + PLAYER_SIZE * CONST, new_pos->y + PLAYER_SIZE * CONST}}; //br

    // Check for collisions in all directions
    horiz_collision(game, new_corners);  // Check horizontal collision
    game->camera.pos.x = round(game->player.p_pos.x + (PLAYER_SIZE + CONST) / 2);
    game->camera.pos.y = round(game->player.p_pos.y + (PLAYER_SIZE + CONST) / 2);
}


static void check_keys_for_movement(t_game *game, mlx_key_data_t keydata)
{
	t_pos new;
	new.x = game->player.p_pos.x;
	new.y = game->player.p_pos.y;
	double new_angle = game->player.angle;
	double angle_size = 2 * M_PI / 100;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x += round(cos(game->player.angle) * DISTANCE_PER_TURN);
		new.y -= round(sin(game->player.angle) * DISTANCE_PER_TURN);
	}
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x -= round(cos(game->player.angle) * DISTANCE_PER_TURN);
		new.y += round(sin(game->player.angle) * DISTANCE_PER_TURN);
	}
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x -= round(sin(game->player.angle) * DISTANCE_PER_TURN);
		new.y -= round(cos(game->player.angle) * DISTANCE_PER_TURN);
	}
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		new.x += round(sin(game->player.angle) * DISTANCE_PER_TURN);
		new.y += round(cos(game->player.angle) * DISTANCE_PER_TURN);
	}

	// Boundary check for player movement
	if (new.x != game->player.p_pos.x || new.y != game->player.p_pos.y)
	{
		if (new.x < X_START)
			new.x = X_START;
		if (new.y < Y_START)
			new.y = Y_START;
		if (new.x > X_START + game->data->minimap_data.width - CONST)
			new.x = X_START + game->data->minimap_data.width - CONST;
		if (new.y > Y_START + game->data->minimap_data.height - CONST)
			new.y = Y_START + game->data->minimap_data.height - CONST;
		int x_offset = 0;
		int y_offset = 0;

		if (is_collision(game, new, &(game->player)))
		{	
			printf ("Collision! x_offset %d y_offest %d\n", x_offset, y_offset);
			printf ("sin(game->player.angle) %f, cos(game->player.angle) %f\n", sin(game->player.angle), cos(game->player.angle));
		}
		else
		{
			game->player.p_pos.x = round(new.x);
			game->player.p_pos.y = round(new.y);
			game->camera.pos.x = round(game->player.p_pos.x + CONST /2);
			game->camera.pos.y = round(game->player.p_pos.y + CONST /2);
			mlx_delete_image(game->mlx, game->stats);
			if (game->is_mmap)
				print_stats(game);

		}
	}

	if (game->is_mouse_active == false &&(keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		new_angle -= angle_size; // Rotate clockwise (right)
	if ( game->is_mouse_active == false && (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)))
		new_angle += angle_size; // Rotate counterclockwise (left)
	//printf ("in check for movement\n");
	normalize_angle_to_2pi(&new_angle);
	if (new_angle != game->player.angle)
	{
		determine_quad(new_angle, &game->player.angle_quad);
		game->player.angle = new_angle;
		mlx_delete_image(game->mlx, game->stats);
		if (game->is_mmap)
			print_stats(game);

	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		printf("Player pressed ESC. Closing the game...\n");
		mlx_close_window(game->mlx);
		clean_nicely(game, NULL);
	}
	check_keys_for_movement(game, keydata);
}
