#pragma once
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <iostream>
#include <SFML/Network.hpp>

#include <thread>         // std::thread
#include <mutex> // std::mutex

struct broadcastIpObject {

	sf::IpAddress ip;
	sf::Clock timeSinceLastPacket;
	bool wantToJoin;

	broadcastIpObject(sf::IpAddress ip) {
		this->ip = ip;
		wantToJoin = true;
	}

};

class VortexNetwork {
public:
	VortexNetwork(unsigned short portNumGame, unsigned short portNumBroadcast);
	~VortexNetwork();

	void startBroadcastSearch();
	std::vector<sf::IpAddress> getIncomingBroadcastIpList();
	void stopBroadcastSearch();

	void startOpenServerTCP();
	void stopOpenServerTCP();
	void connectToServer(sf::IpAddress targetIP);

	bool showMeAsServer;

private:

	bool runBroadcastThreadLoop;
	bool broadcastSearchThreadOnline;
	std::vector<broadcastIpObject> incomingBroadcastIpList;

	unsigned short portNumGame;
	unsigned short portNumBroadcast;
	sf::UdpSocket udpSocket;
	
	bool runServerAcceptThreadLoop;
	bool serverAcceptThreadOnline;

	sf::TcpListener tcpListener;
	sf::TcpSocket tcpConnection;

	std::vector<sf::Packet> receivedPackets;
	std::vector<sf::Packet> pendingSendPackets;

	std::mutex pendingPacketMutex;
	std::mutex receivedPacketMutex;
	std::mutex broadcastSearchMutex;
	std::mutex connectingMutex;

	std::thread sendThread;
	std::thread receiveThread;
	std::thread broadcastSearchThread;
	std::thread serverAcceptThread;


	void listeningThreadLoop();
	void sendingThreadLoop();
	void testUdpSend();
	void testBroadcast();

	void broadcastThreadLoop();
	bool ipInBroadcastList(sf::IpAddress ip);


	void serverAcceptClientThreadLoop();

	

};

