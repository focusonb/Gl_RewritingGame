

#include "rule.h"
#include "../myfunction.h"
#include <stdlib.h>
//#include <QGraphicsScene>
//#include "GameWidget.h"
class GameWidget;

bool is_win(ChessPoint& point_chess, map<ChessPoint, int, cmp> const *ptrchesses, int& chess_width, bool&myturn, const bool& gamegoingon)
{
	if (check_row(point_chess, ptrchesses, chess_width, myturn)||
		check_col(point_chess, ptrchesses, chess_width, myturn)||
		check_obl(point_chess, ptrchesses, chess_width, myturn)||
		check_obl_a(point_chess, ptrchesses, chess_width, myturn)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}  
bool check_row(ChessPoint& point_chess, map<ChessPoint, int, cmp>const* ptrchesses, int& chess_width, bool&myturn)
{
	if (myturn == true)
	{
		return Is_row_win(point_chess, ptrchesses, chess_width, 1);
	}

	return Is_row_win(point_chess, ptrchesses, chess_width, 0);

}
bool Is_row_win(ChessPoint& point_chess, map<ChessPoint, int, cmp> const* ptrchesses, int& chess_width, int i)
{
	int count = -1;
	for (
		 int next_left_x = point_chess.rx();
		ptrchesses->find(ChessPoint(next_left_x, point_chess.ry()))!= ptrchesses->end() &&
		ptrchesses->at(ChessPoint(next_left_x, point_chess.ry())) == i;
		)
	{
		next_left_x -= chess_width;
		++count;
		if (is_outrange(ChessPoint(next_left_x, point_chess.ry()), chess_width))
		{
			break;
	    }  
	}
	for (
		int next_right_x = point_chess.rx();
		ptrchesses->find(ChessPoint(next_right_x, point_chess.ry())) != ptrchesses->end() &&
		ptrchesses->at(ChessPoint(next_right_x, point_chess.ry())) == i;
		)
	{
		next_right_x += chess_width;
		++count;
		if (is_outrange(ChessPoint(next_right_x, point_chess.ry()), chess_width))
		{
			break;
		}
	}
	if (count >= 5)
	{
		return true;
	}
	else
		return false;
}
bool check_col(ChessPoint& point_chess, map<ChessPoint, int, cmp> const* ptrchesses, int& chess_width, bool&myturn)
{
	if (myturn == true)
	{
		return Is_col_win(point_chess, ptrchesses, chess_width, 1);
	}

	return Is_col_win(point_chess, ptrchesses, chess_width, 0);

}
bool Is_col_win(ChessPoint& point_chess, map<ChessPoint, int, cmp> const* ptrchesses, int& chess_width, int i)
{
	int count = -1;
	for (
		int next_down_y= point_chess.ry();
		ptrchesses->find(ChessPoint(point_chess.rx(), next_down_y)) != ptrchesses->end() &&

		ptrchesses->at(ChessPoint( point_chess.rx(), next_down_y)) == i;	
		)
	{
		next_down_y += chess_width;
		++count;
		if (is_outrange(ChessPoint(point_chess.rx(), next_down_y), chess_width))
		{
			break;
		}
	}
	for (
		int next_up_y = point_chess.ry();
		ptrchesses->find(ChessPoint(point_chess.rx(), next_up_y)) != ptrchesses->end() &&
		ptrchesses->at(ChessPoint(point_chess.rx(), next_up_y)) == i;
		)
	{
		next_up_y -= chess_width;
		++count;
		if (is_outrange(ChessPoint(point_chess.rx(), next_up_y), chess_width))
		{
			break;
		}
	}
	if (count >= 5)
	{
		return true;
	}
	else
		return false;
}

bool check_obl(ChessPoint& point_chess, map<ChessPoint, int, cmp> const* ptrchesses, int& chess_width, bool&myturn)
{
	if (myturn == true)
	{
		return Is_obl_win(point_chess, ptrchesses, chess_width, 1);
	}

	return Is_obl_win(point_chess, ptrchesses, chess_width, 0);
}
bool Is_obl_win(ChessPoint& point_chess, map<ChessPoint, int, cmp> const* ptrchesses, int& chess_width, int i)
{
	int count = -1;
	//ChessPoint temp = point_chess;
	for (
		auto p = std::make_pair(point_chess.rx(), point_chess.ry());
		ptrchesses->find(ChessPoint(p.first, p.second)) != ptrchesses->end() &&
		ptrchesses->at(ChessPoint(p.first,p.second)) == i;
		)
	{
		p.first -= chess_width, p.second -= chess_width;
		++count;
		if (is_outrange(ChessPoint(p.first, p.second), chess_width))
		{
			break;
		}
			
	}
	for (
		auto p = std::make_pair(point_chess.rx(), point_chess.ry());
		ptrchesses->find(ChessPoint(p.first, p.second)) != ptrchesses->end() &&
		ptrchesses->at(ChessPoint(p.first,p.second ) )== i;
		)
	{
		p.first += chess_width, p.second += chess_width;
		++count;
		if (is_outrange(ChessPoint(p.first, p.second), chess_width))
		{
			break;
		}
	}
	if (count >= 5)
	{
		return true;
	}
	else
		return false;
}
bool check_obl_a(ChessPoint& point_chess, map<ChessPoint, int, cmp> const* ptrchesses, int& chess_width, bool&myturn)
{
	if (myturn == true)
	{
		return Is_obl_win_a(point_chess, ptrchesses, chess_width, 1);
	}
	return Is_obl_win_a(point_chess, ptrchesses, chess_width, 0);
}
bool Is_obl_win_a(ChessPoint& point_chess, map<ChessPoint, int, cmp> const* ptrchesses, int& chess_width, int i)
{
	int count = -1;
	//ChessPoint temp = point_chess;
	for (
		auto p = std::make_pair(point_chess.rx(), point_chess.ry());
		ptrchesses->find(ChessPoint(p.first, p.second)) != ptrchesses->end() &&
		ptrchesses->at(ChessPoint(p.first,p.second)) == i;
		)
	{
		p.first += chess_width, p.second -= chess_width;
		++count;
		if (is_outrange(ChessPoint(p.first, p.second), chess_width))
		{
			break;
		}
	}
	for (
		auto p = std::make_pair(point_chess.rx(), point_chess.ry());
		ptrchesses->find(ChessPoint(p.first, p.second)) != ptrchesses->end() &&
		ptrchesses->at(ChessPoint(p.first,p.second)) == i;
		)
	{
		p.first -= chess_width, p.second += chess_width;
		++count;
		if (is_outrange(ChessPoint(p.first, p.second), chess_width))
		{
			break;
		}
	}
	if (count >= 5)
	{
		return true;
	}
	else
		return false;
}
