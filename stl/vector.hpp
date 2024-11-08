#ifndef vector_h
#define vector_h
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <stdexcept>

namespace vai {

    template <typename T>
    class vector {

    public:
        using data_t = T;

        vector():
            arr_(nullptr),
            capacity_(0),
            size_(0) {
            std::cout << __PRETTY_FUNCTION__ << __LINE__ << std::endl;
        }

        // vector<int> a(1)
        explicit vector(size_t n):
            capacity_(n),
            size_(n),
            arr_(new data_t[n]) {
            std::cout << __PRETTY_FUNCTION__ << __LINE__ << std::endl;
            for (size_t i = 0; i < n; ++i) {
                new (arr_ + i) data_t();
            }
        }

        // vector<int>(3,5)
        explicit vector(size_t n, const T& val):
            capacity_(n),
            size_(n),
            arr_(new data_t[n]) {
            std::cout << __PRETTY_FUNCTION__ << __LINE__ << std::endl;
            for (size_t i = 0; i < n; ++i) {
                new (arr_ + i) data_t(val);
            }
        }

        // vector<int> v={1,2,3,4}
        vector(std::initializer_list<T> l):
            capacity_(l.size()),
            size_(l.size()),
            arr_(new data_t[capacity_]) {
            for (size_t i = 0; i < size_; ++i) {
                new (arr_[i]) data_t(l.begin() + i);
            }
        }

        // copy constructor
        vector(const vector<T>& temp):
            capacity_(temp.capacity_),
            size_(temp.size_),
            arr_(new data_t[temp.capacity_]) {
            std::cout << __PRETTY_FUNCTION__ << __LINE__ << std::endl;
            for (size_t i = 0; i < size_; ++i) {
                new (arr_ + i) data_t(temp.arr_[i]);
            }
        }

        // move constructor
        vector(vector<T>&& temp) noexcept:
            arr_(temp.arr_),
            capacity_(temp.capacity_),
            size_(temp.size_) {
            std::cout << __PRETTY_FUNCTION__ << __LINE__ << std::endl;
            temp.arr_      = nullptr;
            temp.capacity_ = 0;
            temp.size_     = 0;
        }

        ~vector() {
            for (size_t i = 0; i < size_; ++i) {
                arr_[i].~data_t();
            }
            std::cout << __PRETTY_FUNCTION__ << __LINE__ << std::endl;
            delete[] arr_;
        }

        vector<T>& operator=(const vector<T>& other) {
            if (this == &other) {
                return *this;
            }
            for (size_t i = 0; i < capacity_; ++i) {
                arr_[i]->~T();
            }
            delete[] reinterpret_cast<char*>(arr_);
            capacity_ = other.capacity_;
            size_     = other.size_;
            arr_      = reinterpret_cast<T*>(new char[capacity_ * sizeof(T)]);
            for (size_t i = 0; i < size_; ++i) {
                new (arr_ + i) T(other.arr_[i]);
            }
            return *this;
        }

        vector& operator=(vector&& other) {
            arr_      = other.arr_;
            capacity_ = other.capacity_;
            size_     = other.size_;
            delete[] other.arr_;
            other.capacity_ = 0;
            other.size_     = 0;
            return *this;
        }

        bool operator==(const vector<T>& v) const {
            if (size_ != v.size_) {
                return false;
            }
            for (size_t i = 0; i < size_; i++) {
                if (v.arr_[i] != arr_[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator!=(const vector<T>& v) const {
            return !(*this == v);
        }

        data_t& operator[](size_t index) const noexcept {
            return arr_[index];
        }

        void clear() {
            for (size_t i = 0; i < size_; ++i) {
                arr_[i].~T();
            }
            delete[] reinterpret_cast<char*>(arr_);
        }

        void erase(size_t idx) {
            if (idx >= size_) {
                return;
            }
            for (size_t i = idx; i < size_ - 1; ++i) {
                arr_[i] = arr_[i + 1];
            }
            arr_[size_ - 1].~T();
            --size_;
        }

        void erase(size_t first, size_t last) {
            if (first >= size_ || last >= size_ || first > last) {
                return;
            }
            size_t count = last - first + 1;
            for (size_t i = first; i < size_ - count; ++i) {
                arr_[i] = arr_[i + count];
            }
            for (size_t i = 0; i < count; ++i) {
                arr_[size_ - i - 1].~T();
            }
            size_ -= count;
        }

        void push_back(const data_t& data) {

            if (size_ == capacity_) {
                resize();
            }
            std::cout << __PRETTY_FUNCTION__ << __LINE__ << std::endl;
            new (arr_ + size_) data_t(data);
            ++size_;
        }

        void push_back(data_t&& data) {
            if (size_ == capacity_) {
                resize();
            }
            std::cout << __PRETTY_FUNCTION__ << __LINE__ << std::endl;
            new (arr_ + size_) data_t(std::move(data));
            ++size_;
        }

        template <typename... Args>
        void emplace_back(Args&&... args) {
            if (size_ == capacity_) {
                resize();
            }
            std::cout << __PRETTY_FUNCTION__ << __LINE__ << std::endl;
            new (arr_ + size_) data_t(std::forward<Args>(args)...);
            ++size_;
        }

        void resize() {
            if(capacity_==0) {
                capacity_ = 1;
            }else {
                capacity_ *= 2;
            }
            void *raw_memory=operator new[](capacity_*sizeof(T));
            T* temp=static_cast<T*>(raw_memory);
            for (size_t i = 0; i < size_; i++) {
                new (temp + i) data_t(arr_[i]);
                arr_[i].~T();
            }
            operator delete[] (arr_);
            arr_ = temp;
        }

        void pop_back() {
            if (size_ == 0) {
                return;
            }
            arr_[size_ - 1].~T();
            --size_;
        }

        data_t& at(size_t idx) {
            return arr_[idx];
        }

        const data_t& at(size_t idx) const {
            return arr_[idx];
        }

        const data_t& front() const {
            return arr_[0];
        }

        const data_t& back() const {
            if (size_ == 0) {
                throw std::out_of_range("vector is empty");
            }
            return arr_[size_ - 1];
        }

        size_t size() const {
            return size_;
        }

    private:
        data_t* arr_;

        std::size_t capacity_;

        std::size_t size_;
    };
}
#endif