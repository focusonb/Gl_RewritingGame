#pragma once
#include <map>
using std::pair;
using std::map;
struct cmp
{
public:
	bool operator()(const pair<int, int>& a, const pair<int, int>& b)const
	{
		{
			if (a.second < b.second)
			{
				return true;
			}
			else if (a.second > b.second)
			{
				return false;
			}
			if (a.first == b.first)
			{
				return false;
			}
			else if (a.first < b.first)
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

using ChessData = map<pair<int,int>, int,cmp>;


class SigleChessLocation
{
public:
	SigleChessLocation(const pair<int, int>& pair) :m_loca(pair) {}
	pair<int, int>  getLeftUpLoc()const;
	pair<int, int>  getLeftDownLoc()const;
	pair<int, int>  getRightUpLoc()const;
	pair<int, int>  getRightDownLoc()const;
	pair<int, int>  getUpLoc()const;
	pair<int, int>  getDownLoc()const;
	pair<int, int>  getLeftLoc()const;
	pair<int, int>  getRightLoc()const;
	void setLoca(pair<int, int> loca);
	pair<int, int> getLoc() const;
private:
	pair<int, int> m_loca;
};

class ChessMapData
{
public:
	using SigleChessData = pair<pair<int, int>, int>; //...
	using SigleChessLoca = SigleChessLocation;
	//using SigleChessData = SigleChessLocation; //...
	using ChessLocation = pair<int, int>;
	using ChessColor = int;
public:
	ChessMapData(ChessData data) :m_chessData(data) {}
	ChessColor getColor(const ChessLocation& loca) const;
	void addNewChess(const SigleChessData& sigleChessData);
private:
	ChessData m_chessData;
};

