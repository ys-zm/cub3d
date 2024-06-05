#include "meta.h"

static uint32_t	idx(uint32_t x, uint32_t y, uint32_t w)
{
	return ((y * w + x) * 4);
}

static uint8_t new_val(uint8_t pix_val, uint8_t threshold)
{
	if (pix_val > threshold)
		return (255);
	return (0);
}

void halftone_img(mlx_image_t *image)
{
	// Define the Bayer matrix (4x4)
	uint8_t bayerMatrix[4][4] = {
    	{ 0,  8,  2, 10},
    	{12,  4, 14,  6},
    	{ 3, 11,  1,  9},
    	{15,  7, 13,  5}
	};

	for (uint32_t y = 0; y < image->height; y++)
	{
		for (uint32_t x = 0; x < image->width; x++)
		{
			uint32_t index = idx(x, y, image->width);
			uint8_t r = image->pixels[index];
			uint8_t g = image->pixels[index + 1];
			uint8_t b = image->pixels[index + 2];

			uint8_t threshold = bayerMatrix[y % 4][x % 4] * 16;
			uint32_t new_r = new_val(r, threshold);
			uint32_t new_g = new_val(g, threshold);
			uint32_t new_b = new_val(b, threshold);

			image->pixels[index] = new_r;
            image->pixels[index + 1] = new_g;
            image->pixels[index + 2] = new_b;
		}
	}
}


