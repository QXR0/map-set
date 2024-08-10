#pragma once
#include"RedBlackTree.h"

class MapCompare
{
public:
	bool operator()(int first1,int first2)
	{
		return first1 > first2;
	}
};

template<class K,class V,class _MapCompare=MapCompare>
class Map
{
private:
	RBTree<K, V, _MapCompare>_map;
public:
	typedef _iterator<K, V> iterator;
	pair<iterator,bool> Insert(pair<K, V> data)
	{
		return _map.Insert(data);
	}
	iterator begin()
	{
		return _map._begin();
	}
	iterator end()
	{
		return _map._end();
	}
};
