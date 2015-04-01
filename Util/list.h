#ifndef LIST_H
#define LIST_H

#include <vector>
#include "typedefs.h"

template<class T> class List : public std::vector<T> {
public:
    List() : std::vector<T>() {}
    List(const List& other) : std::vector<T>() { *this = other; }

    inline void append(const T &t) { std::vector<T>::push_back(t); }
    void append(const List<T> &t) { for (uint i = 0; i < t.size(); ++i) { std::vector<T>::push_back(t[i]); } }

    inline void prepend(const T &t) { std::vector<T>::insert(std::vector<T>::begin(), t); }

    void removeFirst() { std::vector<T>::erase(std::vector<T>::begin()); }
    void removeAt(int i) { std::vector<T>::erase(std::vector<T>::begin() + i); }
    void replace(int i, const T &t) {
        std::vector<T>::erase(std::vector<T>::begin() + i);
        std::vector<T>::insert(std::vector<T>::begin() + i, t);
    }

    inline T& first() { return *std::vector<T>::begin(); }
    const T& first() const { return std::vector<T>::at(0); }

    T& last() { return *(--std::vector<T>::end()); }
    const T& last() const { return std::vector<T>::at(std::vector<T>::count() - 1); }

    inline bool isEmpty() const { return std::vector<T>::empty(); }
    inline bool contains(const T& t) {
        for (uint i = 0; i < std::vector<T>::size(); ++i) {
            if (std::vector<T>::at(i) == t) return true;
        }
        return false;
    }
    inline bool contains(const T& t) const {
        for (uint i = 0; i < std::vector<T>::size(); ++i) {
            if (std::vector<T>::at(i) == t) return true;
        }
        return false;
    }

    List<T>& operator=(const List<T>& other) { std::vector<T>::clear(); append(other); return *this; }
    List<T>& operator<<(const T& item) { std::vector<T>::push_back(item); return *this; }
};

#endif // LIST_H
