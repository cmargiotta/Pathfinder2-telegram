#include "bot.hpp"

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <functional>

#include "master.hpp"
#include "message_handler.hpp"
#include "callback_handler.hpp"
#include "common/string_utils.hpp"

using namespace pathfinder2;

bot::bot(SQLite::Database& _database):
	 _bot(getenv("PF2_INV_BOT_TOKEN")),
	database(_database)
{
	using namespace std::placeholders;

	_bot.getEvents().onAnyMessage([this](TgBot::Message::Ptr msg){message_handler(_bot, msg, database);});

	_bot.getEvents().onCallbackQuery([this](TgBot::CallbackQuery::Ptr query) {
        callback_handler(_bot, query, database);
    });

	std::cout << "Bot username: " << _bot.getApi().getMe()->username << std::endl;

	const char* webhook_url = getenv("PF2_INV_WEBHOOK_URL");

	master::get_instance(&database, &_bot);

	if (webhook_url != nullptr)
	{	
		TgBot::TgWebhookTcpServer webhook_server(8080, _bot);
		_bot.getApi().setWebhook(std::string(webhook_url));

		std::cout << "Starting webhook server at " << webhook_url << std::endl;

        webhook_server.start();
	}
	else 
	{
		std::cout << "Warning, webhook url not set, starting long poll mode.\n";

		TgBot::TgLongPoll long_poll(_bot);
		while (true) 
		{
			long_poll.start();
		}
	}
}