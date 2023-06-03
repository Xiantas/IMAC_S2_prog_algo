#include <time.h>
#include <stack>
#include <queue>

#include <iostream>

#include "../lib/binarytree.cpp"
#include "../TP2/common_utils.cpp"

struct SearchTreeNode : public Node
{    
    SearchTreeNode *left;
    SearchTreeNode *right;
    int value;

    SearchTreeNode(): Node(0), left(nullptr), right(nullptr) {};
    void initNode(int value) {
        this->left = nullptr;
        this->right = nullptr;
        this->value = value;
    }
    SearchTreeNode(int value) : Node(value) {initNode(value);}

	void insertNumber(int value) {
        SearchTreeNode  **branch = this->value < value ? &right : &left;

        if (*branch == nullptr) {
            *branch = new SearchTreeNode(value);
            return;
        }

        (**branch).insertNumber(value);
    }

	uint height() const	{
        uint lHeight = this->left == nullptr ? 0 : this->left->height();
        uint rHeight = this->right == nullptr ? 0 : this->right->height();
        return 1 + (lHeight > rHeight ? lHeight : rHeight);
    }

	uint nodesCount() const {
        uint lNodes = this->left == nullptr ? 0 : this->left->nodesCount();
        uint rNodes = this->right == nullptr ? 0 : this->right->nodesCount();
        return 1 + lNodes + rNodes;
	}

	bool isLeaf() const {
        return !(left || right);
	}

	void allLeaves(std::vector<Node*>& nodes) {
        if (this->isLeaf()) {
            nodes.push_back(this);
        }

        if (this->left != nullptr) {
            this->left->allLeaves(nodes);
        }
        if (this->right != nullptr) {
            this->right->allLeaves(nodes);
        }
	}

	void inorderTravel(std::vector<Node*>& nodes) {
        if (this->left != nullptr) {
            this->left->inorderTravel(nodes);
        }
        nodes.push_back(this);
        if (this->right != nullptr) {
            this->right->inorderTravel(nodes);
        }
	}

	void preorderTravel(std::vector<Node*>& nodes) {
        nodes.push_back(this);
        if (this->left != nullptr) {
            this->left->preorderTravel(nodes);
        }
        if (this->right != nullptr) {
            this->right->preorderTravel(nodes);
        }
	}

	void postorderTravel(std::vector<Node*>& nodes) {
        if (this->left != nullptr) {
            this->left->postorderTravel(nodes);
        }
        if (this->right != nullptr) {
            this->right->postorderTravel(nodes);
        }
        nodes.push_back(this);
	}

	Node* find(int value) {
        if (this->value == value)
            return this;
        if (this->value < value && this->right != nullptr)
            return this->right->find(value);
        if (this->value > value && this->left != nullptr)
            return this->left->find(value);
		return nullptr;
	}

    void reset()
    {
        if (left != nullptr)
            delete left;
        if (right != nullptr)
            delete right;
        left = right = nullptr;
    }

    ~SearchTreeNode() {}
    int get_value() const {return value;}
    Node* get_left_child() const {return left;}
    Node* get_right_child() const {return right;}
};

Node* createNode(int value) {
    return new SearchTreeNode(value);
}

void _printTreeRec(SearchTreeNode* tree, int level) {
    if (tree == nullptr) {return;}

    _printTreeRec(tree->right, level+1);
    for (int i = 1; i < level; ++i) {std::cout << "  |";}
    if (level > 0) std::cout << "  + ";
    std::cout << tree->value << "\n";
    _printTreeRec(tree->left, level+1);

}

void printTree(SearchTreeNode* tree) {
    _printTreeRec(tree, 0);
}

int main()
{
    Array array(10, 0);
    fillRandom(array);

    printArray(array);
    SearchTreeNode tree;
    tree.buildFromValues(array);
    printTree(&tree);

    std::cout << "\nHauteur de l'arbre : " << tree.height() << "\n";
    std::cout << "Nombre de nœuds : " << tree.nodesCount() << "\n";

    std::vector<Node*> nodes;
    tree.allLeaves(nodes);
    std::cout << "Les feuilles : [";
    for (uint i = 0; i < nodes.size(); ++i) {
        std::cout << nodes[i]->get_value() << ", ";
    }
    std::cout << "]\n";

    nodes.clear();

    tree.inorderTravel(nodes);
    std::cout << "Parcours infixe : [";
    for (uint i = 0; i < nodes.size(); ++i) {
        std::cout << nodes[i]->get_value() << ", ";
    }
    std::cout << "]\n";

    nodes.clear();

    tree.preorderTravel(nodes);
    std::cout << "Parcours préfixe : [";
    for (uint i = 0; i < nodes.size(); ++i) {
        std::cout << nodes[i]->get_value() << ", ";
    }
    std::cout << "]\n";

    nodes.clear();

    tree.postorderTravel(nodes);
    std::cout << "Parcours postfixe : [";
    for (uint i = 0; i < nodes.size(); ++i) {
        std::cout << nodes[i]->get_value() << ", ";
    }
    std::cout << "]\n";

    std::cout << tree.find(array[array.size()/2])->get_value() << "\n";

    return 0;
}
