#pragma once  // Copyright 2025 wiserin
#include <vector>
#include <utility>

#include <logging/schemas.hpp>


struct LogComparator {
    bool operator()(const Log& a, const Log& b) const;
};


template<typename T, typename Comparator>
class WorkerQueue {
    std::vector<T> heap;
    Comparator comparator;

 public:
    WorkerQueue() {
        heap.reserve(128);
    }

    void Push(T&& log) {
        heap.push_back(std::move(log));
        std::push_heap(heap.begin(), heap.end(), comparator);
    }

    T Pop() {
        std::pop_heap(heap.begin(), heap.end(), comparator);
        T top = std::move(heap.back());
        heap.pop_back();
        return top;
    }

    bool IsEmpty() const { return heap.empty(); }
};
