#include <iostream>
#include <bitset>
#include "huffman/HuffmanTree.h"
#include "huffman/HuffCompress.h"
#include "huffman/HuffDecompression.h"

int main() {

    auto compress = new HuffCompress();
    compress->pretreatment("/home/dongl/code/test.txt");
    compress->constructionHuffTree();
    compress->buildCoding();
    compress->compress("/home/dongl/code/test.txt");

//    auto decompression = new HuffDecompression();
//    decompression->decompression("/home/dongl/code/test.huffman");
    return 0;
}
