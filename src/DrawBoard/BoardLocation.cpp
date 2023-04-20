#include "BoardLocation.h"

BoardLocation::BoardLocation(GlSize widthWindow, GlSize heightWindow, int widNum, int heiNum)
{
	m_width = widthWindow / (widNum + 4);
	m_height = heightWindow / (heiNum + 4);
	int posX = 0;
	int posY = 0;

	for (int i = 0; i < widNum; ++i) {
		for (int j = 0; j < heiNum; ++j) {
			posX = (i + 2)*m_width;
			posY = (j + 2)*m_height;
			m_loca.insert(pair< PointGl, PointInt>(PointGl(posX, posY), PointInt(i, j)));
		}
	}
}

bool BoardLocation::getChessPointGl(GlSize cursor_width, GlSize cursor_height, PointGl& point) const
{
	GlSize widOutput, heiOutput;
	int widNum = static_cast<int>(cursor_width / m_width);
	GlSize nearestWidth = m_width * widNum;
	GlSize pointDistenceWid = cursor_width - nearestWidth;
	if (pointDistenceWid > 0.5* m_width)
		widOutput = nearestWidth + m_width;
	else
		widOutput = nearestWidth;
	int heiNum = static_cast<int>(cursor_height / m_height);
	GlSize nearestHeight = m_height * heiNum;
	GlSize pointDistenceHei = cursor_height - nearestHeight;
	if (pointDistenceHei > 0.5* m_height)
		heiOutput = nearestHeight + m_height;
	else
		heiOutput = nearestHeight;
	auto iterator = m_loca.find(PointGl(widOutput, heiOutput));
	if (iterator == m_loca.end())
		return false;
	point= PointGl(widOutput - m_width*0.5, heiOutput - m_height*0.5);
	return true;

}

bool BoardLocation::getChessPointInt(GlSize cursor_width, GlSize cursor_height, PointInt & point) const
{
	int widOutput, heiOutput;
	int widNum = static_cast<int>(cursor_width / m_width);
	GlSize nearestWidth = m_width * widNum;
	GlSize pointDistenceWid = cursor_width - nearestWidth;
	if (pointDistenceWid > 0.5* cursor_width)
		widOutput = 1 + widNum;
	else
		widOutput = widNum;
	int heiNum = static_cast<int>(cursor_height / m_height);
	GlSize nearestHeight = m_height * heiNum;
	GlSize pointDistenceHei = cursor_height - nearestHeight;
	if (pointDistenceHei > 0.5* cursor_height)
		heiOutput = 1 + heiNum;
	else
		heiOutput = heiNum;
	auto iterator = m_loca.find(PointGl(widOutput*m_width, heiOutput*m_height));
	if (iterator == m_loca.end())
		return false;
	point = PointInt(widOutput, heiOutput);
	return true;
}

bool BoardLocation::fixRandomClickToPoint(GlSize cursor_width, GlSize cursor_height, PointGl& point) const
{

	return true;
}

const GlSize BoardLocation::getWidth() const
{
	return m_width;
}

const BoardLocation::MapLoca BoardLocation::getAllPoint() const
{
	return m_loca;
}
