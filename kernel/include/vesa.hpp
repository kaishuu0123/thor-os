//=======================================================================
// Copyright Baptiste Wicht 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef VESA_H
#define VESA_H

#include <types.hpp>

namespace vesa {

struct vbe_info_block_t {
    char signature[4];             //"VESA"
    uint16_t version;              // == 0x0300 for VBE 3.0
    uint16_t oem_name_ptr[2];
    uint8_t capabilities[4];
    uint16_t video_modes_ptr[2];
    uint16_t total_memory;         // as # of 64KB blocks

    //VBE 2.0
    uint16_t oem_software_version;
    uint16_t vendor_name_ptr[2];
    uint16_t product_name_ptr[2];
    uint16_t product_revision_ptr[2];
    uint16_t vbe_af_version;
    uint16_t accelerator_video_modes_ptr[2];

    uint8_t reserved[216];
    uint8_t oem_scratchpad[256];
} __attribute__((packed));

static_assert(sizeof(vbe_info_block_t) == 512, "The size of a VBE info block is 512 bytes");

struct mode_info_block_t {
    uint16_t mode_attributes;
    uint8_t window_a_attributes;
    uint8_t window_b_attributes;
    uint16_t window_granularity;
    uint16_t window_size;
    uint16_t segment_window_a;
    uint16_t segment_window_b;
    uint16_t window_position_function[2];
    uint16_t pitch; //Bytes per scan line

    //OEM modes

    uint16_t width;
    uint16_t height;
    uint8_t width_char;
    uint8_t height_char;
    uint8_t memory_planes;
    uint8_t bpp;
    uint8_t banks;
    uint8_t memory_model;
    uint8_t bank_size;
    uint8_t image_pages;
    uint8_t reserved;

    //VBE 1.2+

    uint8_t red_mask_size;
    uint8_t red_mask_position;
    uint8_t green_mask_size;
    uint8_t green_mask_position;
    uint8_t blue_mask_size;
    uint8_t blue_mask_position;
    uint8_t reserved_mask_size;
    uint8_t reserved__mask_position;
    uint8_t directcolor_attributes;

    //VBE 2.0+

    uint32_t linear_video_buffer;         //LFB (Linear Framebuffer) address
    uint16_t offscreen_memory[2];
    uint16_t offscreen_memory_size;

    uint16_t bytes_per_scan_line;
    uint8_t number_of_images_banked;
    uint8_t number_of_images_linear;
    uint8_t linear_red_mask_size;
    uint8_t linear_red_mask_position;
    uint8_t linear_green_mask_size;
    uint8_t linear_green_mask_position;
    uint8_t linear_blue_mask_size;
    uint8_t linear_blue_mask_position;
    uint8_t linear_reserved_mask_size;
    uint8_t linear_reserved_mask_position;
    uint32_t maximum_pixel_clock;
    uint8_t reserved_2[190];
} __attribute__((packed));

static_assert(sizeof(mode_info_block_t) == 256, "The size of a mode info block is 256 bytes");

extern vbe_info_block_t vbe_info_block;
extern bool vesa_enabled;
extern mode_info_block_t mode_info_block;

bool init();

uint32_t make_color(uint8_t r, uint8_t g, uint8_t b);

void draw_pixel(size_t x, size_t y, uint32_t color);
void draw_pixel(size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b);

void draw_hline(size_t x, size_t y, size_t w, uint8_t r, uint8_t g, uint8_t b);
void draw_hline(size_t x, size_t y, size_t w, uint32_t color);

void draw_vline(size_t x, size_t y, size_t h, uint32_t color);
void draw_vline(size_t x, size_t y, size_t h, uint8_t r, uint8_t g, uint8_t b);

void draw_rect(size_t x, size_t y, size_t w, size_t h, uint32_t color);
void draw_rect(size_t x, size_t y, size_t w, size_t h, uint8_t r, uint8_t g, uint8_t b);

void draw_char(size_t x, size_t y, char c, uint32_t color);
void draw_char(size_t x, size_t y, char c, uint8_t r, uint8_t g, uint8_t b);

void move_lines_up(size_t y, size_t x, size_t w, size_t lines, size_t n);

} //end of vesa namespace

#endif
