#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef enum e_map_data {
    MAP_EMPTY,
    MAP_WALL,
    MAP_FLOOR,
    MAP_DIR
} t_map_data;

typedef enum e_direction {
    N,
    S,
    E,
    W
} t_direction;


typedef struct s_map_arr {
    t_map_data *content;
    t_direction start_dir;
    size_t      width;
    size_t      height;
} t_map;



// static const char *map[] = 
// {
//             "1111111111111111111111111",
//             "1000000000110000000000001",
//             "1011000001110000000000001",
//             "1001000000000000000000001",
//     "111111111011000001110000000000001",
//     "100000000011000001110111111111111",
//     "11110111111111011100000010001",
//     "11110111111111011101010010001",
//     "11000000110101011100000010001",
//     "10000000000000001100000010001",
//     "10000000000000001101010010001",
//     "11000001110101011111011110N0111",
//     "11110111 1110101 101111010001",
//     "11111111 1111111 111111111111"
// }
