The program uses huffman algorithm for compression. It first stores the bitset in a vector of bytes, calculates the frequency of every byte, sorts them by frequency and calculates the huffman tree and gives the huffman code. 
Then each byte is changed into its huffman code and stored in a new bitset.
For decompression the new bitset is read bit by bit until a recognizable huffman code is read, then the code is translated into its real value and put into a new bitset.
I utilized the page https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/ as a help for the huffman algorithm.