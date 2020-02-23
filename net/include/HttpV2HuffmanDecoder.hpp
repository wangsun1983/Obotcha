#ifndef __HTTP_V2_HUFFMAN_DECODER_HPP__
#define __HTTP_V2_HUFFMAN_DECODER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Byte.hpp"

namespace obotcha {

class _HuffmanDecoder;
class _Node;

DECLARE_SIMPLE_CLASS(Node) {
public:
   friend class _HuffmanDecoder;

private:
   int symbol;      // terminal nodes have a symbol
   int bits;        // number of bits matched by the node
   List<sp<_Node>> children; // internal nodes have children

   _Node();
   _Node(int symbol, int bits);
   bool isTerminal();
};

DECLARE_SIMPLE_CLASS(HuffmanDecoder) {

public:
    _HuffmanDecoder(List<int> codes, List<byte> lengths);

private:
    static Node buildTree(List<int> codes, List<byte> lengths);
    static void insert(Node root, int symbol, int code, byte length);
};



}

#endif
