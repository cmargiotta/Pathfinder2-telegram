#include "commands.hpp"

#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::_money_transaction(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages();

	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

	character_->set_context(messages["money_transaction_request"]);
	bot.getApi().sendMessage(id, character_->get_context(), false, 0, pathfinder2::remove_keyboard);
}