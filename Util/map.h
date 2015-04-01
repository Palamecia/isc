#ifndef MAP_H
#define MAP_H

#include <map>

template<typename _Key,
         typename _Tp,
         typename _Compare = std::less<_Key>,
         typename _Alloc = std::allocator<std::pair<const _Key, _Tp> > >
class Map : public std::map<_Key, _Tp, _Compare, _Alloc> {};

#endif // MAP_H
