#pragma once

#include <string>
#include <atomic>



/** @file Actions.h
    @brief   Actions file defines a thread safe game action
    @details GameActions are stored here as well as a thread safe  
             GameAction variable, which has external linkage. 
*/



/** @enum GameAction
*   @brief is a strongly typed enum class representing the next game action
*/
enum class PlayerAction
{
	INVALID   = -1,
	NONE      =  0,
	LEFT,
	RIGHT,
};



enum class GameState
{
	INVALID = -1,
	MENU    =  0,
	PLAY,
	PAUSE,
	EXIT,
	GAME_OVER,
	LEVEL_WON,
};



enum class FireState
{
	INVALID = -1,
	NONE    =  0,
	FIRE,
};



enum class EnemyState
{
	INVALID = -1,
	NONE    =  0,
	LEFT,
	RIGHT,
	DOWN
};



extern std::atomic<PlayerAction> player_action;
extern std::atomic<GameState> game_state;
extern std::atomic<FireState> fire_state;
extern std::atomic<EnemyState> enemy_state;