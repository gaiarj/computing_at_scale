#!/bin/bash
set +x 
pwd=$PWD
command="${pwd}/matrix.x"
cd ./tests
echo "Running test 1"
$command ./t1_1 ./t1_2
echo -e "Finished \n######"
echo "Running test 2, should give error"
$command ./t2_1 ./t2_2
echo -e "Finished \n######"
echo "Running test 3, should give error"
$command ./notexist ./notexist1
echo -e "Finished \n######"
echo "Running test 4"
$command ./t4_1 ./t4_2
echo -e "Finished \n######"
echo "Running test 5, should give error"
$command ./t5_1 ./t5_2
echo -e "Finished \n######"
echo "Running test 6, should give error"
$command ./t6_1 ./t6_2 ./t5_1 ./t5_2
echo -e "Finished \n######"

