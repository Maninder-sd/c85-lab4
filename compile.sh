#!/bin/sh
#  ./compile.sh ; ./Image_Rescale ./test.ppm ; ./a.out ./fast_rescaled.ppm ./vanilla_rescaled.ppm ;
# Select the appropriate compiler command from the two  below

g++ -g Image_Rescale.cpp -oImage_Rescale -lm      # No compiler optimization
# g++ -g -O3 Image_Rescale.cpp -oImage_Rescale -lm      # With compiler optimization
#
