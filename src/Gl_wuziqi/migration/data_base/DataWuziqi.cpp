#include "DataWuziqi.h"

void DataWuziqiSpecType::insert(Point qPointF, chessState oneChessState)
{
	chessDataBase.insert(std::pair<Point, chessState>(qPointF, oneChessState));
}

DataWuziqiSpecType::chessesData* DataWuziqiSpecType::get()
{
	return &chessDataBase;
}
