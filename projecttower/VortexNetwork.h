#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>
#include <SFML/Network.hpp>

#include <thread>         // std::thread
#include <mutex> // std::mutex

class VortexNetwork {
public:
	VortexNetwork(unsigned short portNumGame, unsigned short portNumBroadcast);
	~VortexNetwork();

	void startBroadcastSearch();
	//list gets cleared each time it's retrived
	std::vector<sf::IpAddress> getIncomingBroadcastIpList();
	void stopBroadcastSearch();

private:

	bool runBroadcastThreadLoop;
	bool broadcastSearchThreadOnline;
	std::vector<sf::IpAddress> incomingBroadcastIpList;

	unsigned short portNumGame;
	unsigned short portNumBroadcast;
	sf::UdpSocket udpSocket;

	std::vector<sf::Packet> receivedPackets;
	std::vector<sf::Packet> pendingSendPackets;

	std::mutex pendingPacketMutex;
	std::mutex receivedPacketMutex;
	std::mutex broadcastSearchMutex;

	std::thread sendThread;
	std::thread receiveThread;
	std::thread broadcastSearchThread;


	void listeningThreadLoop();
	void sendingThreadLoop();
	void testUdpSend();
	void testBroadcast();

	void broadcastThreadLoop();
	bool ipInBroadcastList(sf::IpAddress ip);

	

};

