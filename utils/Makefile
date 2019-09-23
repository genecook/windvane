LIBDIRS := -L/usr/lib/x86_64-linux-gnu -L./lib


TEST_HARNESS := ../bin/test_harness


all: ${TEST_HARNESS}


${TEST_HARNESS}: test_harness.C
	g++ -std=c++11 -fopenmp -Wall -Werror -DOPENMP -o $@ $< $(LIBDIRS) -lboost_program_options