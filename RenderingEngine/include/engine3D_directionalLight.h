#ifndef ENGINE3D_DIRECTIONALLIGHT
#define ENGINE3D_DIRECTIONALLIGHT

typedef struct engine3D_directionalLight_t {
	engine3D_baseLight_t base;
	engine3D_vector3f_t direction;
} engine3D_directionalLight_t;

#endif /* ENGINE3D_DIRECTIONALLIGHT */
