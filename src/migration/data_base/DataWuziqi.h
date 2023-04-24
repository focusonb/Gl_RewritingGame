#pragma once
#include <map>

//#include "../drawer/Drawer.h"
#include "../comStruct.h"

class OneChessData
{
public:

};

//extern struct cmp;

class DataWuziqi
{
public:
	using widthNum = int;
	using heightNum = int;
	using pointSeq = ClickPoint;
	using chessState = int;
	using Point = ClickPoint;
	using chessesData = MapPoint;
public:
	virtual void insert(Point seq, chessState oneChessState) = 0;
	virtual chessesData* get() = 0;
};

class DataWuziqiSpecType : public DataWuziqi
{
public:
	using pointSeq = DataWuziqi::pointSeq;
	using chessState = DataWuziqi::chessState;
	using chessesData = DataWuziqi::chessesData;
	using Point = DataWuziqi::Point;
private:
	chessesData chessDataBase;
public:
	virtual void insert(Point qPointF, chessState oneChessState) override;
	chessesData* get() override;
};