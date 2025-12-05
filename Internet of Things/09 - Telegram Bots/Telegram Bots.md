---
tags:
  - iot
  - telegram
  - api
---

## Telegram Bot

Telegram communication relies on a protocol called MTProto.

Via the usage of bots, it's possible to design an interface for code running somwhere on the server, making it possible to automate various task and provide enhanced functionality to Telegram users.

Bots are different from Users in the following ways:
- Bots don't have "last seen" or online statuses
- Bots jave limited cloud storage, and older messages may be removed by the server after the request is processed
- Bots can't start conversations with users
- Bots added to groups can only see relevant messages (as set in the Privacy settings)

Benefits of a Telegram bot:
- Ubiquitous access
- Rapid development via the extensive APIs and SDKs available
- Rich interaction, made possible via buttons, inline queries, and media upload
- Low infrastructure overhead

#### Telegram APIs 

Telegram offers 3 kind of APIs:
- Bot API, which allows to create programs which use Telegram messages as an interface
- Telegram API and TDLib, which allow to build customized Telegram clients
- Gateway API, which allows any business, app or website to send verification codes through Telegram instead of regular messages

There are 2 main communication methods to communicate with Telegram Bot API:
- Webhook 
	- Based on the `setWebhook()` method
	- It needs a server that accepts POST requests with JSON data
	- *Pros*: More lightweight and better response times
	- *Cons*: Telegram only supports HTTPS hooks, so a valid SSL certificate is needed
- Polling:
	- Based on the `getUpdates()` method
	- It's actually a (Long) Polling (a polling where the client asks the server and waits with the connection open until there is a response)
	- *Pros*: Excellent during development phase, as it's incredibly simple to implement since it does not require a separate server setup
	- *Cons*: Bigger resource usage

#### How to create a bot

1. Create a bot account through the Bot Father on Telegram
2. Implement the bot logic
3. Deploy the bot code to a hosting platform
4. Customize the bot behavior and interface to fit the specific use-case

