////
//// Created by dongl on 23-2-20.
////
//
//#ifndef COMPRESS_BUFFERBASE_H
//#define COMPRESS_BUFFERBASE_H
//#define BUFFER_LEN 10240
//
//class BufferBase {
//
//public:
//    BufferBase() : buffer_index(0) {}
//
//    virtual ~BufferBase() {
//
//    }
//
//    virtual void readBuffer() = 0;
//    virtual void writeBuffer() = 0;
//
//    virtual bool isWritable(unsigned int len) {
//        return buffer_index + len > BUFFER_LEN;
//    }
//
//private:
//    int buffer_index;
//};
//
//
//class MemBuffer : public BufferBase{
//
//public:
//    explicit MemBuffer() : BufferBase() {}
//
//    ~MemBuffer() override {
//
//    }
//
//public:
//    void readBuffer() override {
//
//    }
//
//    void writeBuffer() override {
//
//    }
//
//private:
//    char buffer[];
//};
//
//
//class Buffer {
//private:
//    Buffer() {
//        buffer = (BufferBase *) malloc(sizeof(MemBuffer) + BUFFER_LEN);
//    };
//
//    virtual ~Buffer() {
//        delete buffer;
//    }
//
//private:
//    static BufferBase* buffer;
//
//public:
//    static BufferBase* Instance() {
//        if (buffer) {
//            buffer = new (buffer) MemBuffer();
//        }
//        return buffer;
//    }
//};
//
//BufferBase* Buffer::buffer = nullptr;
//
//
//
//#endif //COMPRESS_BUFFERBASE_H
