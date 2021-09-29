#include "context_commands.hpp"

#include "../master.hpp"
#include "../keyboards.hpp"
#include "../local_data.hpp"
#include "character/character_cache.hpp"

void pathfinder2::edit_item_master_(TgBot::Bot& bot, TgBot::Message::Ptr message, SQLite::Database& database)
{	static auto keyboard = create_keyboard({
		{std::string(get_command("edit_field_category", message->from->languageCode))},
		{std::string(get_command("edit_field_bulk", message->from->languageCode))},
		{std::string(get_command("edit_field_description", message->from->languageCode))},
		{std::string(get_command("edit_field_url", message->from->languageCode))},
		{std::string(get_command("edit_field_image", message->from->languageCode))},
		{std::string(get_command("cancel", message->from->languageCode))}
	});

    auto& text = message->text;
	auto id = message->chat->id;
	auto character_ = pathfinder2::character_cache[id];
	character_->set_data(text);
	character_->set_context(get_message("edit_selection", message->from->languageCode));
	bot.getApi().sendMessage(id, character_->get_context(), false, 0, keyboard);
}