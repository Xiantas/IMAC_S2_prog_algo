#pragma once

#include <vector>

typedef unsigned uint;

struct Node
{
    Node(int) {}
    Node(const Node&) {}

	virtual ~Node()
	{
        reset();
	};

    virtual void initNode(int) {};
    virtual int get_value() const {return 0;}
    virtual Node* get_left_child() const {return nullptr;}
    virtual Node* get_right_child() const {return nullptr;}
    virtual uint height() const {return 0;}
	virtual uint nodesCount() const {return 0;}
	virtual bool isLeaf() const {return false;}
	virtual void allLeaves(std::vector<Node*>&) {return;}
	virtual void inorderTravel(std::vector<Node*>&) {return;}
	virtual void preorderTravel(std::vector<Node*>&) {return;}
	virtual void postorderTravel(std::vector<Node*>&) {return;}
	virtual Node* find(int) {return nullptr;}
	virtual void insertNumber(int) {return;}

//    virtual QString toString() const {return QString::number(this->get_value());}

    virtual void reset() {};
    void buildFromValues(const std::vector<int>& values);
};

Node* createNode(int value);
uint _treeNodesCount(const Node& node);

typedef Node BinaryTree;
