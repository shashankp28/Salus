CXX=g++
CFLAGS=-I./inc -g -Wall -Werror -std=c++11 -O3
bin_dir = bin
obj_dir = obj

matmul: matmul1 matmul2 matmul3

build_matmul1: src/matmul1.cpp obj/matfunc.o
	$(CXX) $(CFLAGS) $^ -o bin/matmul1
build_matmul2: src/matmul2.cpp obj/matfunc.o
	$(CXX) $(CFLAGS) $^ -o bin/matmul2
build_matmul3: src/matmul3.cpp obj/matfunc.o
	$(CXX) $(CFLAGS) $^ -o bin/matmul3
obj/matfunc.o: src/matfunc.cpp inc/matfunc.h
	$(CXX) $(CFLAGS) -c $< -o $@

matmul1: check_bin check_obj build_matmul1
matmul2: check_bin check_obj build_matmul2
matmul3: check_bin check_obj build_matmul3

check_bin:
	[ -d $(bin_dir) ] || mkdir -p $(bin_dir)

check_obj:
	[ -d $(obj_dir) ] || mkdir -p $(obj_dir)

clean:
	rm -f obj/* bin/*