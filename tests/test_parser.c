#include <criterion/criterion.h>

int		map_ext(char *file);

Test(map_extension, extension_invalid) {
    cr_expect(map_ext("file.cu") == 1, "Input: file.cu, Expected: 1");
}

Test(map_extension, extension_valid) {
    cr_expect(map_ext("file.cub") == 0, "Input: file.cub, Expected: 0");
}