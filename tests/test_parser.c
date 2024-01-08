#include <criterion/criterion.h>
#include "meta.h"

typedef struct s_test_params {
	t_meta	meta;
	char	*result;
	char	*expected;
}	t_test_params;

/* Parser function tests */

int map_extension(char *file);
/*
 Map extension checks that the flie extension is .cub and the file has a name before it
*/

Test(map_extension, extension_invalid_1) {
	cr_expect(map_extension("file.cu") == 1, "Input: file.cu, Expected: 1");
}

Test(map_extension, extension_invalid_2) {
	cr_expect(map_extension(".cubhh") == 1, "Input: .cubhh, Expected: 1");
}

Test(map_extension, extension_invalid_3) {
	cr_expect(map_extension(".cuub") == 1, "Input: .cuub, Expected: 1");
}

Test(map_extension, filename_invalid) {
	cr_expect(map_extension(".cub") == 1, "Input: .cub, Expected: 1");
}

Test(map_extension, extension_valid) {
	cr_expect(map_extension("file.cub") == 0, "Input: file.cub, Expected: 0");
}

Test(map_extension, no_extension) {
	cr_expect(map_extension("file") == 1, "Input: file, Expected: 1");
}

