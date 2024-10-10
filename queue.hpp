#ifndef QUEUEARRAY_HPP
#define QUEUEARRAY_HPP

#include <cstddef>
#include <utility>

template <class T>
class QueueArray {
public:
  ~QueueArray()
  {
    delete[] data_;
  }
  QueueArray(size_t size) :
    head_(0),
    tail_(0),
    maxSize_(size),
    isFull_(false)
  {
    if (size == 0)
    {
      throw;
    }
    data_ = new T[maxSize_];
  }
  void enQueue(const T& e)
  {
    if (isFull_)
    {
      throw ;
    }
    if ((head_ == 0 && tail_ == maxSize_ - 1) || (tail_ == head_ - 1))
    {
      isFull_ = true;
      data_[tail_] = e;
    }
    else
    {
      data_[tail_] = e;
      tail_ = (tail_ + 1) % maxSize_;
    }
  }
  T deQueue()
  {
    if (isEmpty())
    {
      throw;
    }
    T res = std::move(data_[head_]);
    if (isFull_)
    {
      tail_ = (tail_ + 1) % maxSize_;
      isFull_ = false;
    }
    head_ = (head_ + 1) % maxSize_;
    return res;
  }
  virtual bool isEmpty() const
  {
    return head_ == tail_;
  }
private:
  T* data_;
  size_t maxSize_;
  size_t head_;
  size_t tail_;
  bool isFull_;
};
#endif
