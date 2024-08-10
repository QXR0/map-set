#include"Set.h"
#include"Map.h"
#include<string>
#include<set>
#include<vector>

class date
{
public:
	int _year;
	int _month;
	int _day;
	date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}
};
class compare
{
public:
	bool operator()(date d1,date d2)
	{
		return (d1._day + d1._month + d1._year) > (d2._day + d2._month + d2._year);
	}
};

int main()
{
	/*Set<int>s;
	s.Insert(1);*/
	
	/*Set<date,compare>s;
	s.Insert(date(2000, 1, 1));
	s.Insert(date(2000, 12, 1));*/
	/*Map<date, date, compare>m;
	m.Insert(make_pair(date(2000, 1, 1), date(2000, 1, 1)));
	m.Insert(make_pair(date(2000, 12, 1), date(2000, 1, 1)));*/
	//RBTree<int, int, MapCompare>t;
	//t.Insert(make_pair(100,1));
	//t.Insert(make_pair(21,1));
	//t.Insert(make_pair(3,1));
	//t.Insert(make_pair(30,1));
	//t.Insert(make_pair(31,1));
	//RBTree<int, int, MapCompare>::Iterator it = t._begin();
	////++it;
	////cout<<*
	////cout << *it;
	//int count = 0;
	//while (it != t._end())
	//{
	//	cout << *it<<" ";
	//	++it;
	//	count++;
	//	if (count == 2)
	//	{
	//		int i = 0;
	//	}
	//}


	Set::Set<int>s;
	s.Insert(10);
	s.Insert(1);
	s.Insert(15);
	Set::Set<int>::iterator it = s.begin();
	/*while (it != s.end())
	{
		cout << *it<<" ";
		++it;
	}*/

	/*for (auto e : s)
	{
		cout << e << " ";
	}*/
	Map <int, int>m;
	m.Insert(make_pair(100, 1));
	m.Insert(make_pair(12, 1));
	m.Insert(make_pair(1000, 1));
	for (auto e : m)
	{
		cout << e << " ";
		
	}
	return 0;
}

