#include "btree.hpp"
#include "../../../pythia/externals/libconfig-1.2/grammar.y"

int LeafNode::delkey(uint64_t key) {
	int pos;
	// key val pair does not exist
	if (pos = find(key) == -1) {
		return 0;
	}
	
	for (int i = pos+1; i < keynum_; ++i) {
		keys_[i-1] = keys_[i];
		value_[i-1] = value_[i];
	}
	--keynum_;
	if (keynum_ >= kLeafNode/2) {
		return 0;
	}
	else {
		return 1;
	}
}

int LeafNode::find(uint64_t key) {
	// TODO should use binary search here
	for (int i = 0; i < keynum_; ++i) {
		if (keys_[i] == key) {
			return i;
		}
	}
	return -1;
}

int LeafNode::inskey(uint64_t key, uint64_t val, LeafNode* &splitnode) {
	int pos;
	splitnode = nullptr;
	if (pos = find(key) != -1) {
		value_[pos] = val;
		return 0;
	}
	pos = 0;
	while (keys_[pos] < key) {
		++pos;
	}
	
	for (int i = keynum_; i > pos; --i) {
		keys_[i] = keys_[i-1];
		value_[i] = value_[i-1];
	}
	keys_[pos] = key;
	value_[pos] = val;
	
	++keynum_;
	if (keynum_ <= kLeafNode) {
		return 0;
	}
	splitnode = new LeafNode();
	split(splitnode);
	return 1;
}

int LeafNode::merge(LeafNode* mergenode) {
	// combine the two nodes
	if (mergenode->keynum_ == kLeafNode/2) {
		
	}
}

int LeafNode::split(LeafNode* &splitnode) {
	LeafNode* nnode = new LeafNode();
	for (int i = kLeafNode/2; i < keynum_; ++i) {
		nnode->keynum_[i-kLeafNode/2] = keynum_[i];
		nnode->value_[i-kLeafNode/2] = value_[i];
	}
	nnode->keynum_ = keynum_ - kLeafNode/2;
	keynum_ = kLeafNode/2;
	splitnode = nnode;
	return 0;
}
