#include "meta.h"

// returns 1 if walls are not closed
int check_horiz_left(t_meta *meta, char *map)
{
	uint32_t x;
	uint32_t y;
	bool closed;

    y = 0;
    while (y < meta->map.height)
    {
        closed = false;
        x = 0;
        while (x < meta->map.width)
        {
            // printf("c: %c\n", map[find_index(meta, y, x)]);
            if (map[find_index(meta, y, x)] == '1')
                closed = true;
            if (!closed && map[find_index(meta, y, x)] == '0') // walls not closed
                return (pr_err(INV_WALLS), EXIT_FAILURE);
            x++;
        }
        y++;
    }
    return (EXIT_SUCCESS);
}

int check_vert_top(t_meta *meta, char *map)
{
	uint32_t x;
	uint32_t y;
	bool closed;

    x = 0;
    closed = false;
    while (x < meta->map.width)
    {
        closed = false;
        y = 0;
        while (y < meta->map.height)
        {
            if (map[find_index(meta, y, x)] == '1')
                closed = 1;
            if (!closed && map[find_index(meta, y, x)] == '0') // walls not closed
                return (pr_err(INV_WALLS), EXIT_FAILURE);
            y++;
        }
        x++;
    }
    return (EXIT_SUCCESS);
}

int check_horiz_right(t_meta *meta, char *map)
{
    uint32_t    x;
    uint32_t    y;
    bool        closed;

    y = meta->map.height;
    while (--y > 0)
    {
        closed = false;
        x = meta->map.width;
        while (--x > 0)
        {
            if (map[find_index(meta, y, x)] == '1')
                closed = true;
            if (!closed && map[find_index(meta, y, x)] == '0') // walls not closed
                return (pr_err(INV_WALLS), EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}

int check_vert_down(t_meta *meta, char *map)
{
    uint32_t    x;
    uint32_t    y;
    bool        closed;

    x = meta->map.width;
    while (--x > 0)
    {
        closed = false;
        y = meta->map.height;
        while (--y > 0)
        {
            if (map[find_index(meta, y, x)] == '1')
                closed = true;
            if (!closed && map[find_index(meta, y, x)] == '0') // walls not closed
                return (pr_err(INV_WALLS), EXIT_FAILURE);
        }
    }
    return (EXIT_SUCCESS);
}
