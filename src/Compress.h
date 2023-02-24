//
// Created by dongl on 23-2-20.
//

#ifndef COMPRESS_COMPRESS_H
#define COMPRESS_COMPRESS_H

#include <fstream>
#include <map>

class Compress {
public:
    using weightPair = std::pair<char, unsigned int>;

public:
    Compress() {}

    virtual ~Compress() {}

    // 单文件压缩
    virtual void pretreatment(const std::string &file_path) = 0;
    virtual void compress(const std::string &file_path) = 0;

public:
    const std::map<char, unsigned int> &getCharWeight() const {
        return kChar_vWeight_;
    }

protected:
    std::fstream read_;
    std::fstream write_;
    std::map<char, unsigned int> kChar_vWeight_;
};


#endif //COMPRESS_COMPRESS_H
