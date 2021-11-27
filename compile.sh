#!/bin/sh
#  ./compile.sh ; ./Image_Rescale ./test.ppm ; ./a.out ./fast_rescaled.ppm ./vanilla_rescaled.ppm ;
# valgrind --tool=callgrind [--cache-sim=yes/--branch-sim=yes] ./Image_Rescale test.ppm
# kcachegrind calgrind.out.12345
# https://waterprogramming.wordpress.com/2017/06/08/profiling-c-code-with-callgrind/
# Select the appropriate compiler command from the two  below

# g++ -g Image_Rescale.cpp -oImage_Rescale -lm      # No compiler optimization
g++ -g -O3 Image_Rescale.cpp -oImage_Rescale -lm      # With compiler optimization
#
