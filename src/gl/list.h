#include "gl.h"

#ifndef DISPLAY_LIST_H
#define DISPLAY_LIST_H

typedef enum {
	STAGE_NONE = 0,
	STAGE_PUSH,
	STAGE_POP,
	STAGE_CALLLIST,
	STAGE_GLCALL,
	STAGE_BINDTEX,
	STAGE_RASTER,
	STAGE_MATERIAL,
	STAGE_LIGHT,
	STAGE_LIGHTMODEL,
	STAGE_TEXGEN,
	STAGE_POLYGON,
	STAGE_DRAW,
	STAGE_LAST
} liststage_t;

static int StageExclusive[STAGE_LAST] = {
	0, 	// STAGE_NONE
	1,	// STAGE_PUSH
	1,  // STAGE_POP
	1, 	// STAGE_CALLLIST
	0,  // STAGE_GLCALL
	1,  // STAGE_BINDTEX
	1,  // STAGE_RASTER
	0,  // STAGE_MATERIAL
	0,  // STAGE_LIGHT
	1,  // STAGE_LIGTMODEL
	0,  // STAGE_TEXGEN
	1,  // STAGE_POLYGON
	1   // STAGE_DRAW
};

typedef struct {
    int face;
    int pname;
    GLfloat color[4];
    int count;
} rendermaterial_t;

typedef struct {
    int which;
    int pname;
    GLfloat color[4];
    int count;
} renderlight_t;

typedef struct {
    int coord;
    int pname;
    GLfloat color[4];
    int count;
} rendertexgen_t;

typedef struct {
	GLfloat	xmove;
	GLfloat ymove;
	GLsizei width;
	GLsizei height;
	GLfloat xorig;
	GLfloat yorig;
	GLfloat zoomx;
	GLfloat zoomy;
	GLboolean bitmap;
	GLuint	texture;
} rasterlist_t;

KHASH_MAP_INIT_INT(material, rendermaterial_t *)
KHASH_MAP_INIT_INT(light, renderlight_t *)
KHASH_MAP_INIT_INT(texgen, rendertexgen_t *)

typedef struct _call_list_t {
    unsigned long len;
    unsigned long cap;
    packed_call_t **calls;
} call_list_t;

typedef struct _renderlist_t {
    unsigned long len;
    unsigned long cap;
    GLenum mode;
    GLenum mode_init;		// initial requested mode
    GLfloat lastNormal[3];

    call_list_t calls;
    GLfloat *vert;
    GLfloat *normal;
    GLfloat *color;
    GLfloat *secondary;
    GLfloat *tex[MAX_TEX];
    GLushort *indices;
    GLboolean q2t;
	
	GLuint	glcall_list;
	rasterlist_t *raster;
	
	liststage_t	stage;
	
	GLbitfield pushattribute;
	GLboolean  popattribute;
    
    khash_t(material) *material;
    khash_t(light) *light;
    khash_t(texgen) *texgen;
    GLfloat	*lightmodel;
    GLenum	lightmodelparam;
    GLenum	polygon_mode;
    GLuint texture;				// I cannot know the active texture inside a list (for now => TODO?)
    GLboolean  set_texture;
    struct _renderlist_t *prev;
    struct _renderlist_t *next;
    GLboolean open;
} renderlist_t;

#define DEFAULT_CALL_LIST_CAPACITY 20
#define DEFAULT_RENDER_LIST_CAPACITY 20

#define NewStage(l, s) if (l->stage+StageExclusive[s] > s) {l = extend_renderlist(l);} l->stage = s

extern renderlist_t *alloc_renderlist();
extern renderlist_t *extend_renderlist(renderlist_t *list);
extern void free_renderlist(renderlist_t *list);
extern void draw_renderlist(renderlist_t *list);
extern void q2t_renderlist(renderlist_t *list);
extern void end_renderlist(renderlist_t *list);

extern void rlBindTexture(renderlist_t *list, GLuint texture);
extern void rlColor4f(renderlist_t *list, GLfloat r, GLfloat g, GLfloat b, GLfloat a);
extern void rlMaterialfv(renderlist_t *list, GLenum face, GLenum pname, const GLfloat * params);
extern void rlLightfv(renderlist_t *list, GLenum which, GLenum pname, const GLfloat * params);
extern void rlTexGenfv(renderlist_t *list, GLenum coord, GLenum pname, const GLfloat * params);
extern void rlNormal3f(renderlist_t *list, GLfloat x, GLfloat y, GLfloat z);
extern void rlPushCall(renderlist_t *list, packed_call_t *data);
extern void rlTexCoord2f(renderlist_t *list, GLfloat s, GLfloat t);
extern void rlMultiTexCoord2f(renderlist_t *list, GLenum texture, GLfloat s, GLfloat t);
extern void rlVertex3f(renderlist_t *list, GLfloat x, GLfloat y, GLfloat z);
extern void rlSecondary3f(renderlist_t *list, GLfloat r, GLfloat g, GLfloat b);
#endif
