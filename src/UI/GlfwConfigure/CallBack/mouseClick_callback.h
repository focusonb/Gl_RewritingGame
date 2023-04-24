#pragma once
#include "../../DrawBoard/BoardLocation.h"
class GlCirclePainter;
extern GlCirclePainter* ptrChessWhitePainter;
extern BoardLocation* ptrBoardLoc;

void handleClickInput_socket(double xpos, double ypos);
void handleClickInput(double xpos, double ypos);
void addOneChessToBaord(PointGl chessCoor, bool myCharacter, GlSize width);