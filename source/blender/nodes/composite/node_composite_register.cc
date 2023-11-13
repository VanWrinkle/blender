/* SPDX-FileCopyrightText: 2023 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

#include "NOD_register.hh"

#include "node_composite_register.hh"

void register_composite_nodes()
{
  register_node_tree_type_cmp();

  register_node_type_cmp_group();

  register_node_type_cmp_alphaover();
  register_node_type_cmp_antialiasing();
  register_node_type_cmp_bilateralblur();
  register_node_type_cmp_blur();
  register_node_type_cmp_bokehblur();
  register_node_type_cmp_bokehimage();
  register_node_type_cmp_boxmask();
  register_node_type_cmp_brightcontrast();
  register_node_type_cmp_channel_matte();
  register_node_type_cmp_chroma_matte();
  register_node_type_cmp_color_matte();
  register_node_type_cmp_color_spill();
  register_node_type_cmp_colorbalance();
  register_node_type_cmp_colorcorrection();
  register_node_type_cmp_combhsva();
  register_node_type_cmp_combine_color();
  register_node_type_cmp_combine_xyz();
  register_node_type_cmp_combrgba();
  register_node_type_cmp_combycca();
  register_node_type_cmp_combyuva();
  register_node_type_cmp_composite();
  register_node_type_cmp_convert_color_space();
  register_node_type_cmp_cornerpin();
  register_node_type_cmp_crop();
  register_node_type_cmp_cryptomatte_legacy();
  register_node_type_cmp_cryptomatte();
  register_node_type_cmp_curve_rgb();
  register_node_type_cmp_curve_time();
  register_node_type_cmp_curve_vec();
  register_node_type_cmp_dblur();
  register_node_type_cmp_defocus();
  register_node_type_cmp_denoise();
  register_node_type_cmp_despeckle();
  register_node_type_cmp_diff_matte();
  register_node_type_cmp_dilateerode();
  register_node_type_cmp_displace();
  register_node_type_cmp_distance_matte();
  register_node_type_cmp_doubleedgemask();
  register_node_type_cmp_ellipsemask();
  register_node_type_cmp_exposure();
  register_node_type_cmp_filter();
  register_node_type_cmp_flip();
  register_node_type_cmp_gamma();
  register_node_type_cmp_glare();
  register_node_type_cmp_hue_sat();
  register_node_type_cmp_huecorrect();
  register_node_type_cmp_idmask();
  register_node_type_cmp_image();
  register_node_type_cmp_inpaint();
  register_node_type_cmp_invert();
  register_node_type_cmp_keying();
  register_node_type_cmp_keyingscreen();
  register_node_type_cmp_kuwahara();
  register_node_type_cmp_lensdist();
  register_node_type_cmp_luma_matte();
  register_node_type_cmp_map_range();
  register_node_type_cmp_map_value();
  register_node_type_cmp_mapuv();
  register_node_type_cmp_mask();
  register_node_type_cmp_math();
  register_node_type_cmp_mix_rgb();
  register_node_type_cmp_movieclip();
  register_node_type_cmp_moviedistortion();
  register_node_type_cmp_normal();
  register_node_type_cmp_normalize();
  register_node_type_cmp_output_file();
  register_node_type_cmp_pixelate();
  register_node_type_cmp_planetrackdeform();
  register_node_type_cmp_posterize();
  register_node_type_cmp_premulkey();
  register_node_type_cmp_rgb();
  register_node_type_cmp_rgbtobw();
  register_node_type_cmp_rlayers();
  register_node_type_cmp_rotate();
  register_node_type_cmp_scale();
  register_node_type_cmp_scene_time();
  register_node_type_cmp_separate_color();
  register_node_type_cmp_separate_xyz();
  register_node_type_cmp_sephsva();
  register_node_type_cmp_seprgba();
  register_node_type_cmp_sepycca();
  register_node_type_cmp_sepyuva();
  register_node_type_cmp_setalpha();
  register_node_type_cmp_splitviewer();
  register_node_type_cmp_stabilize2d();
  register_node_type_cmp_sunbeams();
  register_node_type_cmp_switch_view();
  register_node_type_cmp_switch();
  register_node_type_cmp_texture();
  register_node_type_cmp_tonemap();
  register_node_type_cmp_trackpos();
  register_node_type_cmp_transform();
  register_node_type_cmp_translate();
  register_node_type_cmp_valtorgb();
  register_node_type_cmp_value();
  register_node_type_cmp_vecblur();
  register_node_type_cmp_view_levels();
  register_node_type_cmp_viewer();
  register_node_type_cmp_zcombine();
}
