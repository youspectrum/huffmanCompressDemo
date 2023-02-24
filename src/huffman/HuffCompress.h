//
// Created by dongl on 23-2-20.
//

#ifndef COMPRESS_HUFFCOMPRESS_H
#define COMPRESS_HUFFCOMPRESS_H

#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>
#include "../Compress.h"
#include "HuffmanTree.h"
#include "buffer/BufferBase.h"

#define CHAR_WRITE *(char* )
#define UCHAR_WRITE *(unsigned char* )
#define BIT (std::bitset<8>)

typedef std::function<void()> OpenEvent;

class HuffCompress : public Compress {
public:
    HuffCompress();

    ~HuffCompress() override;

    // 单文件预处理
    void pretreatment(const std::string &file_path) override;

    HuffmanTree* constructionHuffTree();

    std::map<char, std::string>& buildCoding();

    void compress(const std::string &file_path) override;
private:
    HuffmanTree* minWeightNode(const std::vector<HuffmanTree *>& huffNode);
    void open(const std::string &file_path, std::fstream& stream, const OpenEvent& openEvent);

private:
    std::vector<HuffmanTree *> huff_node_;
    std::map<char, std::string> kChar_vCoding_;
};


#endif //COMPRESS_HUFFCOMPRESS_H
