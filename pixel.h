/**********************************************************************************/
/* MIT License                                                                    */
/*                                                                                */
/* Copyright (c) [2024] [Jerrick.Rowe]                                            */
/*                                                                                */
/* Permission is hereby granted, free of charge, to any person obtaining a copy   */
/* of this software and associated documentation files (the "Software"), to deal  */
/* in the Software without restriction, including without limitation the rights   */
/* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      */
/* copies of the Software, and to permit persons to whom the Software is          */
/* furnished to do so, subject to the following conditions:                       */
/*                                                                                */
/* The above copyright notice and this permission notice shall be included in all */
/* copies or substantial portions of the Software.                                */
/*                                                                                */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  */
/* SOFTWARE.                                                                      */
/**********************************************************************************/

#ifndef __PIXEL_H__
#define __PIXEL_H__

/*--- Public dependencies --------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public macros --------------------------------------------------------------*/
#define ARGB(a, r, g, b) \
	((uint32_t)(r) << 24 | (uint32_t)(r) << 16 | (uint32_t)(g) << 8 | (uint32_t)(b) << 0)

#define RGB(r, g, b) ARGB(255, (r), (g), (b))

#define RGB_WHITE  RGB(255, 255, 255)
#define RGB_RED	   RGB(255, 0, 0)
#define RGB_GREEN  RGB(0, 255, 0)
#define RGB_BLUE   RGB(0, 0, 255)
#define RGB_YELLOW RGB(255, 255, 0)
#define RGB_CYAN   RGB(0, 255, 255)
#define RGB_PURPLE RGB(255, 0, 255)
#define RGB_OFF	   RGB(0, 0, 0)

// clang-format off
#define COLOR_SWAP_ARGB(color)  ( (((uint8_t*)&(color))[3] << (8*3)) \
                                | (((uint8_t*)&(color))[2] << (8*2)) \
                                | (((uint8_t*)&(color))[1] << (8*1)) \
                                | (((uint8_t*)&(color))[0] << (8*0)) )

#define COLOR_SWAP_ARBG(color)  ( (((uint8_t*)&(color))[3] << (8*3)) \
                                | (((uint8_t*)&(color))[2] << (8*2)) \
                                | (((uint8_t*)&(color))[1] << (8*0)) \
                                | (((uint8_t*)&(color))[0] << (8*1)) )

#define COLOR_SWAP_AGBR(color)  ( (((uint8_t*)&(color))[3] << (8*3)) \
                                | (((uint8_t*)&(color))[2] << (8*1)) \
                                | (((uint8_t*)&(color))[1] << (8*0)) \
                                | (((uint8_t*)&(color))[0] << (8*2)) )

#define COLOR_SWAP_AGRB(color)  ( (((uint8_t*)&(color))[3] << (8*3)) \
                                | (((uint8_t*)&(color))[2] << (8*1)) \
                                | (((uint8_t*)&(color))[1] << (8*2)) \
                                | (((uint8_t*)&(color))[0] << (8*0)) )

#define COLOR_SWAP_ABRG(color)  ( (((uint8_t*)&(color))[3] << (8*3)) \
                                | (((uint8_t*)&(color))[2] << (8*0)) \
                                | (((uint8_t*)&(color))[1] << (8*2)) \
                                | (((uint8_t*)&(color))[0] << (8*1)) )

#define COLOR_SWAP_ABGR(color)  ( (((uint8_t*)&(color))[3] << (8*3)) \
                                | (((uint8_t*)&(color))[2] << (8*0)) \
                                | (((uint8_t*)&(color))[1] << (8*1)) \
                                | (((uint8_t*)&(color))[0] << (8*2)) )
// clang-format on

/*--- Public type definitions ----------------------------------------------------*/

typedef struct pixel* pixel_t;

typedef int (*pixel_flush_t)(void* user_data, uint32_t* color, size_t n_pixels);

/*--- Public variable declarations -----------------------------------------------*/

/*--- Public function declarations -----------------------------------------------*/

/**
 * @brief
 */
extern pixel_t pixel_new(const char* name, pixel_flush_t flush_function, void* user_data);

/**
 * @brief
 */
extern pixel_t pixel_group_new(const char* name, pixel_flush_t flush_function, void* user_data);

/**
 * @brief
 */
extern int pixel_group_join(pixel_t pixel, pixel_t sub_pixel);

/**
 * @brief
 */
extern int pixel_color_set(pixel_t pixel, uint32_t color);

/**
 * @brief
 */
extern int pixel_flush(pixel_t pixel);

/**
 * @brief
 */
extern void pixel_port_init(void);

/**
 * @brief
 */
extern void pixel_port_poll(void);

/**
 * @brief
 */
extern void pixel_port_deinit(void);

#ifdef __cplusplus
}
#endif

#endif	// __PIXEL_H__
