#include <iostream>
#include <utility>
#include <stdexcept>
#include <algorithm>

template<typename T>
class DynamicArray{
    T* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t newCapacity) {
        T* newData = new T[newCapacity];

        for(size_t i = 0; i < size_; ++i) {
            newData[i] = std::move(data_[i]);
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    public:
    // ===== Constructors & Destructor =====

    DynamicArray()
        : data_(nullptr), size_(0), capacity_(0) {}

    ~DynamicArray() {
        delete[] data_;
    }

    // Copy constructor
    DynamicArray(const DynamicArray& other) 
        : size_(other.size_), capacity_(other.capacity_) {
            data_ = new T[capacity_];
            for(size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }

    // Copy assignment (exception-safe)
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;

        // Allocate new memory first
        T* newData = new T[other.capacity_];
        for(size_t i =0; i < other.size_; ++i) {
            newData[i] = other.data_[i];
        }

        // Only modify state after successful allocation
        delete[] data_;
        data_ = newData;
        size_ = other.size_;
        capacity_ = other.capacity_;

        return *this;
    }

    // Move constructor
    DynamicArray(DynamicArray&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }


    // Move assignment
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

    // ===== Capacity =====

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
    
    void shrink_to_fit() {
        if(size_ < capacity_) {
            if(size_ == 0) {
                delete[] data_;
                data_ = nullptr;
                capacity_ = 0;
            } else {
                reallocate(size_);
            }
        }
    }

    void clear() {
        for(size_t i = 0; i < size_; ++i) {
            data_[i].~T();
        }
        size_ = 0;
    }

    // ===== Element Access =====

    T& operator[](size_t index) {
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& at (size_t index) const {
        if(index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    T& front() {
        return data_[0];
    }

    const T& front() const{
        return data_[0];
    }

    T& back() {
        return data_[size_ - 1];
    }

    const T& back() const {
        return data_[size_ - 1];
    }

    T* data() noexcept {
        return data_;
    }

    const T* data() const noexcept {
        return data_;
    }

    // ===== Modifiers =====
    void push_back(const T& value) {
        if(size_ == capacity_) {
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(newCapacity);
        }

        data_[size_] = value;
        ++size_;
    }

    void push_back(T&& value) {
        if(size_ == capacity_) {
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(newCapacity);
        }

        data_[size_] = std::move(value);
        ++size_;
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if(size_ == capacity_) {
            size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(newCapacity);
        }

        new(&data_[size_]) T(std::forward<Args>(args)...);
        size_++;
    }

    void pop_back() {
        if(size_ > 0) {
            --size_;
        }
    }

    // ===== Iterators =====

    T* begin() noexcept {
        return data_;
    }

    T* end() noexcept {
        return data_ + size_;
    }

    const T* begin() const noexcept {
        return data_;
    }

    const T* end() const noexcept {
        return data_ + size_;
    }

    const T* cbegin() const noexcept {
        return data_;
    }

    const T* cend() const noexcept {
        return data_ + size_;
    }
};

// ======== Testing ========

int main() {
    DynamicArray<int> arr;

    std::cout << "=== Push Back Test ===\n";
    for (int i = 1; i <= 10; ++i) {
        arr.push_back(i * 10);
        std::cout << "Size: " << arr.size()
                  << ", Capacity: " << arr.capacity() << "\n";
    }

    std::cout << "\n=== Contents ===\n";
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    std::cout << "\n=== Front/Back Access ===\n";
    std::cout << "Front: " << arr.front() << "\n";
    std::cout << "Back: " << arr.back() << "\n";

    std::cout << "\n=== Bounds-Checked Access (at) ===\n";
    try {
        std::cout << "arr.at(5) = " << arr.at(5) << "\n";
        std::cout << "arr.at(100) = " << arr.at(100) << "\n";  // Should throw
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << "\n";
    }

    std::cout << "\n=== Copy Test ===\n";
    DynamicArray<int> copy = arr;
    copy.push_back(999);

    std::cout << "Original size: " << arr.size() << "\n";
    std::cout << "Copy size: " << copy.size() << "\n";

    std::cout << "\n=== Move Test ===\n";
    DynamicArray<int> moved = std::move(arr);
    std::cout << "Moved size: " << moved.size() << "\n";
    std::cout << "Original size after move: " << arr.size() << "\n";

    std::cout << "\n=== Pop Back ===\n";
    moved.pop_back();
    for (int x : moved) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    std::cout << "\n=== Emplace Back Test ===\n";
    DynamicArray<std::string> strings;
    strings.emplace_back("Hello");
    strings.emplace_back("World");
    for (const auto& s : strings) {
        std::cout << s << " ";
    }
    std::cout << "\n";

    std::cout << "\n=== Shrink to Fit ===\n";
    moved.reserve(100);
    std::cout << "Before shrink - Size: " << moved.size() 
              << ", Capacity: " << moved.capacity() << "\n";
    moved.shrink_to_fit();
    std::cout << "After shrink - Size: " << moved.size() 
              << ", Capacity: " << moved.capacity() << "\n";

    std::cout << "\n=== Clear ===\n";
    moved.clear();
    std::cout << "Empty: " << std::boolalpha << moved.empty() << "\n";

    return 0;
}