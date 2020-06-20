#pragma once
#include <vector>
#include "Base_item.h"

class Node
{
public:
	Base_item& base_item;
	vector<Node*> nodes_vector;
	bool completed;
	Node() = delete;
	Node(Base_item& _base_item): base_item(_base_item),completed(false) {}
};

