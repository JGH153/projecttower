#include "VortexNetwork.h"


VortexNetwork::VortexNetwork(unsigned short portNumGameParm, unsigned short portNumBroadcastParm) {

	portNumGame = portNumGameParm;
	portNumBroadcast = portNumBroadcastParm;


	if (udpSocket.bind(portNumGame) != sf::Socket::Done) {
		// error...
	}

	testUdpSend();

	testBroadcast();


	broadcastSearchThreadOnline = false;
	





}

void VortexNetwork::testBroadcast(){

	sf::Packet dataPacket;
	dataPacket << (std::string)"lolTest";

	// UDP socket:
	sf::IpAddress recipient = sf::IpAddress::Broadcast;
	if (udpSocket.send(dataPacket, recipient, portNumGame) != sf::Socket::Done) {
		std::cout << "Send error";
	}

	sf::Packet dataPacket2;

	unsigned short senderPortNum;

	// UDP socket:
	sf::IpAddress senderAddress;
	if (udpSocket.receive(dataPacket2, senderAddress, senderPortNum) != sf::Socket::Done) {
		// error...
	}

	std::string data;

	dataPacket2 >> data;

	std::cout << "Data print testBroadcast (fra: " << senderAddress << "): " << data << std::endl;


}


void VortexNetwork::testUdpSend() {

	sf::Packet dataPacket;
	dataPacket << (std::string)"lolTest";

	// UDP socket:
	sf::IpAddress recipient = "127.0.0.1";
	if (udpSocket.send(dataPacket, recipient, portNumGame) != sf::Socket::Done) {
		std::cout << "Send error";
	}

	sf::Packet dataPacket2;

	unsigned short senderPortNum;

	// UDP socket:
	sf::IpAddress senderAddress;
	if (udpSocket.receive(dataPacket2, senderAddress, senderPortNum) != sf::Socket::Done) {
		// error...
	}

	std::string data;

	dataPacket2 >> data;

	std::cout << "Data print testUdpSend (fra: " << senderAddress << "): " << data << std::endl;

}


VortexNetwork::~VortexNetwork() {
}




void VortexNetwork::startBroadcastSearch() {

	if (broadcastSearchThreadOnline) {
		std::cout << "ERROR: VortexNetwork::startBroadcastSearch: broadcastSearchThreadOnline!";
		std::cin.get();
		return;
	}

	incomingBroadcastIpList.clear();

	runBroadcastThreadLoop = true;

	broadcastSearchThread = std::thread(&VortexNetwork::broadcastThreadLoop, this);



}

std::vector<sf::IpAddress> VortexNetwork::getIncomingBroadcastIpList() {

	std::lock_guard<std::mutex> guard(broadcastSearchMutex);

	auto returnList = incomingBroadcastIpList;
	incomingBroadcastIpList.clear();

	return returnList;

	



}

void VortexNetwork::stopBroadcastSearch() {

	runBroadcastThreadLoop = false;


}

void VortexNetwork::broadcastThreadLoop() {

	sf::UdpSocket udpSocketBroadcast;
	udpSocketBroadcast.setBlocking(false);

	if (udpSocketBroadcast.bind(portNumBroadcast) != sf::Socket::Done) {
		std::cout << "Unable to bind to port";
	}

	broadcastSearchThreadOnline = true;

	int broadcastValue = 42;

	std::cout << "broadcastThread Online" << std::endl;

	while (runBroadcastThreadLoop) {

		//std::cout << "Looking for broadcasts" << std::endl;

		sf::Packet sendPacket;
		sendPacket << broadcastValue;

		//send my echo
		sf::IpAddress recipient = sf::IpAddress::Broadcast;
		if (udpSocketBroadcast.send(sendPacket, recipient, portNumBroadcast) != sf::Socket::Done) {
			std::cout << "Send error";
		}



		//listen for echoes (including my own)
		sf::Packet recivePacket;
		unsigned short senderPortNum;
		sf::IpAddress senderAddress;

		do {

			auto packetStatus = udpSocketBroadcast.receive(recivePacket, senderAddress, senderPortNum);
			if (packetStatus != sf::Socket::Done) {
				//std::cout << "packetStatus: " << packetStatus << std::endl;;
				break;
			}
			
			int packetCode;

			recivePacket >> packetCode;

			std::cout <<"NEW FROM BC: " << packetCode << " IP: " << senderAddress.toString() << std::endl;

			if (!ipInBroadcastList(senderAddress)) {
				broadcastSearchMutex.lock();

				incomingBroadcastIpList.push_back(senderAddress);
				broadcastSearchMutex.unlock();
				
			}


		} while (true);



		sf::sleep(sf::milliseconds(100));




	}

	std::cout << "broadcastThread Offline" << std::endl;

	broadcastSearchThreadOnline = false;




}


bool VortexNetwork::ipInBroadcastList(sf::IpAddress ip) {

	std::lock_guard<std::mutex> guard(broadcastSearchMutex);

	for each (auto current in incomingBroadcastIpList) {
		if (current == ip)
			return true;
	}


	return false;


}
