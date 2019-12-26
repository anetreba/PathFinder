echo test1 no arguments
./a.out 2> ./res/res.txt
diff ./res/tst1.txt ./res/res.txt

echo test2 no file
./a.out islands 2> ./res/res.txt
diff ./res/tst2.txt ./res/res.txt

echo test3 empty file
./a.out empty.txt 2> ./res/res.txt
diff ./res/tst3.txt ./res/res.txt

echo test4 invalid1
./a.out invalid1 2> ./res/res.txt
diff ./res/tst4.txt ./res/res.txt

echo test5 invalid2
./a.out invalid2 2> ./res/res.txt
diff ./res/tst5.txt ./res/res.txt

echo test6 invalid3
./a.out invalid3 2> ./res/res.txt
diff ./res/tst6.txt ./res/res.txt

echo test7 example1
./a.out example1 > ./res/res.txt
diff ./res/tst7.txt ./res/res.txt

echo test8 example2
./a.out example2 > ./res/res.txt
diff ./res/tst8.txt ./res/res.txt

echo test9 easy
./a.out easy > ./res/res.txt
diff ./res/tst9.txt ./res/res.txt

echo test10 medium
./a.out medium > ./res/res.txt
diff ./res/tst10.txt ./res/res.txt

echo test11 hard
./a.out hard > ./res/res.txt
diff ./res/tst11.txt ./res/res.txt

echo test12 hardest
./a.out hardest > ./res/res.txt
diff ./res/tst12.txt ./res/res.txt

echo test13 invalid4
./a.out invalid4 2> ./res/res.txt
diff ./res/tst13.txt ./res/res.txt
