#ifndef __OBOTCHA_HTTP_V2_HUFFMAN_DECODER_HPP__
#define __OBOTCHA_HTTP_V2_HUFFMAN_DECODER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Byte.hpp"
#include "List.hpp"
#include "ByteArray.hpp"

namespace obotcha {

class _HuffmanDecoder;
class _Node;

DECLARE_SIMPLE_CLASS(Node) {

friend class _HuffmanDecoder;
public:
   _Node();
   _Node(int symbol, int bits);
   bool isTerminal();

private:
   int symbol;      // terminal nodes have a symbol
   int bits;        // number of bits matched by the node
   List<sp<_Node>> children; // internal nodes have children
};

DECLARE_SIMPLE_CLASS(HuffmanDecoder) {

public:
    _HuffmanDecoder(List<int> codes, List<byte> lengths);
    ByteArray decode(ByteArray buf);

private:
    static Node buildTree(List<int> codes, List<byte> lengths);
    static void insert(Node root, int symbol, int code, byte length);

    Node root;
};



}

#endif
