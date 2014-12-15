#include "NetworkGameClient.h"


NetworkGameClient::NetworkGameClient(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID)
{
	this->gameEngine = gameEngine;
	this->controllerID = controllerID;
	//connectToServer("127.0.0.1", 53000);
}


NetworkGameClient::~NetworkGameClient()
{
	sendingThreadOnline = false;
	receivingThreadOnline = false;
	networkReceiveThread.join();
	networkSendThread.join();
}

void NetworkGameClient::update(){
	// If packet threads are not online, start them
	if (!receivingThreadOnline){
		networkReceiveThread = std::thread(&NetworkGameClient::threadReceivePackets, this);
	}
	// Otherwise proceed
	else {
		// Print if there are any packets received
		if (!receivedPackets.empty()){

			sf::Uint16 x;
			std::string s;
			double d;

			receivedPacketMutex.lock();
			for (auto newPacket : receivedPackets){
				newPacket >> x >> s >> d;
				std::cout << "Client received: " << x << s << d << std::endl;
			}
			receivedPackets.clear();
			receivedPacketMutex.unlock();
		}
		// Testing, just make a packet and send it
		if (gameEngine->eventKeyPressed){
			std::cout << "Gonna make a packet!" << std::endl;
			sf::Uint16 x = 10;
			std::string s = "hello";
			double d = 0.6;

			sf::Packet packet;
//			packet << x << s << d;
			pendingPacketMutex.lock();
			pendingSendPackets.push_back(packet);
			pendingSendPackets.back() << x << s << d;
			std::cout << "Number of sendable packets pending: " << pendingSendPackets.size() << std::endl;
			pendingPacketMutex.unlock();

		}
		
	}
}

void NetworkGameClient::threadReceivePackets() {
	if (!connectedToServer){
		connectedToServer = connectToServer("127.0.0.1", socketNumber);
		if (connectedToServer){
			networkSendThread = std::thread(&NetworkGameClient::threadSendPackets, this);
		}
	}
	receivingThreadOnline = true;
	while (receivingThreadOnline && connectedToServer){
		sf::Packet newPacket;
		if (serverSocket.receive(newPacket) == sf::Socket::Done){
			std::cout << "Received a packet!" << std::endl;
			receivedPacketMutex.lock();
			receivedPackets.push_back(newPacket);
			receivedPacketMutex.unlock();
		}
	}
}

void NetworkGameClient::threadSendPackets() {
	sendingThreadOnline = true;
	while (sendingThreadOnline && connectedToServer){
		if (!pendingSendPackets.empty()){
			std::cout << "Have packets to send!" << std::endl;
			pendingPacketMutex.lock();
			for (auto newPacket : pendingSendPackets) {
				serverSocket.send(newPacket);
			}
			pendingSendPackets.clear();
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