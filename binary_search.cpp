#include <cstdio>
#include <chrono>
#include <algorithm>

#include "utils/gendata.hpp"

#include "binary_search/single.hpp"
#include "binary_search/plain_interleaving.hpp"
#include "binary_search/group_prefetching.hpp"


typedef uint64_t(*func_t)(const uint32_t*,size_t,const uint32_t*,size_t);

static void probe(const char *desc, func_t fn, const GenData &gd){
	auto start = std::chrono::high_resolution_clock::now();

	uint64_t sum = fn(gd.keys, gd.number_of_elements, gd.data, 4*1024*1024);
	//uint64_t sum = fn(gd.keys, gd.number_of_elements, gd.data, gd.number_of_elements);

	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	printf("%23s: %7lu us; sum: %lu\n", desc, time, sum);
}

int main(int argc, char **argv){
	if(argc < 2){
		fprintf(stderr, "requires import file as first argument\n");
		return -1;
	}

	GenData gd(argv[1]);

	// for now use data column as search keys which is not the best
	//TODO: get search keys which are not all hitting

	probe("std::binary_search", stl_binary_search, gd);
	probe("std::lower_bound", stl_lower_bound, gd);
	probe("single", single, gd);
	probe("single2", single2, gd);
	probe("plain_interleaving4", plain_interleaving4, gd);
	probe("plain_interleaving8", plain_interleaving8, gd);
	probe("plain_interleaving<4>", plain_interleaving<4>, gd);
	probe("plain_interleaving<8>", plain_interleaving<8>, gd);
	probe("plain_interleaving<10>", plain_interleaving<10>, gd);
	probe("plain_interleaving<12>", plain_interleaving<12>, gd);
	probe("plain_interleaving<14>", plain_interleaving<14>, gd);
	probe("plain_interleaving<16>", plain_interleaving<16>, gd);
	probe("plain_interleaving<18>", plain_interleaving<18>, gd);
	probe("plain_interleaving<20>", plain_interleaving<20>, gd);
	probe("group_prefetching<4>", group_prefetching<4>, gd);
	probe("group_prefetching<8>", group_prefetching<8>, gd);
	probe("group_prefetching<10>", group_prefetching<10>, gd);
	probe("group_prefetching<12>", group_prefetching<12>, gd);
	probe("group_prefetching<14>", group_prefetching<14>, gd);
	probe("group_prefetching<16>", group_prefetching<16>, gd);
	probe("group_prefetching<18>", group_prefetching<18>, gd);
	probe("group_prefetching<20>", group_prefetching<20>, gd);

	return 0;
}
