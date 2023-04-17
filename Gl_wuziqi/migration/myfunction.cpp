

#include "myfunction.h"
#include <stdlib.h>
//#include <QGraphicsScene>
//#include "GameWidget.h"

//QRectF  qpointtoqrectf(ChessPoint& point_chess,int& chess_width)
//{
//	ChessPoint topLeft(point_chess.rx() - chess_width * 0.4, point_chess.ry() -chess_width * 0.4);
//	ChessPoint bottomRight(point_chess.rx() +chess_width * 0.4, point_chess.ry() +chess_width * 0.4);
//	return QRectF(topLeft, bottomRight);
//}
void pointstd(ChessPoint& point_chess, int& chess_width)
{
	int extra_x = point_chess.x()/chess_width;
	int extra_y= point_chess.y()/chess_width;
	int x;
	int y;
	if(extra_x<=0)
	 x=extra_x-0.5;
	else
		x = extra_x + 0.5;
	if (extra_y <= 0)
		y = extra_y - 0.5;
	else
		y = extra_y +0.5;

	point_chess.rx() = x* chess_width;
	point_chess.ry() = y* chess_width;
}


bool is_outrange(ChessPoint point_chess, int chess_width)
{
	//if (
	//	((point_chess.rx() <= chess_width * 7) &&
	//	(point_chess.rx() >= chess_width * (-7)))
	//	&&
	//	((point_chess.ry() <= chess_width * 7) &&
	//	(point_chess.ry() >= chess_width * (-7)))
	//	)
	//{
	//	return false;
	//}
	//else
	//	return true;
	return false;
}
bool is_chessmade(MapPoint* ptrchesses, ChessPoint& point_chess)
{
	//if (ptrchesses->at(point_chess) != 0)
	if (ptrchesses->find(point_chess) != ptrchesses->end() &&
		ptrchesses->at(point_chess) != 0)
	{
		return true;
	}
	return false;
}
void split_a(string&s, ChessPoint&chesspoint)
{
	size_t pos = s.find('a');
    
	string xstr(s, 0, pos);
	string ystr(s, pos + 1);
	int xq = atof(xstr.c_str());
	int yq = atof(ystr.c_str());
	chesspoint.setX(xq);
	chesspoint.setY(yq);
}