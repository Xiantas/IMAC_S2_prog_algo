#include "binarytree.h"

#include <time.h>
#include <chrono>
#include <thread>

void Node::buildFromValues(const std::vector<int>& values) {
	if (values.empty())
		return;
    this->initNode(values[0]);
    for (size_t i=1; i <values.size(); ++i)
	{
		insertNumber(values[i]);
	}
}

uint _treeNodesCount(const Node &node)
{
	uint count = 1;
    if (node.get_left_child())
    {
        count += _treeNodesCount(*node.get_left_child());
    }
    if (node.get_right_child())
    {
        count += _treeNodesCount(*node.get_right_child());
    }
	return count;
}
