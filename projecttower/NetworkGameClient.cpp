#include "NetworkGameClient.h"


NetworkGameClient::NetworkGameClient(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID)
{
	this->gameEngine = gameEngine;
	this->controllerID = controllerID;
	//connectToServer("127.0.0.1", 53000);
}


NetworkGameClient::~NetworkGameClient()
{
	packetThreadOnline = false;
	networkThread.join();
}

void NetworkGameClient::update(){
	// If packe thread is not online, start it
	if (!packetThreadOnline){
		networkThread = std::thread(&NetworkGameClient::waitForPackets, this);
	}
	// Otherwise proceed
	else {
		// Print if there are any packets received
		if (!receivedPackets.empty()){
			receivedPacketMutex.lock();
			sf::Uint16 x;
			std::string s;
			double d;

			receivedPackets.back() >> x >> s >> d;
			receivedPackets.pop_back();
			std::cout << "Client received: " << x << s << d << std::endl;
			receivedPacketMutex.unlock();
		}
		// Testing, just make a packet and send it
		if (gameEngine->eventKeyPressed){
			std::cout << "Gonna make a packet!" << std::endl;
			std::cout << "Number of received packets pending: " << receivedPackets.size() << std::endl;
			sf::Uint16 x = 10;
			std::string s = "hello";
			double d = 0.6;

			sf::Packet packet;
			packet << x << s << d;
			pendingPacketMutex.lock();
			pendingSendPackets.push_back(packet);
			pendingPacketMutex.unlock();
		}
		
	}
}

void NetworkGameClient::waitForPackets() {
	packetThreadOnline = true;
	while (packetThreadOnline){
		if (!connectedToServer){
			connectedToServer = connectToServer("127.0.0.1", socketNumber);
		}
		sf::Packet newPacket;
		std::cout << "Waiting for packet" << std::endl;
		if (serverSocket.receive(newPacket) == sf::Socket::Done){
			std::cout << "Received a packet!" << std::endl;
			receivedPacketMutex.lock();
			receivedPackets.push_back(newPacket);
			receivedPacketMutex.unlock();
		}
		if (!pendingSendPackets.empty()){
			std::cout << "Have packets to send!" << std::endl;
			pendingPacketMutex.lock();
			for (auto newPacket : pendingSendPackets) {
				serverSocket.send(newPacket);
			}
			pendingPacketMutex.unlock();
		}
	}
}

bool NetworkGameClient::connectToServer(sf::IpAddress address, int socket){
	serverIP = address;
	socketNumber = socket;

	if (serverSocket.connect(serverIP, socketNumber) != sf::Socket::Done){
		return false;
	}
	return true;
}

std::vector<std::vector<sf::Drawable *>> NetworkGameClient::getDynamicRenderData() {
	return std::vector<std::vector<sf::Drawable *>>();
}
std::vector<std::vector<sf::Drawable *>> NetworkGameClient::getStaticRenderData() {
	return std::vector<std::vector<sf::Drawable *>>();
}

sf::View NetworkGameClient::getView() {
	return gameView;
}

std::vector<SubController *> NetworkGameClient::getChildControllers() {
	return childControllers;

}

void NetworkGameClient::preloadAssets() {

}