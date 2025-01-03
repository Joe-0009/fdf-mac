#include "fdf.h"

int main(int argc, char **argv)
{
    t_vars  vars;
    t_map   map;
    t_point **points;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return (1);
    }

    // Initialize map dimensions
    map = map_dimension(argv[1]);
    
    // Initialize points array
    points = points_init(&map);
    
    // Parse map data
    parse_map(points, argv[1], &map);
    
    // Apply isometric transformation
    iso_points(points, &map);
    
    // Set up window name
    vars.window_name = "FDF";
    
    // Initialize MLX
    init_fdf(&vars);
    
    // Create image
    create_image(&vars);
    
    // Draw the map
    main_draw(&vars, points, &map);
    
    // Put image to window
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);
    
    // Set up hooks
    mlx_hooks(&vars, argv[1]);
    
    // Start MLX loop
    mlx_loop(vars.mlx);
    
    // Cleanup
    free_points(&map, points);
    
    return (0);
}