This program mimicks the well-known first-person shooter game, Wolfenstein, from the 90's. It is a group effort, developed together with Joppe Boeve (thanks for the collab).

## Overview:

Our program is made up of 3 distinct parts: an input parser, a raycaster and a renderer. As fun extras, we also added openable doors, sprites and a minimap for orientation purposes.

The parser parses the input file, saving data regarding the player starting position, textures, floor and ceiling colors and the maze shape. It also checks that the proposed configuration is suitable (error handling).

The raycaster shoots individual rays across a window to calculate the wall lengths to be used by the renderer.

The renderer colors individual pixels to draw the 3D maze based on the wall lengths and displays the scene to the user.

---

## Compiling: 

1. `make` creates the executable named "cub3D" 

2. `make clean` removes object files
   
3. `make fclean` removes object files and the executable
   
4. `make re` calls `fclean` followed by `all`

---

## Usage:

```
./cub3D [map_file]
```

### Parameters:

map_file: a configuration file (with a .cub extension) outlining texture paths, player start position and maze shape. Please see the example .cub files in the 'test_maps' directory to set one up or use one directly.
