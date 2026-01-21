#include <iostream>
#include <utility>
#include <stdexcept>

using namespace std;

template<typename T>
class DynamicArray{
    T* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t newCapacity) {
        T* newData = new T[newCapacity];

        for(size_t i = 0; i < size_; ++i) {
            newData[i] = move(data_[i]);
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    public:

    DynamicArray()
        : data_(nullptr), size_(0), capacity_(0) {}

    ~DynamicArray() {
        delete[] data_;
    }

    DynamicArray(const DynamicArray& other) 
        : size_(other.size_), capacity_(other.capacity_) {

            data_ = new T[capacity_];
            for(size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }

    DynamicArray(DynamicArray&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
        return *this;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if(this == &other) return *this;

        delete[] data_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void reserve(size_t newCapacity) {
        if(newCapacity > capacity_) {
            reallocate(newCapacity);
        }
    }

    void clear() {
        size_ = 0;
    }

    T& operator[](size_t index) {
        if (index >= size_) throw out_of_range("Index out of range");
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) throw out_of_range("Index out of range");
        return data_[index];
    }

    void push_back(const T& value) {
        if(size_ == capacity_) {
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(newCapacity);
        }

        data_[size_] = value;
        size_++;
    }

    void push_back(T&& value) {
        if(size_ == capacity_) {
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(newCapacity);
        }

        data_[size_] = move(value);
        size_++;
    }

    void pop_back() {
        if(size_ == 0) return;
        size_--;
    }
    T* begin() {
        return data_;
    }

    T* end() {
        return data_ + size_;
    }

    const T* begin() const {
        return data_;
    }

    const T* end() const {
        return data_ + size_;
    }
};

int main() {
    DynamicArray<int> arr;

    cout << "Pushing values...\n";
    for (int i = 1; i <= 10; ++i) {
        arr.push_back(i * 10);
        cout << "Size: " << arr.size() << ", Capacity: " << arr.capacity() << endl;
    }

    cout << "\nContents:\n"; 
    for(int x : arr) {
        cout << x << " ";
    }
    cout << '\n';

    cout << "\nCopy test...\n";
    DynamicArray<int> copy = arr;
    copy.push_back(999);

    cout << "Original size: " << arr.size() << endl;
    cout << "Copy size: " << copy.size() << endl;

    cout << "\nMove test...\n";
    DynamicArray<int> moved = move(arr);
    cout << "Moved size: " << moved.size() << endl;
    cout << "Original size after move: " << arr.size() << endl;

    cout << "\nPop back...\n";
    moved.pop_back();
    for(int x : moved) {
        cout << x << " ";
    }
    cout << "\n";

    cout << "\nClear...\n";
    moved.clear();
    cout << "Empty: " << moved.empty() << endl;

    return 0;
}