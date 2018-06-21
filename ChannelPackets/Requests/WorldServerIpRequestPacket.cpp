#include "WorldServerIpRequestPacket.h"

std::string WorldServerIpRequestPacket::toPrintable() const {
	char buf[0x100] = { 0x00 };
	sprintf_s(buf, "[WorldServerIpRequestPacket - %i bytes]\n\t* Unknown Byte: 0x%x\n\t* Unknown Byte: 0x%x\n\t* Unknown Byte: 0x%x\n\t* Name: %s", 
		getLength(), unknownByte1, unknownByte2, unknownByte3, getSelectedCharacter().c_str());
	return std::string(buf);
}