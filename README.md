# Optical Flow Method
Optical flow for planetary cloud tracking

# Objective
Use two images taken $\Delta t$ apart and track the wind velocity patterns.
Purely algorithmic, no AI/ML.

# Run Instructions
 - Download ![libTIFF](https://libtiff.gitlab.io/libtiff/) for parsing .tif images
 - `cd` in to `src` directory
 - Adjust Makefile as necessary
    - If you ran `make install` for LibTIFF should work out of the box
 - run `make clean` and `make`
 - `./main <img_before.tif> <img_after.tif> dt`

# Acknowledgements
This work used data acquired from the NASA/ESA HST Space Telescope, associated
with OPAL program (PI: Simon, GO13937), and archived by the Space Telescope
Science Institute, which is operated by the Association of Universities for
Research in Astronomy, Inc., under NASA contract NAS 5-26555. All maps are
available at http://dx.doi.org/10.17909/T9G593
