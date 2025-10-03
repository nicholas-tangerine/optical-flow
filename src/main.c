#include <stdlib.h>

#include "preprocessor.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("not enough params\n");
        exit(1);
    }

    Preprocessor *preprocessorBefore = createPreprocessor(argv[1]);
    //Preprocessor *preprocessorAfter = createPreprocessor(argv[2]);
    
    printAllTags(preprocessorBefore);

    deletePrepreprocessor(&preprocessorBefore);
    //deletePrepreprocessor(&preprocessorAfter);
    return 0;
}
