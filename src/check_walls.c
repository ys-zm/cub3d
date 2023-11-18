#include "meta.h"

// returns 1 if walls are not closed
int check_horiz_left(t_meta *meta, char *map)
{
    int closed = 0;
    int x;
    int y;

    y = -1;
    while (++y < (int)meta->map.height)
    {
        closed = 0;
        x = -1;
        while (++x < (int)meta->map.width)
        {
            // printf("c: %c\n", map[find_index(meta, y, x)]);
            if (map[find_index(meta, y, x)] == '1')
                closed = 1;
            if (!closed && map[find_index(meta, y, x)] == '0') // walls not closed
                return (pr_err(INV_WALLS));
        }
    }
    return (0);
}

int check_vert_top(t_meta *meta, char *map)
{
    int closed = 0;
    int x;
    int y;

    x = -1;
    while (++x < (int)meta->map.width)
    {
        closed = 0;
        y = -1;
        while (++y < (int)meta->map.height)
        {
            if (map[find_index(meta, y, x)] == '1')
                closed = 1;
            if (!closed && map[find_index(meta, y, x)] == '0') // walls not closed
                return (pr_err(INV_WALLS));
        }
    }
    return (0);
}

int check_horiz_right(t_meta *meta, char *map)
{
    int closed = 0;
    uint32_t x;
    uint32_t y;

    y = meta->map.height;
    while (--y > 0)
    {
        closed = 0;
        x = meta->map.width;
        while (--x > 0)
        {
            if (map[find_index(meta, y, x)] == '1')
                closed = 1;
            if (!closed && map[find_index(meta, y, x)] == '0') // walls not closed
                return (pr_err(INV_WALLS));
        }
    }
    return (0);
}

int check_vert_down(t_meta *meta, char *map)
{
    int closed = 0;
    uint32_t x;
    uint32_t y;

    x = meta->map.width;
    while (--x > 0)
    {
        closed = 0;
        y = meta->map.height;
        while (--y > 0)
        {
            if (map[find_index(meta, y, x)] == '1')
                closed = 1;
            if (!closed && map[find_index(meta, y, x)] == '0') // walls not closed
                return (pr_err(INV_WALLS));
        }
    }
    return (0);
}