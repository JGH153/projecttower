#include "NetworkGameServer.h"


NetworkGameServer::NetworkGameServer(Vortex * gameEngine, int controllerID) : SubController(gameEngine, controllerID)
{
	this->gameEngine = gameEngine;
	this->controllerID = controllerID;
	//this->socketNumber = socketNumber;
}


NetworkGameServer::~NetworkGameServer()
{
	listenerThreadOnline = false;
	listenerThread.join();
	connectionListener.close();
}


void NetworkGameServer::update(){
	if (!listenerThreadOnline){
		std::cout << "Starting server" << std::endl;
		listenerThread = std::thread(&NetworkGameServer::listenForPackets, this);
	}
	else {
		// Echo
		if (!receivedPackets.empty()){
			std::vector<sf::Packet> newPackets;
			receivedMutex.lock();
			newPackets = receivedPackets;
			receivedMutex.unlock();

			sendMutex.lock();
			pendingSendPackets = newPackets;
			sendMutex.unlock();

		}
		if (gameEngine->eventKeyPressed){
			std::cout << "I have received this many packets: " << receivedPackets.size() << std::endl
				<< "And i have this many pending: " << pendingSendPackets.size() << std::endl;
		}
	}
}

void NetworkGameServer::setSocketNumber(int socketNumber){
	this->socketNumber = socketNumber;
}

bool NetworkGameServer::establishPlayerConnection(){
	std::cout << "Listening for opponent" << std::endl;
	if (connectionListener.accept(otherPlayer) == sf::TcpSocket::Done){
		return true;
	}
	std::cout << "No new opponent connected, listener timed out" << std::endl;
	return false;
}


void NetworkGameServer::listenForPackets(){
	std::cout << "Packet thread started" << std::endl;
	listenerThreadOnline = true;
	if (connectionListener.listen(socketNumber) != sf::Socket::Done){
		// Connection error
		std::cout << "Socket connection listener could not establish the connection" << std::endl;
		listenerThreadOnline = false;
	}

	while (listenerThreadOnline){
		if (!playerConnected){
			playerConnected = establishPlayerConnection();
		}
		std::cout << "Starting new round of listening.." << std::endl;
		sf::Packet receivedPacket;
		if (otherPlayer.receive(receivedPacket) == sf::Socket::Done){
			std::cout << "Received a packet!" << std::endl;
			receivedMutex.lock();
			receivedPackets.push_back(receivedPacket);
			receivedMutex.unlock();
		}
		if (!pendingSendPackets.empty()){
			std::cout << "Have packets to send!" << std::endl;
			sendMutex.lock();
			for (auto newPacket : pendingSendPackets) {
				otherPlayer.send(newPacket);
			}
			sendMutex.unlock();
		}
	}
}

std::vector<std::vector<sf::Drawable *>> NetworkGameServer::getDynamicRenderData() {
	return std::vector<std::vector<sf::Drawable *>>();
}
std::vector<std::vector<sf::Drawable *>> NetworkGameServer::getStaticRenderData() {
	return std::vector<std::vector<sf::Drawable *>>();
}

sf::View NetworkGameServer::getView() {
	return gameView;
}

std::vector<SubController *> NetworkGameServer::getChildControllers() {
	return childControllers;

}

void NetworkGameServer::preloadAssets() {

}