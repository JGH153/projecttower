#pragma once
#include <SFML\Network.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include "SubController.h"
class NetworkGameServer :
	public SubController
{
public:
	NetworkGameServer(Vortex * gameEngine, int controllerID);
	~NetworkGameServer();
	void update();
	bool prepareServer();

	void setSocketNumber(int socketNumber);

	std::vector<std::vector<sf::Drawable *>> getDynamicRenderData();
	std::vector<std::vector<sf::Drawable *>> getStaticRenderData();
	sf::View getView();
	std::vector<SubController *> getChildControllers();
	void preloadAssets();

private:
	bool establishPlayerConnection();
	void threadReceivePackets();
	void threadSendPackets();

	Vortex* gameEngine;
	int controllerID;
	int socketNumber = 53000;
	
	std::mutex receivedMutex;
	std::mutex sendMutex;
	std::vector<sf::Packet> receivedPackets;
	std::vector<sf::Packet> pendingSendPackets;

	bool playerConnected = false;
	bool receivingThreadOnline = false;
	bool sendingThreadOnline = false;
	std::thread networkSendThread;
	std::thread networkReceiveThread;

	//sf::TcpSocket localPlayer;
	sf::TcpSocket otherPlayer;
	sf::TcpListener connectionListener;

};