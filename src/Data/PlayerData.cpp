#include "PlayerData.h"
#include "../migration/socket/GameSocketManager.h"

bool PlayerData::isInitialized = false;
bool PlayerData::myCharacter = false;
bool PlayerData::bMyTurn = false;

void PlayerData::iniPlayerData(const GameSocketManager& gameSocketManager) {
	if (isInitialized) {
		return;
	}
	myCharacter = gameSocketManager.getBRequestConnection();
	bMyTurn = myCharacter;
}