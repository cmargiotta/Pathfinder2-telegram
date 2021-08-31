#ifndef RESET_HPP_
#define RESET_HPP_

#include "commands.hpp"

#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

using pathfinder2::character;

void pathfinder2::_reset(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();
	
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	character_->get_inventory().reset();
	character_->set_capacity(0);

	character_->set_context("");
	bot.getApi().sendMessage(character_->get_id(), messages["reset_done"], false, 0, pathfinder2::remove_keyboard);
	bot.getApi().sendMessage(id, messages["default_message"], false, 0, pathfinder2::get_default_keyboard());
}

#endif // RESET_HPP_