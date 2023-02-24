//
// Created by dongl on 23-2-20.
//

#ifndef COMPRESS_TREE_H
#define COMPRESS_TREE_H

#include <utility>

#define treePair std::pair<Tree*, Tree*>
#define NULL_NODE treePair(nullptr, nullptr)

struct Tree {
public:
    Tree(char data) : data_(data) {}

    virtual void setChildNode(std::pair<Tree*, Tree*> pair) {
        left_ = pair.first;
        right_ = pair.second;
    }

    virtual void setParent(Tree* parent) {
        parent_ = parent;
    }

    Tree *getParent() const {
        return parent_;
    }

    treePair getChildNode() const {
        return treePair(left_, right_);
    }

    char getData() const {
        return data_;
    }

protected:
    Tree* parent_;
    Tree* left_;
    Tree* right_;
    char data_;
};

#endif //COMPRESS_TREE_H
