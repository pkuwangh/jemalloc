LIB=../build/lib
INC=../build/include

default: pf_test.c
	gcc -g pf_test.c -I$(INC) -o exe_pf_test_baseline -O2
	gcc -g pf_test.c -I$(INC) -o exe_pf_test_jemalloc -DUSE_JEMALLOC -O2 -L$(LIB) -ljemalloc

run: baseline jemalloc

baseline: default
	./exe_pf_test_baseline
	./exe_pf_test_baseline
	./exe_pf_test_baseline
	./exe_pf_test_baseline

jemalloc: default
	LD_LIBRARY_PATH=$(LIB) ./exe_pf_test_jemalloc
	LD_LIBRARY_PATH=$(LIB) ./exe_pf_test_jemalloc
	LD_LIBRARY_PATH=$(LIB) ./exe_pf_test_jemalloc
	LD_LIBRARY_PATH=$(LIB) ./exe_pf_test_jemalloc

clean:
	rm -f exe_*
