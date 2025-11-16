clear
make clean
make -j
#
# FULL JUPITER IMAGES
#
# ./main ../cloud-images/OPAL/jupiter-2016-f395n/hlsp_opal_hst_wfc3-uvis_jupiter-2016a_f395n_v1_globalmap.tif ../cloud-images/OPAL/jupiter-2016-f395n/hlsp_opal_hst_wfc3-uvis_jupiter-2016b_f395n_v1_globalmap.tif 20
# ./main ../cloud-images/OPAL/jupiter-2017-f502n/hlsp_opal_hst_wfc3-uvis_jupiter-2017a_f502n_v1_globalmap.tif ../cloud-images/OPAL/jupiter-2017-f502n/hlsp_opal_hst_wfc3-uvis_jupiter-2017b_f502n_v1_globalmap.tif 20
# ./main ../cloud-images/OPAL/jupiter-2021-f631n/hlsp_opal_hst_wfc3-uvis_jupiter-2021a_f631n_v1_globalmap.tif ../cloud-images/OPAL/jupiter-2021-f631n/hlsp_opal_hst_wfc3-uvis_jupiter-2021a_f631n_v1_globalmap.tif 20

# 
# CROPPED GRS IMAGES
#
# ./main ../cloud-images/OPAL/jupiter-2017-f502n-cropped/hlsp_opal_hst_wfc3-uvis_jupiter-2017a_f502n_v1_globalmap_cropped.tif ../cloud-images/OPAL/jupiter-2017-f502n-cropped/hlsp_opal_hst_wfc3-uvis_jupiter-2017b_f502n_v1_globalmap_cropped.tif 20

# 
# GRS-WFC3 images (from ACCIV paper iirc?????)
#
# ./main ../cloud-images/GRS-WFC3/grs09_01.tiff ../cloud-images/GRS-WFC3/grs09_02.tiff 20

#
# SYNTHETIC IMAGES
# 
./main ../cloud-images/simulated-images/before.tif ../cloud-images/simulated-images/after.tif 20

open output1-streamlines.ppm
open output2-streamlines.ppm
