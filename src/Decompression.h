//
// Created by dongl on 23-2-24.
//

#ifndef COMPRESS_DECOMPRESSION_H
#define COMPRESS_DECOMPRESSION_H
#include <string>
#include <bitset>
#include <map>
#include <fstream>
#include <functional>

#define pairCharString std::pair<char, std::string>
#define pairStringChar std::pair<std::string, char>
#define HEADER_BEGIN std::bitset<8>(00000000)
#define HEADER_END std::bitset<8>(00000000)
#define BIT_8 (std::bitset<8>)
#define TURN_CHAR *(char *)

typedef std::function<void()> OpenEvent;

class Decompression {

public:
    Decompression() {}

    virtual ~Decompression() {

    }

    virtual void decompression(const std::string &file_path) = 0;

protected:
    std::fstream read_;
    std::fstream write_;
    std::map<char, std::string> kChar_vCoding;
    std::map<std::string, char> kCoding_vChar;
};

#endif //COMPRESS_DECOMPRESSION_H
