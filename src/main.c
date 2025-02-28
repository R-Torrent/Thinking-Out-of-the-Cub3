#include "../inc/game.h"

void draw_all(void *param)
{
	t_game *game;
	game = (t_game *)param;

	cast_rays(game);
	if (game->is_mmap)
	{
		draw_grid(game, game->data->map_data.rows, game->data->map_data.cols);
		
		// printf ("drawing grid\n");
		int i = 0;
		if (game->is_debug == false)
			game->ray->number_of_rays = SCREEN_WIDTH;
		else
			game->ray->number_of_rays = 1;
			
		while (i < game->ray->number_of_rays)
		// while (i < 1)
		{
			draw_bresenham_ray(game, game->camera.pos, game->ray->ray_end[i]);
			//DDA_ray(game, game->camera.pos, game->ray->ray_end[i], 0xA4FFAAFF);
			i++;
		}
		
		draw_player(game);
	
		//printf ("player angle %f\n", game->player.angle);
		draw_player_direction(game, (t_pos){game->camera.pos.x, game->camera.pos.y}, game->player.angle);
	}
	print_stats(game);
}

static void allocate_structures(t_game **pgame)
{
	*pgame = malloc(sizeof(t_game));

	if (*pgame)
	{
		(*pgame)->data = malloc(sizeof(t_data));
		(*pgame)->ray = ft_calloc(1, sizeof(t_ray));
		(*pgame)->mapdata = NULL;
		(*pgame)->mlx = NULL;
		(*pgame)->stats = NULL;
		(*pgame)->scene = NULL;
		if ((*pgame)->data && (*pgame)->ray)
			return ;
	}
	clean_nicely(*pgame, "Out of memory");
}

static void check_arguments(t_game *game, int argc, char *argv[])
{
	char	*extension;

	if (argc >= 2)
		game->is_debug = !ft_strncmp(*++argv, "-d", 3);
	if (game->is_debug)
	{
		argc--;
		argv++;
	}
	if (argc < 2)
		clean_nicely(game, "Missing scene description file");
	if (argc > 2)
		clean_nicely(game, "Too many arguments");
	extension = ft_strrchr(*argv, '.');
	if (!extension || ft_strncmp(extension, ".cub", 5))
		clean_nicely(game, "Expected `.cub\' extension");
	game->data->scene_description_file = *argv;
}

int	main(int argc, char *argv[])
{
	t_game	*game;
	int width, height;
	int temp_width, temp_height;

	
	allocate_structures(&game);
	check_arguments(game, argc, argv);
	
	parse_file(game, game->data, game->data->scene_description_file);
	printf ("game->data->map_data.cols is %d\n", game->data->map_data.cols);
	
	temp_width = (SCREEN_WIDTH / 2) / game->data->map_data.cols;
	temp_height = (SCREEN_HEIGHT / 2) / game->data->map_data.rows;
	if (temp_width > temp_height)
		game->cell_size = temp_height;
	else
		game->cell_size = temp_width;
	printf ("tile size is %d\n", game->cell_size);
	init_game_struct(game);
	
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	//printf ("main: player angle is %f\n", data->player.angle);
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Ray cast3r", true);
	if (!game->mlx)
		clean_nicely(game, "Failed to initialize MLX42");
	mlx_get_monitor_size(0, &width, &height);
	//printf ("width is %d, height is %d\n", width, height);

	game->scene = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->scene || (mlx_image_to_window(game->mlx, game->scene, X_START, Y_START ) < 0))
		clean_nicely(game, "Failed to create/copy an MLX42 image");
	
	mlx_loop_hook(game->mlx, draw_all, game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_cursor_hook(game->mlx, cursor_hook, game);
	mlx_mouse_hook(game->mlx, mouse_action, game);
	mlx_loop(game->mlx);
	clean_nicely(game, NULL);
}
