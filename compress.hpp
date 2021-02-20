#ifndef COMPRESS
#define COMPRESS

#include <iostream>
#include <vector>
#include <boost/dynamic_bitset.hpp> 
#include <cstdint>
#include <fstream>
#include <vector>
#include <boost/math/cstdfloat/cstdfloat_types.hpp>
#include <climits>
#include <cstring>
#include <iostream>
#include <map>
#include <boost/numeric/conversion/cast.hpp>
#include <set>
#include <queue>
#include <bitset>
using namespace std;

struct comp
{
	template<typename T>
	bool operator()(const T& l, const T& r) const
	{
		if (l.second != r.second)
			return l.second < r.second;

		return l.first < r.first;
	}
};



struct MinHeapNode { 
  
    float data; 
  
    unsigned freq; 
  
    MinHeapNode *left, *right; 
  
    MinHeapNode(float data, unsigned freq) 
  
    { 
  
        left = right = NULL; 
        this->data = data; 
        this->freq = freq; 
    } 
}; 
  
struct compare { 
  
    bool operator()(MinHeapNode* l, MinHeapNode* r) 
  
    { 
        return (l->freq > r->freq); 
    } 
}; 
  
void printCodes(struct MinHeapNode* root, string str, map<float,string> &code) 
{ 
  
    if (!root) 
        return; 
  
    if (root->data != 500) 
	{
  	code[root->data]=str;
	}
    printCodes(root->left, str + "0", code); 
    printCodes(root->right, str + "1", code); 
} 
  
void HuffmanCodes(set<pair<float,int>,comp> set, map<float,string> &code) 
{ 
    struct MinHeapNode *left, *right, *top; 
  
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap; 
  
  
	for(auto const &p: set)
	{
		minHeap.push(new MinHeapNode(p.first, p.second));
	}
    while (minHeap.size() != 1) { 
  
        left = minHeap.top(); 
        minHeap.pop(); 
  
        right = minHeap.top(); 
        minHeap.pop(); 
  
        top = new MinHeapNode(500, left->freq + right->freq); 
  
        top->left = left; 
        top->right = right; 
  
        minHeap.push(top); 
    } 
  
    printCodes(minHeap.top(), "",code); 
} 

map<float,string> code;
typedef boost::float32_t float32;

int compress(boost::dynamic_bitset<unsigned char>& input, boost::dynamic_bitset<unsigned char>& output){
	std::vector<float32> bytes;
	boost::to_block_range(input,std::back_inserter(bytes));
	map<float,int> freq;
	for(int i: bytes)
	{
		freq[i]=freq[i]+1;
	}
	
	set<pair<float,int>, comp> set(freq.begin(),freq.end());

	HuffmanCodes(set,code);
	for(int i: bytes)
	{
		string huff=code[i];
		for( auto c:huff)
		{
			if(c=='1')
				output.push_back(true);
			else
				output.push_back(false);
		}
	}
	cout<<"vector size: "<<bytes.size()<<endl;
	cout<<"SIZE: "<<endl<<input.size()<<endl<<output.size();
	return true;
}

int decompress(boost::dynamic_bitset<unsigned char>& input, boost::dynamic_bitset<unsigned char>& output){
	map<float, string>::iterator it;
	map<string,float> reverse;
	std::vector<float32> bytes;
	for(it =code.begin();it!=code.end();it++)
	{	
		reverse[it->second]=it->first;
	}
	
	bool b;
	string huffcode="";
	for(int i=0; i<input.size();i++)
	{	
		b=input[i];
		if(b==true)
			huffcode=huffcode+"1";
		else
			huffcode=huffcode+"0";

		map<string,float>::iterator it;
		it=reverse.find(huffcode);
		if(it!=reverse.end())
		{	
			bytes.push_back(reverse.find(huffcode)->second);
			string binary=bitset<8>(reverse.find(huffcode)->second).to_string();
			huffcode="";
			for(auto c: binary)
			{
				if(c=='1')
					output.push_back(true);
				else
					output.push_back(false);
			}		

		}
	}
	
	cout<<"FINAL SIZE: "<<output.size();
	//boost::from_block_range(bytes.begin(),bytes.end(),output);
	return true;
}

#endif
