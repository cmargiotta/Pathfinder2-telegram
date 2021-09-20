#include "commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::_list(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{
	static auto& messages = pathfinder2::get_messages(message->from->languageCode);
    static auto& buttons = pathfinder2::get_commands(message->from->languageCode);

	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];

    auto keyboard = pathfinder2::create_keyboard({{buttons["list_brief"]}, {buttons["list_detail"]}});

	character_->set_context(messages["list_granularity_request"]);
	bot.getApi().sendMessage(character_->get_id(), character_->get_context(), false, 0, keyboard);
}