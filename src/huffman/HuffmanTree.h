//
// Created by dongl on 23-2-20.
//

#ifndef COMPRESS_HUFFMANTREE_H
#define COMPRESS_HUFFMANTREE_H

#include "tree/Tree.h"

class HuffmanTree : public Tree {
public:
    HuffmanTree(char data, unsigned int weight, bool dataNode) : Tree(data), weight_(weight), data_node_(dataNode) {}

    virtual ~HuffmanTree() {

    }

    void setChildNode(std::pair<Tree *, Tree *> pair) override {
        Tree::setChildNode(pair);
    }

    void setParent(Tree *parent) override {
        Tree::setParent(parent);
    }


    unsigned int getWeight() const {
        return weight_;
    }

    void setWeight(unsigned int weight) {
        weight_ = weight;
    }

    bool isDataNode() const {
        return data_node_;
    }

private:
    unsigned int weight_;
    bool data_node_;
};

#endif //COMPRESS_HUFFMANTREE_H
