#include "enemy.h"
#include <unistd.h>
#include <stdlib.h>

enemy_t *enemy_init(const char *name)
{
    enemy_t *e = malloc(sizeof(enemy_t));
    bzero(e);
    e->name = name;
    return e;
}

void enemy_die(void *ptr)
{
    enemy_t *e = ptr;
    e->health= 0;

}