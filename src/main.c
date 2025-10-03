#include <stdlib.h>

#include "preprocessor.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "DEBUG: not enough params\n");
        exit(1);
    }

    Preprocessor *preprocessorBefore = createPreprocessor(argv[1]);
    //Preprocessor *preprocessorAfter = createPreprocessor(argv[2]);
    
    int *imgDimensions = calloc(2, sizeof(int));
    getImgDimensions(preprocessorBefore, imgDimensions);

    printf("%d %d\n", imgDimensions[0], imgDimensions[1]);

    /**
     * FREE MEMORY
     */
    deletePrepreprocessor(&preprocessorBefore);
    //deletePrepreprocessor(&preprocessorAfter);
    free(imgDimensions);
    imgDimensions = NULL;
    return 0;
}
