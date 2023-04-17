#include "ChessMapData.h"
#include "WuziqiRule.h"
#include <iostream>

using std::cout;
using std::endl;
using std::pair;
#ifdef _EXEwin
int main()
{
	using SigleChessData = pair<pair<int, int>, int>;
	using ChessLoc = pair<int, int>;
	//ChessData siglechess = { pair<pair<int,int>,int>(pair<int,int>(1,1),1) };

	ChessLoc siglechess (1,1);
	SigleChessLocation chessLoc(siglechess);

	SigleChessData chessData(siglechess, 1);
	SigleChessData chessData2{ ChessLoc(2,2),1 };
	SigleChessData chessData3{ ChessLoc(3,3),1 };
	SigleChessData chessData4{ ChessLoc(4,4),1 };
	SigleChessData chessData5{ ChessLoc(5,5),1 };
	SigleChessData chessData6{ ChessLoc(6,6),1 };
	SigleChessData chessData7{ ChessLoc(2,4),1 };
	ChessData mapData1 = { chessData,chessData2,chessData3,chessData4, chessData5};


	ChessMapData mapData (mapData1);
	PlayRule<ChessMapData> rule(mapData);
	cout << rule.isWin(ChessLoc(0,0),4) << endl;
	return 0;

}
#endif