#include "Actions.h"

/**< Queued Game Action. The next action to be processed as determined by user input. */
std::atomic<PlayerAction> player_action = PlayerAction::NONE;
std::atomic<GameState> game_state = GameState::MENU;
std::atomic<FireState> fire_state = FireState::NONE;
std::atomic<EnemyState> enemy_state = EnemyState::NONE;