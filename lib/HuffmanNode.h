#pragma once

#include "binarytree.h"
#include <vector>

struct HuffmanNode : public Node
{
    HuffmanNode* left;
    HuffmanNode* right;

    int frequences;
    unsigned char character;
    std::string code;

    HuffmanNode(unsigned char c='\0', int frequences=0) : Node(frequences)
    {
        this->frequences = frequences;
        this->character = c;
        this->code = std::string();
        this->left = this->right = NULL;
    }

    HuffmanNode(const HuffmanNode& node): Node(node)
    {
        this->frequences = node.frequences;
        this->character = node.character;
        this->code = std::string(node.code);
        this->left = this->right = NULL;
    }

    virtual bool isLeaf() const {return !this->left && !this->right;}

    void insertNode(HuffmanNode*);
    void processCodes(const std::string &baseCode);
    void fillCharactersArray(std::string nodes_for_chars[]);


    virtual ~HuffmanNode() {}
};


class HuffmanHeap : public std::vector<HuffmanNode*>
{
public:
    typedef std::vector<HuffmanNode*> Base;

    virtual ~HuffmanHeap() {}

    HuffmanHeap(uint size=100) : std::vector<HuffmanNode*>()
    {
        if (size>0)
        {
            (*this).resize(size);
            for (uint i=0; i<size; ++i)
                (*this)[i] = nullptr;
        }
    }

    virtual size_t effectiveSize() const
    {
        size_t size=0;
        for (const HuffmanNode* value : (*this))
            if (value == nullptr)
                return size;
            else
                size++;
        return size;
    }

    HuffmanNode* get(uint index) const {
        return (*this)[index];
    }

    void insertHeapNode(int heapSize, HuffmanNode *newNode);
    void heapify(int heapSize, int nodeIndex);
    HuffmanNode* extractMinNode(int heapSize);

protected:
//    void insert(const int index, const ElementType& value) {
//        // Base::insert(index, value);
//    }
};
