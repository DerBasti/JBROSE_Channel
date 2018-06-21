#include "ChannelServerPacketFactory.h"
#include "RequestPackets.h"

ChannelServerPacketFactory::ChannelServerPacketFactory() {
	addCommand<IdentifyAccountRequestPacket>(IdentifyAccountRequestPacket::ID);
	addCommand<CharacterListRequestPacket>(CharacterListRequestPacket::ID);
	addCommand<CharacterCreationRequestPacket>(CharacterCreationRequestPacket::ID);
	addCommand<WorldServerIpRequestPacket>(WorldServerIpRequestPacket::ID);
}