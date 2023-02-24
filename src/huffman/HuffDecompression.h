//
// Created by dongl on 23-2-24.
//

#ifndef COMPRESS_HUFFDECOMPRESSION_H
#define COMPRESS_HUFFDECOMPRESSION_H

#include "../Decompression.h"

class HuffDecompression : public Decompression {
public:

    void decompression(const std::string &file_path) override;
private:
    void open(const std::string& file_path, std::fstream& stream, const OpenEvent& openEvent);
    int binary2to10(const std::string& binary);
};

#endif //COMPRESS_HUFFDECOMPRESSION_H
