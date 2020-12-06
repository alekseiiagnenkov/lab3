#pragma once

#include <iostream>
#include <vector>
#include <list>

using namespace std;

template<class T>
class container {
private:
    int size_;
    T *data_;

    void resize(int index, int resize_size);

    int findElement(T &element);

public:

    container() : size_(0), data_(nullptr) {}

    container(const container &other);

    container(const std::vector<T> &other);

    container(const T other[]);

    container(const std::initializer_list<T> &other);

    ~container() { delete[] data_; }

    T &operator[](int n);

    const T &operator[](int n) const;

    container &operator=(const container &vec);

    bool operator==(const container &vec);

    container operator-(const container &vec);

    container operator+(const container &vec);

    void push_back(const T &it);

    void pop_back();

    void erase(int index);

    void clear();

    int size() const { return size_; }
};

template<class T>
container<T>::container(const container<T> &other) {
    this->size_ = 0;
    if (this->data_ != nullptr)
        this->data_ = nullptr;
    for (int i = 0; i < other.size_; i++) {
        this->push_back(other.data_[i]);
    }
}

template<class T>
container<T>::container(const std::vector<T> &other) {
    this->size_ = 0;
    if (this->data_ != nullptr)
        this->data_ = nullptr;
    for (int i = 0; i < other.size(); i++) {
        this->push_back(other[i]);
    }
}

template<class T>
container<T>::container(const std::initializer_list<T> &other) {

    this->size_ = 0;
    if (this->data_ != nullptr)
        this->data_ = nullptr;
    this->size_ = other.size();
    this->data_ = new T[other.size()];
    std::copy(other.begin(), other.end(), this->data_);
}

template<class T>
container<T>::container(const T other[]) {
    this->size_ = 0;
    if (this->data_ != nullptr)
        this->data_ = nullptr;
    for (int i = 0; i < sizeof(other); i++) {
        this->push_back(other[i]);
    }
}


template<class T>
T &container<T>::operator[](int n) {
    if (n < 0 || n > size_)
        throw std::exception();
    else
        return this->data_[n];
}

template<class T>
const T &container<T>::operator[](int n) const {
    if (n < 0 || n > size_)
        throw std::exception();
    else
        return this->data_[n];
}

template<class T>
container<T> &container<T>::operator=(const container<T> &vec) {
    if (data_ == nullptr)
        delete[] data_;
    size_ = vec.size();
    data_ = new T[size_];
    if (vec.data_ != nullptr) {
        for (int i = 0; i < vec.size_; ++i) {
            data_[i] = vec.data_[i];
        }
    }
    return *this;
}

template<class T>
bool container<T>::operator==(const container<T> &vec) {
    if (this->size_ == vec.size_) {
        for (int i = 0; i < this->size_; i++) {
            if (this->data_[i] != vec.data_[i])
                return false;
        }
        return true;
    } else
        return false;
}

template<class T>
container<T> container<T>::operator-(const container<T> &vec) {
    container<T> result(*this);
    for (int i = 0; i < vec.size_; i++) {
        if (result.findElement(vec.data_[i]) != -1)
            result.erase(result.findElement(vec.data_[i]));
    }
    return result;
}

template<class T>
container<T> container<T>::operator+(const container<T> &vec) {
    container<T> result;
    for (int i = 0; i < vec.size_; i++) {
        if (result.findElement(vec.data_[i]) == -1)
            result.push_back(vec.data_[i]);
    }
    for (int i = 0; i < this->size_; i++) {
        if (result.findElement(this->data_[i]) == -1)
            result.push_back(this->data_[i]);
    }
    return result;
}

template<class T>
void container<T>::resize(int index, int resize_size) {
    T *p = new T[resize_size];
    if (data_ != nullptr) {
        for (int i = 0, j = 0; i < size_; i++, j++) {
            p[j] = data_[i];
            if (index == i)
                j--;
        }
        delete[] data_;
    }
    data_ = p;
    size_ = resize_size;
}

template<class T>
int container<T>::findElement(T &element) {
    for (int i = 0; i < this->size_; i++) {
        if (this->data_[i] == element) {
            return i;
        }
    }
    return -1;
}

template<class T>
void container<T>::push_back(const T &it) {
    resize(size_ + 2, size_ + 1);
    data_[size_ - 1] = it;
}

template<class T>
void container<T>::erase(int index) {
    if (size_ > 0 && (index < size_ && index >= 0))
        resize(index, size_ - 1);
    else
        throw std::exception();
}

template<class T>
void container<T>::pop_back() {
    if (size_ > 0)
        resize(size_ - 1, size_ - 1);
    else
        throw std::exception();
}

template<class T>
void container<T>::clear() {
    if (this->data_ != nullptr)
        delete[] this->data_;
    this->size_ = 0;
}




