#pragma once
#include <vector>
#include <stdexcept>

template<typename T>
class KHeap {
private:
    std::vector<T> data;
    size_t k;

    size_t parent(size_t i) const {
        return i == 0 ? 0 : (i - 1) / k;
    }

    size_t firstChild(size_t i) const {
        return k * i + 1;
    }

    void siftDown(size_t i) {
        size_t minChild;
        while ((minChild = firstChild(i)) < data.size()) {
            size_t lastChild = std::min(minChild + k, data.size());
            for (size_t j = minChild + 1; j < lastChild; j++) {
                if (data[j] < data[minChild]) {
                    minChild = j;
                }
            }
            if (data[i] <= data[minChild]) {
                break;
            }
            std::swap(data[i], data[minChild]);
            i = minChild;
        }
    }

    void siftUp(size_t i) {
        while (i > 0 && data[parent(i)] > data[i]) {
            std::swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }

public:
    KHeap(size_t k) : k(k) {}
    
    void heapify(std::vector<T>& arr) {
        data = arr;
        for (int i = data.size() / k - 1; i >= 0; i--) {
            siftDown(i);
        }
        arr = data;
    }

    void insert(const T& value) {
        data.push_back(value);
        siftUp(data.size() - 1);
    }

    T extractMin() {
        if (data.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        T min = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) {
            siftDown(0);
        }
        return min;
    }

    const T& peekMin() const {
        if (data.empty()) {
            throw std::runtime_error("Heap is empty");
        }
        return data[0];
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }
};

