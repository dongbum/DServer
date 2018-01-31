#pragma once

#include "../dnetwork/protocol/base_protocol.h"
#include "../protocol/client_game_protocol.h"
#include "../protocol/bridge_game_protocol.h"
#include "protocol/game_protocol.h"
#include "protocol/BR_GS/bridge_protocol.h"
#include "game_socket.h"
#include "game_user.h"
#include "bridge_connector.h"
#include "game_server.h"

#define GAME_SVR	std::static_pointer_cast<GameServer>(GameServer::GetServerInstance())