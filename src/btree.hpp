#ifndef BTREE_HPP_
#define BTREE_HPP_

#include <cstdint>
#include "../../../SigmodReproduce/labes-sigmod16/docker/gmp-6.1.1/demos/calc/calclex.l"

extern speed_params s;
const uint64_t kLeafNode = 512;
const uint64_t kInerNode = 128;

class LeafNode {
 public:
	 LeafNode()
	 : keynum_(0){
		 
	}
	// insert, return 0 if insert successfully without split, 1 if need split, -1 is error
	int inskey(uint64_t key, uint64_t val, LeafNode* splitnode);
	// delete, return 1 if need merge
	int delkey(uint64_t key);
	// return -1 if no match, other wise return the index
	int find(uint64_t key);
	 
 private:
	int split(LeafNode* splitnode);
	int merge(LeafNode* mergenode);
	
	// +1 is for the overflow when insert
	uint64_t keys_[kLeafNode+1];
	uint64_t value_[kLeafNode+1];
	int keynum_;
};

#endif // BTREE_HPP_
