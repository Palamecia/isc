#ifndef STACK_H
#define STACK_H

#include <vector>

template<class T>
class Stack : public std::vector<T> {
public:
    inline Stack() {}
    inline ~Stack() {}
    inline void swap(Stack<T> &other) { std::vector<T>::swap(other); } // prevent vector<->Stack swaps
    inline void push(const T &t) { std::vector<T>::push_back(t); }
    inline bool isEmpty() { return std::vector<T>::empty(); }
    T pop();
    T &top();
    const T &top() const;
};

template<class T>
inline T Stack<T>::pop()
{ T t = std::vector<T>::back(); std::vector<T>::pop_back(); return t; }

template<class T>
inline T &Stack<T>::top()
{ return std::vector<T>::back(); }

template<class T>
inline const T &Stack<T>::top() const
{ return std::vector<T>::back(); }

#endif // STACK_H
