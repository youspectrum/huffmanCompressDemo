//
// Created by dongl on 23-2-20.
//

#include <cstring>
#include <bitset>
#include <iostream>
#include "HuffCompress.h"

HuffCompress::HuffCompress() : Compress() {

}

HuffCompress::~HuffCompress() {
    read_.close();
    write_.close();
}

void HuffCompress::pretreatment(const std::string &file_path) {
    open(file_path, read_, [&]() {
        char temp;
        while (read_ >> temp) {
            auto Char = kChar_vWeight_.find(temp);
            if (Char == kChar_vWeight_.end()) {
                kChar_vWeight_.insert(weightPair(temp, 1));
            } else {
                kChar_vWeight_.insert(weightPair(temp, ++(Char->second)));
            }
        }
    });
}

HuffmanTree *HuffCompress::constructionHuffTree() {
    for (const auto &item: kChar_vWeight_) {
        huff_node_.push_back(new HuffmanTree(item.first, item.second, true));
    }
    for (unsigned int i = kChar_vWeight_.size(); i < kChar_vWeight_.size() * 2 - 1; ++i) {
        char c = '0';
        auto huffmanTree = new HuffmanTree(c, -1, false);
        huff_node_.push_back(huffmanTree);
    }

    unsigned int nodeSize = kChar_vWeight_.size() - 1;
    for (int i = 0; i < nodeSize; ++i) {
        HuffmanTree *left = minWeightNode(huff_node_);
        HuffmanTree *right = minWeightNode(huff_node_);

        huff_node_[kChar_vWeight_.size() + i]->setChildNode(treePair(left, right));
        huff_node_[kChar_vWeight_.size() + i]->setWeight(left->getWeight() + left->getWeight());

        left->setParent(huff_node_[kChar_vWeight_.size() + i]);
        right->setParent(huff_node_[kChar_vWeight_.size() + i]);

        if (left->isDataNode()) {
            left->setChildNode(NULL_NODE);
        }
        if (right->isDataNode()) {
            right->setChildNode(NULL_NODE);
        }
    }


    printf("start \n");
    for (const auto &item: huff_node_) {
        printf("data: %c, ptr: %p, parent: %p, left: %p, right: %p, weight: %u\n",
               item->getData(),
               item,
               item->getParent(),
               item->getChildNode().first,
               item->getChildNode().second,
               item->getWeight()
        );
    }
    printf("end \n");
    return huff_node_[huff_node_.size() - 1];
}

std::map<char, std::string> &HuffCompress::buildCoding() {
    HuffmanTree *node_header = huff_node_[huff_node_.size() - 1];

    for (unsigned int i = 0; i < kChar_vWeight_.size(); ++i) {
        std::string coding;
        HuffmanTree *tempNode = huff_node_[i];
        while (tempNode->getParent() != node_header->getParent()) {
            if (tempNode->getParent()->getChildNode().first == tempNode)
                coding.push_back('0');
            if (tempNode->getParent()->getChildNode().second == tempNode)
                coding.push_back('1');
            tempNode = (HuffmanTree *) tempNode->getParent();
        }
        // 反转
        reverse(coding.begin(), coding.end());
        kChar_vCoding_.insert(std::pair<char, std::string>(huff_node_[i]->getData(), coding));
    }

    for (const auto &item: kChar_vCoding_) {
        printf("data: %c,  coding: %s\n", item.first, item.second.c_str());
    }

    return kChar_vCoding_;
}

void HuffCompress::compress(const std::string &file_path) {
    char rbuffer[10240];
    char wbuffer[10240];
    read_.rdbuf()->pubsetbuf(rbuffer, 10240);
    write_.rdbuf()->pubsetbuf(wbuffer, 10240);

    open("/home/dongl/code/test.huffman", write_, [&] {
        std::bitset<8> headerType(00000000);
        std::string headerCoding;
        int index = 7;
        write_ << CHAR_WRITE &headerType;

        /*********************** begin ***************************/
        // 写入头部长度
        unsigned long int sum = 0;
        // 8bit char xxx bit coding 4bit coding len
        for (const auto &item: kChar_vCoding_) {
            sum += sizeof(item.first) * 8 + item.second.size() + 4;
        }

        printf("sum:    %lu\n", sum);
        sum = sum % 8 == 0 ? sum / 8 : sum / 8 + 1;
        printf("sum:    %lu\n", sum);
        // 解压时 告诉 解压程序 有多少个 coding对
        write_ << (unsigned char) kChar_vCoding_.size();
        // 解压时 接下来要读 sum个字节
        write_ << UCHAR_WRITE &sum;
        /************************ end ***************************/

        for (const auto &item: kChar_vCoding_) {
            auto bitSum = BIT item.second.size();
            // 头部每个字符huffman编码的长度 4bit len
            headerCoding += bitSum.to_string().substr(4,8);

            for (const char i: (BIT item.first).to_string()) {
                headerCoding.push_back(i);
                std::cout << i;
            }
            std::cout << std::endl;
            for (const auto &coding_i: item.second) {
                headerCoding.push_back(coding_i);
                std::cout << coding_i;
            }
            std::cout << std::endl;
        }

        for (const auto &item: headerCoding) {
            if (index == 0) {
                if (item == '1') {
                    headerType.set(index);
                }
                write_ << CHAR_WRITE &headerType;
                headerType.reset();
                index = 7;
            } else {
                if (item == '1') {
                    headerType.set(index);
                }
                index--;
            }
        }
        write_ << CHAR_WRITE &headerType;
        headerType.reset();
        write_ << CHAR_WRITE &headerType;

        std::bitset<8> type;
        type.reset();
        char temp;
        unsigned int bit_max_index = 8 - 1;
        unsigned int bit_index = 0;

        open(file_path, read_, [&]() {
            while (read_ >> temp) {
                auto coding = kChar_vCoding_.find(temp)->second;
                for (char i: coding) {
                    if (bit_index == bit_max_index) {
                        if (i == '1') {
                            type.set(bit_max_index - bit_index);
                        }

                        char s = CHAR_WRITE &type;
                        write_ << s;
                        type.reset();
                        bit_index = 0;

                    } else {
                        if (i == '1') {
                            type.set(bit_max_index - bit_index);
                        }

                        bit_index++;
                    }
                }
            }
        });

        char s = CHAR_WRITE &type;
        write_ << s;
        write_.close();
    });
}


void HuffCompress::open(const std::string& file_path, std::fstream& stream, const OpenEvent& openEvent) {
    if (&stream == &this->read_) {
        stream.open(file_path.c_str(), std::ios::in | std::ios::binary);
    } else if (&stream == &this->write_) {
        stream.open(file_path.c_str(), std::ios::out | std::ios::binary | std::ios::app);
    }

    if (!stream.is_open()) {
        printf("fs.is_open() = %s, notnull\n", file_path.c_str());
        exit(1);
    } else {
        // 取消 忽略流中的空白字符
        stream.unsetf(std::ios::skipws);
        printf("fs.is_open() = %s, true\n", file_path.c_str());
    }

    openEvent();

    stream.close();
}


HuffmanTree *HuffCompress::minWeightNode(const std::vector<HuffmanTree *> &huffNode) {
    unsigned int minWeight = 4294967295;
    static std::vector<HuffmanTree *> filter;
    HuffmanTree *min;

    for (const auto &item: huffNode) {
        if (std::find(filter.begin(), filter.end(), item) == filter.end() && minWeight > item->getWeight()) {
            minWeight = item->getWeight();
            min = item;
        }
    }

    filter.push_back(min);
    return min;
}















