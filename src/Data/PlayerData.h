#pragma once
class GameSocketManager;
class PlayerData {

	static bool isInitialized;
public:
	PlayerData() = delete;
	static void iniPlayerData(const GameSocketManager& gameSocketManager);
	static bool myCharacter;
	static bool bMyTurn;
};