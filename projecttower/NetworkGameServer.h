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
	void listenForPackets();

	Vortex* gameEngine;
	int controllerID;
	int socketNumber = 53000;
	
	bool playerConnected = false;
	bool listenerThreadOnline = false;
	
	std::thread listenerThread;
	std::mutex receivedMutex;
	std::mutex sendMutex;
	std::vector<sf::Packet> receivedPackets;
	std::vector<sf::Packet> pendingSendPackets;

	//sf::TcpSocket localPlayer;
	sf::TcpSocket otherPlayer;
	sf::TcpListener connectionListener;

};