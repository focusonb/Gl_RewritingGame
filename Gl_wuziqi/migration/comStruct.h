#pragma once
#include<map>
//#include<vector>

//using ClickPoint = std::vector<PointType>;
class ClickPoint {
	using PointType = int;
	PointType m_data[2];
public:
	ClickPoint(PointType x = 0, PointType y = 0) :m_data{ x, y } {}
	PointType x() const {
		return m_data[0];
	}
	PointType& rx() {
		return m_data[0];
	}

	PointType y() const {
		return m_data[1];
	}
	PointType& ry() {
		return m_data[1];
	}
	void setX(PointType x) {
		m_data[0] = x;
	}
	void setY(PointType y) {
		m_data[1] = y;
	}
};
struct cmp
{
public:
	bool operator()(const ClickPoint& a, const ClickPoint& b)const
	{
		{
			if (a.y() < b.y())
			{
				return true;
			}
			else if (a.y() > b.y())
			{
				return false;
			}
			if (a.x() == b.x())
			{
				return false;
			}
			else if (a.x() < b.x())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
};
//class ChessPoint {
//	std::pair<int, int> m_data;
//public:
//	ChessPoint(int x = 0, int y = 0) :m_data(x, y) {}
//	void setX(int x) {
//		std::get<0>(m_data) = x;
//	}
//	void setY(int y) {
//		std::get<1>(m_data) = y;
//	}
//	int& rx() {
//		return std::get<0>(m_data);
//	}
//	int x() const {
//		return std::get<0>(m_data);
//	}
//	int& ry() {
//		return std::get<1>(m_data);
//	}
//	int y() const {
//		return std::get<1>(m_data);
//	}
//};
using MapPoint = std::map<ClickPoint, int, cmp>;

struct SocketData {
	ClickPoint point_chess;
	//MapPoint* ptrchesses = nullptr;
	//int chess_width;
};

typedef void(*handleInput)(double x, double y);

