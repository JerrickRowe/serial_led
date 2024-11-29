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

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public macros --------------------------------------------------------------*/
#define RGB(r, g, b) ((uint32_t)(r) << 16 | (uint32_t)(r) << 8 | (uint32_t)(r) << 0)

#define RGB_WHITE  RGB(255, 255, 255)
#define RGB_RED	   RGB(255, 0, 0)
#define RGB_GREEN  RGB(0, 255, 0)
#define RGB_BLUE   RGB(0, 0, 255)
#define RGB_YELLOW RGB(255, 255, 0)
#define RGB_CYAN   RGB(0, 255, 255)
#define RGB_PURPLE RGB(255, 0, 255)
#define RGB_OFF	   RGB(0, 0, 0)

/*--- Public type definitions ----------------------------------------------------*/

typedef struct pixel* pixel_t;

typedef int (*pixel_flush_t)(pixel_t pixel, uint8_t* data, size_t nbytes);

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

#ifdef __cplusplus
}
#endif

#endif  // __PIXEL_H__
