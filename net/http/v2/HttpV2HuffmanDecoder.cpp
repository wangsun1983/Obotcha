#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpV2HuffmanDecoder.hpp"
#include "IllegalStateException.hpp"

namespace obotcha {

//------------------------ Node ---------------------
_Node::_Node() {
    symbol = 0;
    bits = 8;
    children = createList<Node>(256);
}

_Node::_Node(int symbol, int bits) {
    this->symbol = symbol;
    this->bits = bits;
    children = nullptr;
}

bool _Node::isTerminal() {
    return children == nullptr;
}

//------------------------ HuffmanDecoder ---------------------
_HuffmanDecoder::_HuffmanDecoder(List<int> codes, List<byte> lengths) {
    //TODO
}

Node _HuffmanDecoder::buildTree(List<int>codes, List<byte> lengths) {
    #if 0
    Node root = new Node();
    for (int i = 0; i < codes->size(); i++) {
        insert(root, i, codes[i], lengths[i]);
    }
    return root;
    #endif
    return nullptr;
}

void _HuffmanDecoder::insert(Node root, int symbol, int code, byte length) {
    // traverse tree using the most significant bytes of code
    #if 0
    Node current = root;
    while (length > 8) {
        if (current->isTerminal()) {
            throw IllegalStateException("invalid Huffman code: prefix not unique");
        }
        length -= 8;
        int i = (code >>> length) & 0xFF;
        if (current->children[i] == null) {
            current->children[i] = createNode();
        }
        current = current->children[i];
    }

    Node terminal = createNode(symbol, length);
    int shift = 8 - length;
    int start = (code << shift) & 0xFF;
    int end = 1 << shift;
    for (int i = start; i < start + end; i++) {
        current->children[i] = terminal;
    }
    #endif
}

}
