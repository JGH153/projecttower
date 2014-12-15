#pragma once
#include <SFML\Network.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include "SubController.h"
class NetworkGameClient :
	public SubController
{
public:
	NetworkGameClient(Vortex * gameEngine, int controllerID);
	~NetworkGameClient();
	void update();
	
	std::vector<std::vector<sf::Drawable *>> getDynamicRenderData();
	std::vector<std::vector<sf::Drawable *>> getStaticRenderData();
	sf::View getView();
	std::vector<SubController *> getChildControllers();
	void preloadAssets();
private:
	bool connectToServer(sf::IpAddress address, int socket);
	void threadReceivePackets();
	void threadSendPackets();


	sf::TcpSocket serverSocket;
	Vortex* gameEngine;
	int controllerID;
	sf::IpAddress serverIP;
	int socketNumber = 53000;

	std::vector<sf::Packet> receivedPackets;
	std::vector<sf::Packet> pendingSendPackets;

	std::mutex pendingPacketMutex;
	std::mutex receivedPacketMutex;

	bool connectedToServer = false;
	bool receivingThreadOnline = false;
	bool sendingThreadOnline = false;
	std::thread networkSendThread;
	std::thread networkReceiveThread;
};

