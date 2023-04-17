#pragma once


template<typename DataType>
class PlayRule
{
	using ChessData = typename DataType::SigleChessLoca;
	using ChessLocation = typename DataType::ChessLocation;
	using ChessColor = typename DataType::ChessColor;
public:
	PlayRule(const DataType& data):m_chessData(data){ }
	//void addNewChess(ChessData chessLocation) { m_chessData.addNewChess(chessLocation); };
	bool isWin(const ChessData& chessLocation,int max)const;
protected:
	//bool getMaxNum(const ChessData& chessLocation) const;
	int getLeftUpNum(ChessData chessLocation) const;
	int getLeftDownNum(ChessData chessLocation) const;
	int getRightUpNum(ChessData chessLocation) const;
	int getRightDownNum(ChessData chessLocation) const;
	int getUpNum(ChessData chessLocation) const;
	int getDownNum(ChessData chessLocation) const;
	int getLeftNum(ChessData chessLocation) const;
	int getRightNum(ChessData chessLocation) const;
	void addNewData(const DataType& data) { m_chessData = data; }
private:
	DataType m_chessData;
};

template<typename DataType>
inline bool PlayRule<DataType>::isWin(const ChessData& chessLocation, int max) const
{
	if (getLeftUpNum(chessLocation) + getRightDownNum(chessLocation) + 1 >= max
		|| getRightUpNum(chessLocation) + getLeftDownNum(chessLocation) + 1 >= max
		|| getUpNum(chessLocation) + getDownNum(chessLocation) + 1 >= max
		|| getLeftNum(chessLocation) + getRightNum(chessLocation) + 1 >= max)
		return true;
	else
		return false;
}

template<typename DataType>
inline int PlayRule<DataType>::getLeftUpNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData.getColor(chessLocation.getLeftUpLoc()) == m_chessData.getColor(chessLocation.getLoc()) &&
		m_chessData.getColor(chessLocation.getLoc())!=0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getLeftUpLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getLeftDownNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData.getColor(chessLocation.getLeftDownLoc()) == m_chessData.getColor(chessLocation.getLoc())&&
		m_chessData.getColor(chessLocation.getLoc()) != 0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getLeftDownLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getRightUpNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData.getColor(chessLocation.getRightUpLoc()) == m_chessData.getColor(chessLocation.getLoc())&&
		m_chessData.getColor(chessLocation.getLoc()) != 0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getRightUpLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getRightDownNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData.getColor(chessLocation.getRightDownLoc()) == m_chessData.getColor(chessLocation.getLoc())&&
		m_chessData.getColor(chessLocation.getLoc()) != 0)
	{
		int c = m_chessData.getColor(chessLocation.getRightDownLoc());
		int d = m_chessData.getColor(chessLocation.getLoc());
		++num;
		ChessLocation chessLoca = chessLocation.getRightDownLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getUpNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData.getColor(chessLocation.getUpLoc()) == m_chessData.getColor(chessLocation.getLoc())&&
		m_chessData.getColor(chessLocation.getLoc()) != 0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getUpLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getDownNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData.getColor(chessLocation.getDownLoc()) == m_chessData.getColor(chessLocation.getLoc())&&
		m_chessData.getColor(chessLocation.getLoc()) != 0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getDownLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getLeftNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData.getColor(chessLocation.getLeftLoc()) == m_chessData.getColor(chessLocation.getLoc())&&
		m_chessData.getColor(chessLocation.getLoc()) != 0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getLeftLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}
template<typename DataType>
inline int PlayRule<DataType>::getRightNum(ChessData chessLocation) const
{
	int num = 0;
	while (m_chessData.getColor(chessLocation.getRightLoc()) == m_chessData.getColor(chessLocation.getLoc())&&
		m_chessData.getColor(chessLocation.getLoc()) != 0)
	{
		++num;
		ChessLocation chessLoca = chessLocation.getRightLoc();
		chessLocation.setLoca(chessLoca);
	}
	return num;
}

