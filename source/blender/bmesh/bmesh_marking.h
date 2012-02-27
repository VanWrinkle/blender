/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
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
 * Contributor(s): Joseph Eagar.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#ifndef __BMESH_MARKING_H__
#define __BMESH_MARKING_H__

/** \file blender/bmesh/bmesh_marking.h
 *  \ingroup bmesh
 */

typedef struct BMEditSelection
{
	struct BMEditSelection *next, *prev;
	BMElem *ele;
	char htype;
} BMEditSelection;

/* geometry hiding code */
void BM_elem_hide_set(BMesh *bm, void *element, int hide);
void BM_vert_hide_set(BMesh *bm, BMVert *v, int hide);
void BM_edge_hide_set(BMesh *bm, BMEdge *e, int hide);
void BM_face_hide_set(BMesh *bm, BMFace *f, int hide);

/* Selection code */
void BM_elem_select_set(BMesh *bm, void *element, int select);

/* use BM_elem_flag_test(ele, BM_ELEM_SELECT) to test selection */

void BM_mesh_elem_flag_enable_all(BMesh *bm, const char htype, const char hflag);
void BM_mesh_elem_flag_disable_all(BMesh *bm, const char htype, const char hflag);

/* individual element select functions, BM_elem_select_set is a shortcut for these
 * that automatically detects which one to use*/
void BM_vert_select_set(BMesh *bm, BMVert *v, int select);
void BM_edge_select_set(BMesh *bm, BMEdge *e, int select);
void BM_face_select_set(BMesh *bm, BMFace *f, int select);

void BM_select_mode_set(BMesh *bm, int selectmode);

/* counts number of elements with flag set */
int BM_mesh_count_flag(BMesh *bm, const char htype, const char hflag, int respecthide);

/* edit selection stuff */
void    BM_active_face_set(BMesh *em, BMFace *f);
BMFace *BM_active_face_get(BMesh *bm, int sloppy);
void BM_editselection_center(BMesh *bm, float r_center[3], BMEditSelection *ese);
void BM_editselection_normal(float r_normal[3], BMEditSelection *ese);
void BM_editselection_plane(BMesh *bm, float r_plane[3], BMEditSelection *ese);

int  BM_select_history_check(BMesh *bm, const BMElem *ele);
void BM_select_history_remove(BMesh *bm, BMElem *ele);
void BM_select_history_store(BMesh *bm, BMElem *ele);
void BM_select_history_validate(BMesh *bm);
void BM_select_history_clear(BMesh *em);

#endif /* __BMESH_MARKING_H__ */
