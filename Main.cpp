#include "ChannelServer.h"

int main() {
	ChannelServer server(29100);
	server.loadEncryption();
	server.startAcceptingClients();
	while (true) {
		Sleep(1);
	}
	return 0;
}