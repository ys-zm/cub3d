#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
Foreground colors:

    Black: \033[30m
    Red: \033[31m
    Green: \033[32m
    Yellow: \033[33m
    Blue: \033[34m
    Magenta: \033[35m
    Cyan: \033[36m
    White: \033[37m

Background colors (use 40 to 47 instead of 30 to 37):

    Black: \033[40m
    Red: \033[41m
    Green: \033[42m
    Yellow: \033[43m
    Blue: \033[44m
    Magenta: \033[45m
    Cyan: \033[46m
    White: \033[47m

Text styles:

    Reset: \033[0m (resets colors and styles to default)
    Bold: \033[1m
    Underline: \033[4m
    Blink: \033[5m
    Reverse: \033[7m
*/

int main(void)
{
	// parser tests
	printf(" \033[37m \033[5mPARSER TESTS \033[0m \n\n");
	// bad extension
	printf("\033[1;33m TEST FOR BAD EXTENSION: \033[0m\n");
	system("./app test_maps/bad_ext.u");
	printf("\n");
	// duplicate elements
	printf("\033[1;33m TEST FOR DUPLICATE ELEMENTS: \033[0m\n");
	system("./app test_maps/duplicate_elements.cub");
	printf("\n");
	// no player
	printf("\033[1;33m TEST FOR NO PLAYER: \033[0m\n");
	system("./app test_maps/no_player.cub");
	printf("\n");
	// not enough elements
	printf("\033[1;33m TEST FOR MISSING ELEMENTS: \033[0m\n");
	system("./app test_maps/not_enough_elements.cub");
	printf("\n");
	// too many players
	printf("\033[1;33m TEST FOR TOO MANY PLAYERS: \033[0m\n");
	system("./app test_maps/too_many_players.cub");
	printf("\n");
	// unclosed walls
	printf("\033[1;33m TEST FOR UNCLOSED WALLS: \033[0m\n");
	system("./app test_maps/unclosed_walls.cub");
	printf("\n");
	// map with invalid chars
	printf("\033[1;33m TEST FOR MAP WITH INVALID CHARS: \033[0m\n");
	system("./app test_maps/wrong_chars.cub");
	printf("\n");
	// wrong order
	printf("\033[1;33m TEST FOR FILE WITH WRONG ORDER: \033[0m\n");
	system("./app test_maps/wrong_order.cub");
	printf("\n");
	// file failed to open
	printf("\033[1;33m TEST FOR FILE FAILED TO OPEN: \033[0m\n");
	system("./app test_maps/filedoesntexist.cub");
	printf("\n");
	// file failed to open
	printf("\033[1;33m TEST FOR FILE WITH NO MAP: \033[0m\n");
	system("./app test_maps/file_with_no_map.cub");
	printf("\n");
	// random chars between elements
	printf("\033[1;33m TEST FOR FILE WITH RANDOM CHARS BETWEEN ELEMENTS: \033[0m\n");
	system("./app test_maps/random_chars_between_elements.cub");
	printf("\n");
	// colour code wrong
	printf("\033[1;33m TEST FOR FILE WITH WRONG COLOR CODES: \033[0m\n");
	system("./app test_maps/wrong_color_code.cub");
	printf("\n");
	return (0);
}