#ifndef ENGINE3D_MAIN_H
#define ENGINE3D_MAIN_H

extern const int engine3D_width;
extern const int engine3D_height;
extern const char *const engine3D_title;
extern const double engine3D_frameCap;
extern int engine3D_fps;

typedef void(*game_callback_t)(void);

void engine3D_init(void);

void engine3D_start(void);

void engine3D_stop(void);

void engine3D_setGame_init(const game_callback_t fun);

void engine3D_setGame_input(const game_callback_t fun);

void engine3D_setGame_update(const game_callback_t fun);

void engine3D_setGame_render(const game_callback_t fun);

void engine3D_setGame_cleanup(const game_callback_t fun);

#endif /* ENGINE3D_MAIN_H */
