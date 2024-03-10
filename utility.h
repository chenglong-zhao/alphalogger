#ifndef Utility_HEADER_
#define Utility_HEADER_


template <class T>
class RingBuffer {
  public:
    RingBuffer()
      : size_(128),
        front_(0),
        rear_(0){
    }

    ~RingBuffer(){
        delete [] data_;
    }

    void Init(){
      data_ = new T[size_];
    }
   
    void Push(T elemt){
        data_[rear_] = elemt;
        rear_ = (rear_+1)%size_;
    }

    T Pop(){
        T tmp = data_[front_];
        front_ = (front_+1)%size_;
        return tmp;
    }

    bool isEmpty() const{
        return front_ == rear_;
    };

    bool isFull() const{
        return (front_ + 1)%size_ == rear_;
    }

  private:
    int front_;
    int rear_;
    unsigned int size_;
    T* data_;
    std:: thread flushthread;
};

#endif 