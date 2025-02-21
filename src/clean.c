#include "../inc/game.h"

void	delete_images(t_game *game)
{
	if (game->stats)
		mlx_delete_image(game->mlx, game->stats);
	if (game->scene)
		mlx_delete_image(game->mlx, game->scene);
}

void	del_token(void *token)
{
	free(((struct s_token *)token)->value);
	free(token);
}

//use ft_free as in minishell
void	clean_nicely(t_game *game, char *error_message)
{
	//free_map_grid
	if (game)
	{
		ft_lstclear(data->tokens, del_token);
		free(game->data->mapdata);
		free(game->data);
		delete_images(game);
		if (game->mlx)
		 	mlx_terminate(game->mlx); //causes seg fault??
		free(game->ray);
		free(game);
	}
	if (error_message)
	{
		printf("Error\ncube3D: %s\n", error_message);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
 //add cleaning the wall textures
