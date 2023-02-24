//
// Created by dongl on 23-2-24.
//

#include <iostream>
#include <cstring>
#include <valarray>
#include <queue>
#include "HuffDecompression.h"

void HuffDecompression::decompression(const std::string &file_path) {
    char temp;
    HuffDecompression::open(file_path, read_, [&] () {
        std::string headerChar;
        std::string header;

        /// 头校验
        read_ >> temp;
        std::cout << "temp: " << (std::bitset<8>)temp << std::endl;
        if (BIT_8 temp != HEADER_BEGIN) {
            return;
        }

        /// coding对数量 sum
        read_ >> temp;
        int codingPairLen = (int) (unsigned char) temp;
        printf("codingPairLen, %d\n", codingPairLen);
        /// 接下来要读 多少个字节
        read_ >> temp;
        int headerLen = (int)  (unsigned char) temp;
        headerLen = 160;

        for (int i = 0; i < headerLen; ++i) {
            read_ >> temp;
            headerChar += temp;
        }
        printf("headerLen, %d\n", headerLen);
        /// 字节内01 存到 string  是为 header bit流
        for (const auto &item: headerChar) {
            header += (BIT_8 item).to_string();
        }
        printf("headerCoding, %s\n", header.c_str());
//        std::queue<char> headerCoding;
//        for (int i = header.size(); i >= 0; --i) {
//            headerCoding.push(header[i]);
//        }


        /// 循环 编码对 数量 的次数  生成 header解压编码
        for (int i = 0; i < codingPairLen; ++i) {
            // 读 coding len
            std::string codingLen;
            for (int j = 0; j < 4; ++j) {
                char front = header.front();
                codingLen += front;
                header.erase(std::find(header.begin(), header.end(), front));
            }
            int len = binary2to10(codingLen);
            printf("headerCoding, %s\n", codingLen.c_str());
            printf("len: %d, ", len);

            // 读char
            std::string Char;
            for (int j = 0; j < 8; ++j) {
                char front = header.front();
                Char += front;
                header.erase(std::find(header.begin(), header.end(), front));
            }
            char kChar = (char )binary2to10(Char);
            printf("kChar: %c, ", kChar);

            // 读coding
            std::string vCoding;
            for (int j = 0; j < len; ++j) {
                char front = header.front();
                vCoding += front;
                header.erase(std::find(header.begin(), header.end(), front));
            }
            printf("vCoding: %s, \n", vCoding.c_str());

            printf("header: %s \n", header.c_str());
            kChar_vCoding.insert(pairCharString(kChar, vCoding));
            kCoding_vChar.insert(pairStringChar(vCoding, kChar));
        }

        /// header end
        read_ >> temp;
        if (BIT_8 temp != HEADER_END) {
            return;
        }

        /// body data
        std::string bodyDataStream;
        char bodyData;
        while (read_ >> bodyData) {
            for (const auto &item: (BIT_8 bodyData).to_string()) {
                bodyDataStream += item;
                auto originalText = kCoding_vChar.find(bodyDataStream);
                if (originalText != kCoding_vChar.end()) {
                    printf("%c", originalText->second);
                    bodyDataStream.clear();
                }
            }
        }
    });
}

void HuffDecompression::open(const std::string& file_path, std::fstream& stream, const OpenEvent& openEvent) {
    stream.open(file_path.c_str(), std::ios::in | std::ios::binary);
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

int HuffDecompression::binary2to10(const std::string& binary) {

    int decimalNumber = 0, i = 0, remainder;
    long long n = atoi(binary.c_str());
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }

    return decimalNumber;
}


