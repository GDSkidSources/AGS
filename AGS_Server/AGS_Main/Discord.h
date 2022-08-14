#pragma once
#include "./DiscordSDK/discord_rpc.h"
#include "./DiscordSDK/discord_register.h"
#include <chrono>

namespace Discord {
	std::string Message = "Setting Up...";
	DiscordRichPresence RP;
	void Setup() {
		DiscordEventHandlers handlers;
		memset(&handlers, 0, sizeof(handlers));
		Discord_Initialize("971173994944430141", &handlers, 1, "0");
	}

	void Update() {
		static int64_t Time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		memset(&RP, 0, sizeof(RP));
		RP.state = "AGS";
		RP.details = Message.c_str();
		RP.startTimestamp = Time;
		RP.endTimestamp = 0;
		RP.largeImageKey = "l_image";
		RP.largeImageText = "AGS";
		RP.instance = 1;
		Discord_UpdatePresence(&RP);
	}

	void SetMessage(std::string NMessage) {
		Message = NMessage;
		//Update();
	}

	void StartRPC() {
		//Setup();
		//Update();
	}
}