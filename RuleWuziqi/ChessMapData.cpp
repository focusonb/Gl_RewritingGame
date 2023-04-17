#include "ChessMapData.h"

pair<int, int> SigleChessLocation::getLeftUpLoc() const
{
	return pair<int, int>(m_loca.first-1, m_loca.second-1);
}
pair<int, int> SigleChessLocation::getLeftDownLoc() const
{
	return pair<int, int>(m_loca.first - 1, m_loca.second + 1);
}
pair<int, int> SigleChessLocation::getRightUpLoc() const
{
	return pair<int, int>(m_loca.first + 1, m_loca.second - 1);
}
pair<int, int> SigleChessLocation::getRightDownLoc() const
{
	return pair<int, int>(m_loca.first + 1, m_loca.second + 1);
}
pair<int, int> SigleChessLocation::getUpLoc() const
{
	return pair<int, int>(m_loca.first, m_loca.second - 1);
}
pair<int, int> SigleChessLocation::getDownLoc() const
{
	return pair<int, int>(m_loca.first, m_loca.second + 1);
}
pair<int, int> SigleChessLocation::getLeftLoc() const
{
	return pair<int, int>(m_loca.first - 1, m_loca.second);
}
pair<int, int> SigleChessLocation::getRightLoc() const
{
	return pair<int, int>(m_loca.first + 1, m_loca.second);
}

void SigleChessLocation::setLoca(pair<int, int> loca)
{
	m_loca = loca;
}

pair<int, int> SigleChessLocation::getLoc() const
{
	return m_loca;
}

ChessMapData::ChessColor ChessMapData::getColor(const ChessLocation & loca) const
{
	auto interator = m_chessData.find(loca);
	if (interator == m_chessData.end())
		return 0;
	return interator->second;
}

void ChessMapData::addNewChess(const SigleChessData & sigleChessData)
{
	auto loca = sigleChessData.first;
	auto interator = m_chessData.find(loca);
	if (interator == m_chessData.end())
		return;
	interator->second = sigleChessData.second;
}
