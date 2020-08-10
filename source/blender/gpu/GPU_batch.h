/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2016 by Mike Erwin.
 * All rights reserved.
 */

/** \file
 * \ingroup gpu
 *
 * GPU geometry batch
 * Contains VAOs + VBOs + Shader representing a drawable entity.
 */

#pragma once

#include "BLI_utildefines.h"

#include "GPU_element.h"
#include "GPU_shader.h"
#include "GPU_vertex_buffer.h"

#define GPU_BATCH_VBO_MAX_LEN 6
#define GPU_BATCH_INST_VBO_MAX_LEN 2
#define GPU_BATCH_VAO_STATIC_LEN 3
#define GPU_BATCH_VAO_DYN_ALLOC_COUNT 16

typedef enum eGPUBatchFlag {
  /** Invalid default state. */
  GPU_BATCH_INVALID = 0,

  /** GPUVertBuf ownership. (One bit per vbo) */
  GPU_BATCH_OWNS_VBO = (1 << 0),
  GPU_BATCH_OWNS_VBO_MAX = (GPU_BATCH_OWNS_VBO << (GPU_BATCH_VBO_MAX_LEN - 1)),
  GPU_BATCH_OWNS_VBO_ANY = ((GPU_BATCH_OWNS_VBO << GPU_BATCH_VBO_MAX_LEN) - 1),
  /** Instance GPUVertBuf ownership. (One bit per vbo) */
  GPU_BATCH_OWNS_INST_VBO = (GPU_BATCH_OWNS_VBO_MAX << 1),
  GPU_BATCH_OWNS_INST_VBO_MAX = (GPU_BATCH_OWNS_INST_VBO << (GPU_BATCH_INST_VBO_MAX_LEN - 1)),
  GPU_BATCH_OWNS_INST_VBO_ANY = ((GPU_BATCH_OWNS_INST_VBO << GPU_BATCH_INST_VBO_MAX_LEN) - 1) &
                                ~GPU_BATCH_OWNS_VBO_ANY,
  /** GPUIndexBuf ownership. */
  GPU_BATCH_OWNS_INDEX = (GPU_BATCH_OWNS_INST_VBO_MAX << 1),

  /** Has been initialized. At least one VBO is set. */
  GPU_BATCH_INIT = (1 << 16),
  /** Batch is initialized but it's VBOs are still being populated. (optional) */
  GPU_BATCH_BUILDING = (1 << 16),
  /** Cached data need to be rebuild. (VAO, PSO, ...) */
  GPU_BATCH_DIRTY = (1 << 17),
} eGPUBatchFlag;

#define GPU_BATCH_OWNS_NONE GPU_BATCH_INVALID

BLI_STATIC_ASSERT(GPU_BATCH_OWNS_INDEX < GPU_BATCH_INIT,
                  "eGPUBatchFlag: Error: status flags are shadowed by the ownership bits!")

ENUM_OPERATORS(eGPUBatchFlag)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * IMPORTANT: Do not allocate manually as the real struct is bigger (i.e: GLBatch). This is only
 * the common and "public" part of the struct. Use the provided allocator.
 * TODO(fclem) Make the content of this struct hidden and expose getters/setters.
 **/
typedef struct GPUBatch {
  /** verts[0] is required, others can be NULL */
  GPUVertBuf *verts[GPU_BATCH_VBO_MAX_LEN];
  /** Instance attributes. */
  GPUVertBuf *inst[GPU_BATCH_INST_VBO_MAX_LEN];
  /** NULL if element list not needed */
  GPUIndexBuf *elem;
  /** Bookeeping. */
  eGPUBatchFlag flag;
  /** Type of geometry to draw. */
  GPUPrimType prim_type;
  /** Current assigned shader. DEPRECATED. Here only for uniform binding. */
  struct GPUShader *shader;
} GPUBatch;

GPUBatch *GPU_batch_calloc(void);
GPUBatch *GPU_batch_create_ex(GPUPrimType prim,
                              GPUVertBuf *vert,
                              GPUIndexBuf *elem,
                              eGPUBatchFlag own_flag);
void GPU_batch_init_ex(GPUBatch *batch,
                       GPUPrimType prim,
                       GPUVertBuf *vert,
                       GPUIndexBuf *elem,
                       eGPUBatchFlag own_flag);
void GPU_batch_copy(GPUBatch *batch_dst, GPUBatch *batch_src);

#define GPU_batch_create(prim, verts, elem) GPU_batch_create_ex(prim, verts, elem, 0)
#define GPU_batch_init(batch, prim, verts, elem) GPU_batch_init_ex(batch, prim, verts, elem, 0)

/* Same as discard but does not free. (does not call free callback). */
void GPU_batch_clear(GPUBatch *);

void GPU_batch_discard(GPUBatch *); /* verts & elem are not discarded */

void GPU_batch_vao_cache_clear(GPUBatch *);

void GPU_batch_instbuf_set(GPUBatch *, GPUVertBuf *, bool own_vbo); /* Instancing */
void GPU_batch_elembuf_set(GPUBatch *batch, GPUIndexBuf *elem, bool own_ibo);

int GPU_batch_instbuf_add_ex(GPUBatch *, GPUVertBuf *, bool own_vbo);
int GPU_batch_vertbuf_add_ex(GPUBatch *, GPUVertBuf *, bool own_vbo);

#define GPU_batch_vertbuf_add(batch, verts) GPU_batch_vertbuf_add_ex(batch, verts, false)

void GPU_batch_set_shader(GPUBatch *batch, GPUShader *shader);
void GPU_batch_program_set_imm_shader(GPUBatch *batch);
void GPU_batch_program_set_builtin(GPUBatch *batch, eGPUBuiltinShader shader_id);
void GPU_batch_program_set_builtin_with_config(GPUBatch *batch,
                                               eGPUBuiltinShader shader_id,
                                               eGPUShaderConfig sh_cfg);

/* Will only work after setting the batch program. */
void GPU_batch_uniform_1i(GPUBatch *, const char *name, int value);
void GPU_batch_uniform_1b(GPUBatch *, const char *name, bool value);
void GPU_batch_uniform_1f(GPUBatch *, const char *name, float value);
void GPU_batch_uniform_2f(GPUBatch *, const char *name, float x, float y);
void GPU_batch_uniform_3f(GPUBatch *, const char *name, float x, float y, float z);
void GPU_batch_uniform_4f(GPUBatch *, const char *name, float x, float y, float z, float w);
void GPU_batch_uniform_2fv(GPUBatch *, const char *name, const float data[2]);
void GPU_batch_uniform_3fv(GPUBatch *, const char *name, const float data[3]);
void GPU_batch_uniform_4fv(GPUBatch *, const char *name, const float data[4]);
void GPU_batch_uniform_2fv_array(GPUBatch *, const char *name, const int len, const float *data);
void GPU_batch_uniform_4fv_array(GPUBatch *, const char *name, const int len, const float *data);
void GPU_batch_uniform_mat4(GPUBatch *, const char *name, const float data[4][4]);

void GPU_batch_draw(GPUBatch *batch);
void GPU_batch_draw_range(GPUBatch *batch, int v_first, int v_count);
void GPU_batch_draw_instanced(GPUBatch *batch, int i_count);

/* This does not bind/unbind shader and does not call GPU_matrix_bind() */
void GPU_batch_draw_advanced(GPUBatch *, int v_first, int v_count, int i_first, int i_count);

/* Does not even need batch */
void GPU_draw_primitive(GPUPrimType, int v_count);

#if 0 /* future plans */

/* Can multiple batches share a GPUVertBuf? Use ref count? */

/* We often need a batch with its own data, to be created and discarded together. */
/* WithOwn variants reduce number of system allocations. */

typedef struct BatchWithOwnVertexBuffer {
  GPUBatch batch;
  GPUVertBuf verts; /* link batch.verts to this */
} BatchWithOwnVertexBuffer;

typedef struct BatchWithOwnElementList {
  GPUBatch batch;
  GPUIndexBuf elem; /* link batch.elem to this */
} BatchWithOwnElementList;

typedef struct BatchWithOwnVertexBufferAndElementList {
  GPUBatch batch;
  GPUIndexBuf elem; /* link batch.elem to this */
  GPUVertBuf verts; /* link batch.verts to this */
} BatchWithOwnVertexBufferAndElementList;

GPUBatch *create_BatchWithOwnVertexBuffer(GPUPrimType, GPUVertFormat *, uint v_len, GPUIndexBuf *);
GPUBatch *create_BatchWithOwnElementList(GPUPrimType, GPUVertBuf *, uint prim_len);
GPUBatch *create_BatchWithOwnVertexBufferAndElementList(GPUPrimType,
                                                        GPUVertFormat *,
                                                        uint v_len,
                                                        uint prim_len);
/* verts: shared, own */
/* elem: none, shared, own */
GPUBatch *create_BatchInGeneral(GPUPrimType, VertexBufferStuff, ElementListStuff);

#endif /* future plans */

void gpu_batch_init(void);
void gpu_batch_exit(void);

/* Macros */

#define GPU_BATCH_DISCARD_SAFE(batch) \
  do { \
    if (batch != NULL) { \
      GPU_batch_discard(batch); \
      batch = NULL; \
    } \
  } while (0)

#define GPU_BATCH_CLEAR_SAFE(batch) \
  do { \
    if (batch != NULL) { \
      GPU_batch_clear(batch); \
      memset(batch, 0, sizeof(*(batch))); \
    } \
  } while (0)

#define GPU_BATCH_DISCARD_ARRAY_SAFE(_batch_array, _len) \
  do { \
    if (_batch_array != NULL) { \
      BLI_assert(_len > 0); \
      for (int _i = 0; _i < _len; _i++) { \
        GPU_BATCH_DISCARD_SAFE(_batch_array[_i]); \
      } \
      MEM_freeN(_batch_array); \
    } \
  } while (0)

#ifdef __cplusplus
}
#endif
