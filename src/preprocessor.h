#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "tiffio.h"

class Preprocessor {
    public:
        TIFF *imgBefore;
        TIFF *imgAfter;

        /**
         * Class constructor
         *
         * @param beforeFile        file name of image at t1
         * @param afterFile         file name of image at t2
         * @param dt                change in time in minutes
         */
        Preprocessor(string beforeFile, string afterFile, double dt);

        /**
         * Class destructor: Frees all memory hopefully
         */
        ~Preprocessor();

};

#endif
