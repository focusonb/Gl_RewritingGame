#pragma once
#include <map>

using std::map;
using std::pair;

namespace spgl {
	using GlSize = int;
	using PointGl = pair<GlSize, GlSize>;
};

using namespace spgl;
class BoardLocation
{
public:
	
	using PointInt = pair<int, int>;
	using MapLoca = map<PointGl, PointInt>;
	//widNUm is number of rows and collums of the board
	BoardLocation(GlSize widthWindow, GlSize heightWindow, int widNum,int heiNUm);

	bool getChessPointGl(GlSize cursor_width, GlSize cursor_height, PointGl& point) const;
	bool getChessPointInt(GlSize cursor_width, GlSize cursor_height, PointInt& point) const;
	bool fixRandomClickToPoint(GlSize cursor_width, GlSize cursor_height, PointGl& point) const;
	const GlSize getWidth() const;
	const MapLoca getAllPoint() const;

private:
	GlSize m_width;
	GlSize m_height;
	MapLoca m_loca;
};

