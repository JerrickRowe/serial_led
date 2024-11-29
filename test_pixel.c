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

/*--- Private dependencies -------------------------------------------------------*/
#include "test_pixel.h"

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public variable definitions ------------------------------------------------*/

/*--- Private macros -------------------------------------------------------------*/

/*--- Private type definitions ---------------------------------------------------*/

/*--- Private variable definitions -----------------------------------------------*/

/*--- Private function declarations ----------------------------------------------*/

/*--- Private function definitions -----------------------------------------------*/
static int simulated_flush(void* contex, uint32_t* color, size_t n_pixels) {
    FILE* fp = (FILE*)contex;
    for(int i=0; i<n_pixels; i++){
		uint32_t output = COLOR_SWAP_ARGB(*color);
        fprintf(fp, "0x08X, ", output);
    }
    fprintf(fp, "\r\n");
	return 0;
}

/*--- Public function definitions ------------------------------------------------*/
int test_pixel_interface(void) {
	pixel_t pixel[4];
	pixel_t ws2812;
	pixel_t button1_bl;
	pixel_t button2_bl;
    
	pixel[0] = pixel_new("U28", NULL, NULL);
	pixel[1] = pixel_new("U22", NULL, NULL);
	pixel[2] = pixel_new("U12", NULL, NULL);
	pixel[3] = pixel_new("U59", NULL, NULL);

	ws2812	 = pixel_group_new("ws2812", simulated_flush, stdout);
	pixel_group_join(ws2812, pixel[0]);
	pixel_group_join(ws2812, pixel[1]);
	pixel_group_join(ws2812, pixel[2]);
	pixel_group_join(ws2812, pixel[3]);

	button1_bl = pixel_group_new("button1", NULL, NULL);
	pixel_group_join(button1_bl, pixel[0]);
	pixel_group_join(button1_bl, pixel[2]);

	button2_bl = pixel_group_new("button2", NULL, NULL);
	pixel_group_join(button2_bl, pixel[1]);
	pixel_group_join(button2_bl, pixel[3]);

    pixel_color_set(ws2812, RGB_OFF);
    pixel_flush(ws2812);
    
    pixel_color_set(button1_bl, RGB_RED);
    pixel_flush(ws2812);
    pixel_color_set(button1_bl, RGB_GREEN);
    pixel_flush(ws2812);
    pixel_color_set(button2_bl, RGB_BLUE);
    pixel_flush(ws2812);

    pixel_color_set(ws2812, RGB_OFF);
    pixel_flush(ws2812);
	return 0;
}

#ifdef __cplusplus
}
#endif
