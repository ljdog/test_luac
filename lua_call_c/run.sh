#/bin/bash
gcc  -o my_addtest.o -c my_addtest.c ; gcc -O2 -bundle -undefined dynamic_lookup -o mylib.so my_addtest.o # 编译so
lua test_so.lua

