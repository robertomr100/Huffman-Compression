// We need to test compress - decomprss 
//
// Test both size + speed of the function
// Correctness + Size + Speed tests + Rank all students

// This code takes as the last argument the name of the student
// It can take variable number of files as input arguments.

#include "compress.hpp"
#include <cstdint>
#include <fstream>
#include <vector>
#include <boost/math/cstdfloat/cstdfloat_types.hpp>
#include <climits>
#include <cstring>
#include <iostream>
#include <boost/numeric/conversion/cast.hpp>
#include <sys/time.h>
#include <unistd.h>

typedef boost::float32_t float32;
typedef boost::uint32_t uint32;
struct timeval st, et;

int main(int argc, char *argv[]){
       unsigned char *cp;
       float32 value;
       value = 8.0;
       boost::uint32_t internal;
       std::memcpy( &internal , &value , sizeof( value ) );
       int correct_count=0;
       long int num_files=argc-2;
       long int compress_time=0;
       long int decompress_time=0;
       long long int compressed_size=0;
	// all arguments except the last are test files
       
       for(int i=1; i < argc-1;i++)
       {
	//read the files and put in vector       
		std::vector<unsigned char> data;
           	std::ifstream fin(argv[i], std::ios::binary);
           	while (fin.read(reinterpret_cast<char*>(&internal), sizeof(uint32))){
              		std::memcpy( &value, &internal , sizeof( internal ) );
              		cp = (unsigned char *)&internal;
              		for(int i = 0; i < 4; ++i){
                      		data.push_back(*cp);
                      		++cp;
              		}
        	}
		
		// create bitset for entire data
		boost::dynamic_bitset<unsigned char> c_db;
	        boost::dynamic_bitset<unsigned char> d_db;
        	boost::dynamic_bitset<unsigned char> db, backup;
        	db.init_from_block_range(data.begin(), data.end());
                backup = db;
                std::cout << db.size() << std::endl;
		// finding the time for compression
                gettimeofday(&st, NULL);
        	compress(db, c_db);
                // sleep(10);
                gettimeofday(&et, NULL);
                compress_time += (((et.tv_sec - st.tv_sec) * 1000) + (et.tv_usec/1000 - st.tv_usec/1000));
                // Find the size after compression
		compressed_size+= (long int)c_db.size();
		// finding time for decompression
        	gettimeofday(&st, NULL);
		decompress(c_db, d_db);
                //sleep(5);
		gettimeofday(&et, NULL);
                decompress_time += (((et.tv_sec - st.tv_sec) * 1000) + (et.tv_usec/1000 - st.tv_usec/1000));
                // Comparison for correctness
		if(backup == db)
			correct_count++;
	}
        //file.open(argv[argc-1], std::ios::out | std::ios::app);
	// print the stats
	std::cout << "Name, Num_correct, Compress_time, Decompress_time, Size" << std::endl;
        std::cout << argv[argc-1] << ", " << correct_count << ", " << ((float)compress_time)/(float)num_files << ", " << ((float)decompress_time)/(float)num_files << ", " << compressed_size << std::endl;      
        return 0;
}
