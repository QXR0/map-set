#pragma once
#include"RedBlackTree.h"


namespace Set
{
	class _SetCompare
	{
	public:
		bool operator()(int first1, int first2)
		{
			return first1 > first2;
		}
	};

	
	template<class K, class Set_Compare = _SetCompare>
	class Set
	{
	private:
		RBTree<K, K, Set_Compare>_set;
	public:

		typedef _iterator<K,K> iterator;


		pair<iterator,bool> Insert(K data)
		{
			return _set.Insert(make_pair(data,data));
		}
		iterator begin()
		{
			return _set._begin();
		}
		iterator end()
		{
			return _set._end();
		}
	};

}
 