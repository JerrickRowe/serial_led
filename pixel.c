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
#include "pixel.h"

#include <stdlib.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public variable definitions ------------------------------------------------*/

/*--- Private macros -------------------------------------------------------------*/
#define PIXEL_GROUP_MAGIC_NUMBER ((uint32_t)0x78e1564du)

#define CALLOC(n, size) calloc((n), (size))
// #define REALLOC(p, new_size) realloc((p), (new_size))
#define FREE(p)	  free(p)
#define ASSERT(e) assert(e)

/*--- Private type definitions ---------------------------------------------------*/

struct pixel_list {
	struct pixel_list* next;
	pixel_t			   pixel;
};
typedef struct pixel_list pixel_list_s, *pixel_list_t;

struct pixel_group {
	pixel_list_t pixel_list;
	uint32_t*	 color_buffer;
	size_t		 color_buffer_size;
};
typedef struct pixel_group pixel_group_s, *pixel_group_t;

struct pixel {
	const char*	  name;
	uint32_t	  color;
	uint32_t	  color_next;
	pixel_flush_t flush;
	void*		  user_data;
	pixel_group_t group;
};
typedef struct pixel pixel_s;

/*--- Private variable definitions -----------------------------------------------*/

/*--- Private function declarations ----------------------------------------------*/

/*--- Private function definitions -----------------------------------------------*/

/*--- Public function definitions ------------------------------------------------*/
pixel_t pixel_new(const char* name, pixel_flush_t flush_function, void* user_data) {
	pixel_t ret = (pixel_t)CALLOC(1, sizeof(struct pixel));
	ASSERT(ret != NULL);
	ret->name		= name;
	ret->flush		= flush_function;
	ret->user_data	= user_data;
	ret->color		= RGB_OFF;
	ret->color_next = RGB_OFF;
	ret->group		= NULL;
	return ret;
}

pixel_t pixel_group_new(const char* name, pixel_flush_t flush_function, void* user_data) {
	pixel_t ret = (pixel_t)CALLOC(1, sizeof(struct pixel));
	ASSERT(ret != NULL);
	ret->name		= name;
	ret->flush		= flush_function;
	ret->user_data	= user_data;
	ret->color		= RGB_OFF;
	ret->color_next = RGB_OFF;
	ret->group		= (pixel_group_t)CALLOC(1, sizeof(struct pixel_group));
	ASSERT(ret->group != NULL);
	return (pixel_t)ret;
}

int pixel_group_join(pixel_t pixel, pixel_t sub_pixel) {
	pixel_group_t group = pixel->group;
	ASSERT(group != NULL);	// This pixel is not a group
	uint32_t	  pixel_count = 0;
	pixel_list_t* p			  = &group->pixel_list;
	while(*p) {
		pixel_count++;
		p = &(*p)->next;
	}
	pixel_list_t new_node = (pixel_list_t)CALLOC(1, sizeof(struct pixel_list));
	ASSERT(new_node);
	new_node->pixel = sub_pixel;
	*p				= new_node;
	pixel_count++;
	if(group->color_buffer != NULL) {
		FREE(group->color_buffer);
	}
	group->color_buffer_size = pixel_count * sizeof(uint32_t);
	group->color_buffer		 = CALLOC(1, group->color_buffer_size);
	ASSERT(group->color_buffer != NULL);
	return 0;
}

int pixel_color_set(pixel_t pixel, uint32_t color) {
	ASSERT(pixel);
	pixel->color_next = color;
	if(pixel->group == NULL) {
		return 0;
	}
	pixel_group_t group = pixel->group;
	pixel_list_t* p		= &group->pixel_list;
	while(*p) {
		pixel_t sub_pixel	  = (*p)->pixel;
		sub_pixel->color_next = color;

		p = &(*p)->next;
	}
	return 0;
}

int pixel_flush(pixel_t pixel) {
	pixel_flush_t flush = pixel->flush;
	pixel_group_t group = pixel->group;
	if(group != NULL) {
		uint32_t pixel_changed_num = 0;
		uint32_t pixel_count	   = 0;

		pixel_list_t* p = &group->pixel_list;
		while(*p) {
			pixel_t sub_pixel = (*p)->pixel;
			pixel_changed_num += (sub_pixel->color != sub_pixel->color_next);
			sub_pixel->color				 = sub_pixel->color_next;
			group->color_buffer[pixel_count] = sub_pixel->color;
			pixel_count++;
			p = &(*p)->next;
		}

		if(flush != NULL && pixel_changed_num != 0) {
			flush(pixel, group->color_buffer, pixel_count);
		}
	}
	if(pixel->color != pixel->color_next) {
		pixel->color = pixel->color_next;
		if(flush != NULL) {
			flush(pixel, &pixel->color_next, 1);
		}
	}
}

#ifdef __cplusplus
}
#endif
