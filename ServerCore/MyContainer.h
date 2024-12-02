//#pragma once
//
//#include "Types.h"
//#include "Allocator.h"
//#include <vector>
//#include <list>
//#include <queue>
//#include <stack>
//
//#include <unordered_map>
//#include <map>
//#include <set>
//#include <unordered_set>
//#include <string>
//using namespace std;
//
//template<typename T>
//using Deque = deque<T, STLAlloctor<T>>;
//
//
//template<typename T>
//using Vector = vector<T, STLAlloctor<T>>;
//
//template<typename T>
//using List = list<T, STLAlloctor<T>>;
//
//template<typename Key,typename T, typename Pred = less<Key>>
//using Map = map<Key,T,Pred , STLAlloctor<pair<const Key,T>>>;
//
//template<typename Key, typename T,typename Hasher = std::hash<Key>, typename Equal = equal_to<Key>>
//using HashTable = unordered_map<Key, T, Hasher, Equal, STLAllocator<pair<const Key, T>>>;
//
//template<typename T> 
//using Stack = stack<T, Deque<T>>;
//
//template <typename T>
//using Queue = queue < T, Deque<T>>; // vector list 장점 s ? 
//
//template<typename T, typename Container = Vector<T>, typename Pred = less<typename Container::value_type>>
//using PriorityQueue = priority_queue<T, Container, Pred>;
//
//template<typename Key,typename Pred = less<Key>>
//using Set = set<Key, Pred, STLAlloctor<Key>>;
//
//template<typename Key,typename Hasher = std::hash<Key>,typename KeyEqual = equal_to<Key>>
//using HashSet = unordered_set<Key, Hasher, KeyEqual, STLAlloctor<Key>>;
//
//using String = basic_string<char, char_traits<char>, STLAlloctor<char>>;
//using WStirng = basic_string<wchar_t, char_traits<wchar_t>, STLAlloctor<char>>;
#pragma once

#include "Types.h"
#include "Allocator.h"
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <set>
#include <unordered_set>
#include <string>

using namespace std;

template<typename T>
using Deque = deque<T, STLAllocator<T>>;

template<typename T>
using Vector = vector<T, STLAllocator<T>>;

template<typename T>
using List = list<T, STLAllocator<T>>;

template<typename Key, typename T, typename Pred = less<Key>>
using Map = map<Key, T, Pred, STLAllocator<pair<const Key, T>>>;

template<typename Key, typename T, typename Hasher = std::hash<Key>, typename Equal = equal_to<Key>>
using HashTable = unordered_map<Key, T, Hasher, Equal, STLAllocator<pair<const Key, T>>>;

template<typename T>
using Stack = stack<T, Deque<T>>;

template<typename T>
using Queue = queue<T, Deque<T>>;

template<typename T, typename Container = Vector<T>, typename Pred = less<typename Container::value_type>>
using PriorityQueue = priority_queue<T, Container, Pred >;

template<typename Key, typename Pred = less<Key>>
using Set = set<Key, Pred, STLAllocator<Key>>;

template<typename Key, typename Hasher = std::hash<Key>, typename KeyEqual = equal_to<Key>>
using HashSet = unordered_set<Key, Hasher, KeyEqual, STLAllocator<Key>>;

using String = basic_string<char, char_traits<char>, STLAllocator<char>>;
using WString = basic_string<wchar_t, char_traits<wchar_t>, STLAllocator<char>>;