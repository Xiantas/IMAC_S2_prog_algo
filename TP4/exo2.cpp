#include <time.h>
#include <stdio.h>
#include <string>
#include <utility>
#include <iostream>

#include "../lib/HuffmanNode.h"
#include "../TP2/common_utils.cpp"

using std::size_t;
using std::string;

void processCharFrequences(string data, Array& frequences);
void buildHuffmanHeap(const Array& frequences, HuffmanHeap& priorityMinHeap, int& heapSize);
HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode);
HuffmanNode* buildHuffmanTree(HuffmanHeap& priorityMinHeap, int heapSize);

string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree);
string huffmanDecode(const string& toDecode, HuffmanNode* huffmanTreeRoot);

void displayCharacterFrequences(Array& array) {
    for (uint i = 0; i < array.size(); ++i) {
        if (array[i] != 0) {
            std::cout << "freq " << i << " : " << array[i] << "\n";
        }
    }
}

void main_function(HuffmanNode*& huffmanTree)
{
    string data = "Ouesh, bien ou bien ? Ceci est une chaine de caracteres sans grand interet";

    // this array store each caracter frequences indexed by their ascii code
    Array characterFrequences(256, 0);
    // this array store each caracter code indexed by their ascii code
    string characterCodes[256];
    HuffmanHeap priorityMinHeap;
    int heapSize = 0;

    processCharFrequences(data, characterFrequences);
    displayCharacterFrequences(characterFrequences);
    buildHuffmanHeap(characterFrequences, priorityMinHeap, heapSize);
    std::cout << "Huffman heap built\n";

    huffmanTree = buildHuffmanTree(priorityMinHeap, heapSize);
    std::cout << "Huffman tree built\n";
    huffmanTree->processCodes("");
    string encoded = huffmanEncode(data, huffmanTree);
    string decoded = huffmanDecode(encoded, huffmanTree);

    std::cout << "Encodé : " << encoded << "\n";
    std::cout << "Décodé : " << decoded << "\n";
}


void processCharFrequences(string data, Array& frequences)
{
    fill(frequences, 0);

    for (uint i = 0; i < data.size(); ++i) {
        ++frequences[data[i]];
    }
}

void HuffmanHeap::insertHeapNode(int heapSize, HuffmanNode* newNode)
{
    int i = heapSize;

    (*this)[i] = newNode;
    while (i>0 && (*this)[i]->frequences < (*this)[(i-1)/2]->frequences) {
        std::swap((*this)[i], (*this)[(i-1)/2]);
        i = (i-1)/2;
    }
}

void buildHuffmanHeap(const Array& frequences, HuffmanHeap& priorityMinHeap, int& heapSize)
{
    heapSize = 0;

    for (unsigned i = 0; i < frequences.size(); ++i) {
        if (frequences[i] != 0) {
            priorityMinHeap.insertHeapNode(heapSize, new HuffmanNode(i, frequences[i]));
            ++heapSize;
        }
    }
}

void HuffmanHeap::heapify(int heapSize, int nodeIndex)
{
	int i_min = nodeIndex;
    int childIndex = 2*nodeIndex+1;
    if (childIndex < heapSize && (*this)[i_min]->frequences > (*this)[childIndex]->frequences) {
        i_min = childIndex;
    }
    childIndex = 2*nodeIndex+2;
    if (childIndex < heapSize && (*this)[i_min]->frequences > (*this)[childIndex]->frequences) {
        i_min = childIndex;
    }

    if (i_min != nodeIndex) {
        std::swap((*this)[i_min], (*this)[nodeIndex]);
        this->heapify(heapSize, i_min);
    }
}


HuffmanNode* HuffmanHeap::extractMinNode(int heapSize)
{
    HuffmanNode *first_node = (*this)[0];

    (*this)[0] = (*this)[heapSize];
    --heapSize;
    this->heapify(heapSize, 0);

    return first_node;
}

HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode)
{
    HuffmanNode* res = new HuffmanNode('\0', leftNode->frequences+rightNode->frequences);

    res->left = leftNode;
    res->right = rightNode;

    return res;
}

HuffmanNode* buildHuffmanTree(HuffmanHeap& priorityMinHeap, int heapSize)
{
    while (heapSize > 1) {
        HuffmanNode *nodeA = priorityMinHeap.extractMinNode(heapSize);
        --heapSize;
        HuffmanNode *nodeB = priorityMinHeap.extractMinNode(heapSize);
        --heapSize;
        HuffmanNode *newNode = makeHuffmanSubTree(nodeA, nodeB);
        priorityMinHeap.insertHeapNode(heapSize, newNode);
        ++heapSize;
    }

    return priorityMinHeap[0];
}

void HuffmanNode::processCodes(const std::string& baseCode)
{
    if (this->character != '\0') {
        this->code = baseCode;
        return;
    }

    this->left->processCodes(baseCode + "0");
    this->right->processCodes(baseCode + "1");
}

void HuffmanNode::fillCharactersArray(std::string charactersCodes[])
{
    /**
      * Fill the string array with all nodes codes of the tree
      * It store a node into the cell corresponding to its ascii code
      * For example: the node describing 'O' should be at index 79
     **/
    if (!this->left && !this->right)
        charactersCodes[this->character] = this->code;
    else {
        if (this->left)
            this->left->fillCharactersArray(charactersCodes);
        if (this->right)
            this->right->fillCharactersArray(charactersCodes);
    }
}

string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree)
{
    /**
      * Encode a string by using the huffman compression.
      * With the huffmanTree, determine the code for each character
     **/

    // Your code
    std::string charactersCodes[256]; // array of 256 huffman codes for each character
    huffmanTree->fillCharactersArray(charactersCodes);
    string encoded = "";

    for (uint i = 0; i < toEncode.size(); ++i) {
        encoded += charactersCodes[toEncode[i]];
    }

    return encoded;
}


string huffmanDecode(const string& toDecode, HuffmanNode* huffmanTreeRoot)
{
    /**
      * Use each caracters of toDecode, which is '0' either '1',
      * to travel the Huffman tree. Each time you get a leaf, get
      * the decoded character of this node.
     **/
    // Your code
    string decoded = "";

    HuffmanNode *readingHead = huffmanTreeRoot;

    for (uint i = 0; i < toDecode.size(); ++i) {
        if (toDecode[i] == '0') {
            readingHead = readingHead->left;
        } else {
            readingHead = readingHead->right;
        }

        if (readingHead->isLeaf()) {
            decoded += readingHead->character;
            readingHead = huffmanTreeRoot;
        }
    }

    return decoded;
}


int main()
{
    HuffmanNode *huffmanTree = nullptr;
    main_function(huffmanTree);
    return 0;
}
