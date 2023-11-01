typedef struct enemy_s {
    bool (*func)(t_renderer *);
    int health;
    char *name;
} enemy_t;

typedef struct enemy_s {
    bool (*func)(t_renderer *);
    int health;
    char *name;
} enemy_t;

void enemy_render()


typedef render_func bool (*func)(t_renderer *);


typedef struct meta_s {
    void *gameObjs[];


} meta_t;


void render(void *objs)
{

    render_func func;
    while (i < objs_size)
    {
        func = (render_func *) objs[i];
        func();
    }
    

}

main struct
    - args
    - options
        - controls
        - 
    - map_list
        - map
            - colorinfo
            - img_list
            - actual map ()
    - player 
        - pos
            - x
            - y
        - view direction
        - fov