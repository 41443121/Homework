# test
#include<iostream>
using namespace std;
class Point
{
	int x, y;
public:
	Point() {
		x = y = 0;
	}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	friend istream& operator >>(istream& s, Point& p);
	friend ostream& operator <<(ostream& s, Point p);
	int w;
	Point operator (Point p)
	{
		if (w == 1)
		{
			return Point(x + p.x, y + p.y);
		}
		else (w == 2)
		{
			return Point(x * p.x, y * p.y);
		}
		else(w == 3)
		{
		return Point()
		}
	}
};
istream& operator >>(istream& s, Point& p)
{
	cout << "輸入點座標: ";
	s >> p.x >> p.y;
	return s;
}
ostream& operator <<(ostream& s, Point p)
{
	s << "(" << p.x << ", " << p.y << ")";
	return s;
}
int main() 
{	
	int n;
	cout << "要建立幾個式";
	cin >> n;
	Point* p = new Point[n];
	for (int i = 0; i < n; i++)
	{
		cout << "第" << i + 1 << "個點";
		cin >> p[i];
	}
	
	do 
	{

	} while (z != 3);
	return 0;
}
