#include <stdlib.h>

#include "tiff_helpers.h"
#include "preprocessor.h"
#include "image.h"

#include "debug_utils.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "DEBUG: not enough params\n");
        return 1;
    }

    image_t *img_before = image_init(argv[1], "r");
    image_t *img_after = image_init(argv[2], "r");

    if (!image_same_dimensions(img_before, img_after)) {
        fprintf(stderr, "DEBUG: before and after images do not have the same dimensions\n");
        return 1;
    }

    write_intensity_buffer_to_ppm(img_before->intensity_buffer, img_before->width, img_before->height, "intensity output1.ppm");
    write_intensity_buffer_to_ppm(img_after->intensity_buffer, img_after->width, img_after->height, "intensity output2.ppm");

    write_color_buffer_to_ppm(img_before->color_buffer, img_before->width, img_before->height, "color output1.ppm");
    write_color_buffer_to_ppm(img_after->color_buffer, img_after->width, img_after->height, "color output2.ppm");

    intensity_normalize(img_before->intensity_buffer, img_before->height, img_before->width);
    intensity_normalize(img_after->intensity_buffer, img_after->height, img_after->width);

    write_intensity_buffer_to_ppm(img_before->intensity_buffer, img_before->width, img_before->height, "normalized intensity output1.ppm");
    write_intensity_buffer_to_ppm(img_after->intensity_buffer, img_after->width, img_after->height, "normalized intensity output2.ppm");

    /**
     * FREE MEMORY
     */
    image_free(&img_before);
    image_free(&img_after);

    return 0;
}
