#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpV2HuffmanDecoder.hpp"
#include "IllegalStateException.hpp"
#include "IllegalArgumentException.hpp"
#include "ByteArrayWriter.hpp"
#include "Math.hpp"
#include "HttpV2HpackUtil.hpp"

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
    if (codes->size() != 257 || codes->size() != lengths->size()) {
      throw IllegalArgumentException("invalid Huffman coding");
    }

    root = buildTree(codes, lengths);
}

Node _HuffmanDecoder::buildTree(List<int>codes, List<byte> lengths) {
    
    Node root = createNode();
    for (int i = 0; i < codes->size(); i++) {
        insert(root, i, codes[i], lengths[i]);
    }
    return root;
}

void _HuffmanDecoder::insert(Node root, int symbol, int code, byte length) {
    // traverse tree using the most significant bytes of code

    Node current = root;
    while (length > 8) {
        if (current->isTerminal()) {
            throw IllegalStateException("invalid Huffman code: prefix not unique");
        }
        length -= 8;
        int i = (st(Math)::abs(code) >> length) & 0xFF;
        if (current->children[i] == nullptr) {
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
}


ByteArray _HuffmanDecoder::decode(ByteArray buf) {

    ByteArrayWriter baos = createByteArrayWriter();

    Node node = root;
    int current = 0;
    int bits = 0;
    for (int i = 0; i < buf->size(); i++) {
        int b = buf->at(i) & 0xFF;
        current = (current << 8) | b;
        bits += 8;
        while (bits >= 8) {
            int c = (st(Math)::abs(current) >> (bits - 8)) & 0xFF;
            node = node->children[c];
            bits -= node->bits;
            if (node->isTerminal()) {
                if (node->symbol == st(HttpV2HpackUtil)::HUFFMAN_EOS) {
                    throw IllegalStateException("EOS Decoded");
                }
                baos->writeInt(node->symbol);
                node = root;
            }
        }
    }

    while (bits > 0) {
        int c = (current << (8 - bits)) & 0xFF;
        node = node->children[c];
        if(node->isTerminal() && node->bits <= bits) {
            bits -= node->bits;
            baos->writeInt(node->symbol);
            node = root;
        } else {
            break;
        }
    }

    // Section 5.2. String Literal Representation
    // Padding not corresponding to the most significant bits of the code
    // for the EOS symbol (0xFF) MUST be treated as a decoding error.
    int mask = (1 << bits) - 1;
    if ((current & mask) != mask) {
        throw IllegalStateException("Invalid Padding");
    }

    return baos->getByteArray();

}

}
