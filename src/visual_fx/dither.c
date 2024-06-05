#include "meta.h"

static uint32_t	idx(uint32_t x, uint32_t y, uint32_t w)
{
	return ((y * w + x) * 4);
}

// Ditherig effect Floyd-Steinberg dithering
// Looping over the image row by row i.e. y loop first makes a different
void dither_img(mlx_image_t *image)
{

	for (uint32_t y = 0; y < image->height - 1; y++)
	{
		for (uint32_t x = 1; x < image->width - 1; x++)
		{
			uint32_t index = idx(x, y, image->width); // Find index relevant in image array storing pixel color info
			uint8_t r = image->pixels[index];
			uint8_t g = image->pixels[index + 1];
			uint8_t b = image->pixels[index + 2];

			int fc = 2;
			uint8_t new_r = round(fc * r / 255) * 255/fc; 
			uint8_t new_g = round(fc * g / 255) * 255/fc;
			uint8_t new_b = round(fc * b / 255) * 255/fc;
			// uint8_t new_g = round(((fc * g>>8)) * ((255>>1)));
			// uint8_t new_b = round(((fc * b>>8)) * ((255>>1)));
			// uint8_t new_r = round(((fc * r>>8)) * ((255>>1)));

			int32_t err_r = r - new_r;
			int32_t err_g = g - new_g;
			int32_t err_b = b - new_b;

			image->pixels[index] = new_r;
            image->pixels[index + 1] = new_g;
            image->pixels[index + 2] = new_b;

            // Distribute the quantization error to 4 neightbouring pixels in 7/16, 1/16, 3/16, 5/16 ratio
			uint32_t pix1 = idx(x + 1, y, image->width);
            image->pixels[pix1] += err_r * 7 / 16.0;
            image->pixels[pix1 + 1] += err_g * 7 / 16.0;
            image->pixels[pix1 + 2] += err_b * 7 / 16.0;

			uint32_t pix2 = idx(x - 1, y + 1, image->width);
            image->pixels[pix2] += err_r * 3 / 16.0;
            image->pixels[pix2 + 1] += err_g * 3 / 16.0;
            image->pixels[pix2 + 2] += err_b * 3 / 16.0;

			uint32_t pix3 = idx(x, y + 1, image->width);
			image->pixels[pix3] += err_r * 5 / 16.0;
            image->pixels[pix3 + 1] += err_g * 5 / 16.0;
            image->pixels[pix3 + 2] += err_b * 5 / 16.0;

			uint32_t pix4 = idx(x + 1, y + 1, image->width);
            image->pixels[pix4] += err_r * 1 / 16.0;
            image->pixels[pix4 + 1] += err_g * 1 / 16.0;
            image->pixels[pix4 + 2] += err_b * 1 / 16.0;
        
		}
	}
}
