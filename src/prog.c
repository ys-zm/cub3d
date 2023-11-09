#include "enemy.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef void enemy;

enemy_t *enemy_init(const char *name);
void enemy_die(void *ptr);


//int main()
//{
//    enemy *e = enemy_init("sjon");
//    enemy_die(e);
//}
