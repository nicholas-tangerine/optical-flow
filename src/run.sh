clear
make clean
make
#./main ../cloud-images/jupiter-2016-f395n/hlsp_opal_hst_wfc3-uvis_jupiter-2016a_f395n_v1_globalmap.tif ../cloud-images/jupiter-2016-f395n/hlsp_opal_hst_wfc3-uvis_jupiter-2016b_f395n_v1_globalmap.tif 20
#./main ../cloud-images/jupiter-2017-f502n/hlsp_opal_hst_wfc3-uvis_jupiter-2017a_f502n_v1_globalmap.tif ../cloud-images/jupiter-2017-f502n/hlsp_opal_hst_wfc3-uvis_jupiter-2017b_f502n_v1_globalmap.tif 20
./main ../cloud-images/jupiter-2021-f631n/hlsp_opal_hst_wfc3-uvis_jupiter-2021a_f631n_v1_globalmap.tif ../cloud-images/jupiter-2021-f631n/hlsp_opal_hst_wfc3-uvis_jupiter-2021a_f631n_v1_globalmap.tif 20
open output1-streamlines.ppm
open output2-streamlines.ppm
#echo "beginning python script\n" && python3 draw_velo_field.py "velo field downscaled.txt"
