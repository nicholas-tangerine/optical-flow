#include "preprocessor.h"

Preprocessor::Preprocessor(string beforeFile, string afterFile, double dt) {
    imgBefore = TIFFOpen(beforeFile, "r");
    imgBefore = TIFFOpen(afterFile, "r");
}

Preprocessor::~Preprocessor() {
    TIFFClose(imgBefore);
    TIFFClose(imgAfter);
}
