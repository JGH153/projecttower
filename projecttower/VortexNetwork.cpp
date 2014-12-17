#include "VortexNetwork.h"


VortexNetwork::VortexNetwork(unsigned short portNumGameParm, unsigned short portNumBroadcastParm) {

	portNumGame = portNumGameParm;
	portNumBroadcast = portNumBroadcastParm;

	//auto udpBindStatus = udpSocket.bind(portNumGame);
	////auto udpBindStatus = udpSocket.bind(portNumGame);
	//if (udpBindStatus != sf::Socket::Done) {
	//	// error...
	//	std::cout << "fatal error setup UDP(" << udpBindStatus << ")(" << sf::UdpSocket::MaxDatagramSize<<")" << std::endl;
	//}

	

	//testUdpSend();

	//testBroadcast();


	broadcastSearchThreadOnline = false;
	

	showMeAsServer = false;

	serverAcceptThreadOnline = false;

	connectedByTCP = false;

	runReceiveTcpThreadLoop = false;
	receiveTcpThreadOnline = false;

	runSendTcpThreadLoop = false;
	sendTcpThreadOnline = false;

	newPacketsReady = false;



}

void VortexNetwork::testUdpSend() {

	std::cout << "Start udp test\n";

	sf::Packet dataPacket;
	dataPacket << (std::string)"lolTest";

	// UDP socket:
	sf::IpAddress recipient = "127.0.0.1";
	//NB! You need to send to same port as you binded the udp socet to or you get an error, what??!?
	if (udpSocket.send(dataPacket, recipient, udpSocket.getLocalPort()) != sf::Socket::Done) {
		std::cout << "Send error\n";
	}

	sf::Packet dataPacket2;

	unsigned short senderPortNum;

	// UDP socket:
	sf::IpAddress senderAddress;
	auto receiveStatus = udpSocket.receive(dataPacket2, senderAddress, senderPortNum);
	if (receiveStatus != sf::Socket::Done) {
		// error...
		std::cout << "Receive error (" << receiveStatus << ")\n";
	}

	std::string data;

	dataPacket2 >> data;

	std::cout << "Data print testUdpSend (fra: " << senderAddress << ":" << senderPortNum << "): " << data << std::endl;

}

void VortexNetwork::testBroadcast(){

	std::cout << "Start testBroadcast test\n";

	sf::Packet dataPacket;
	dataPacket << (std::string)"lolTest";

	// UDP socket:
	sf::IpAddress recipient = sf::IpAddress::Broadcast;
	if (udpSocket.send(dataPacket, recipient, udpSocket.getLocalPort()) != sf::Socket::Done) {
		std::cout << "Send error\n";
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





VortexNetwork::~VortexNetwork() {
}







void VortexNetwork::startTcpConnectionHandlerThreads() {

	runSendTcpThreadLoop = true;
	sendTcpThreadOnline = false;

	runReceiveTcpThreadLoop = true;
	receiveTcpThreadOnline = false;

	sendThread = std::thread(&VortexNetwork::sendTcpThreadLoop, this);
	receiveThread = std::thread(&VortexNetwork::receiveTcpThreadLoop, this);

	connectedByTCP = true;

}




void VortexNetwork::sendTcpThreadLoop() {

	sendTcpThreadOnline = true;
	tcpConnection.setBlocking(true);

	sf::Packet packet;

	while (runSendTcpThreadLoop) {


		pendingSendPacketMutex.lock();
		if (!pendingSendPackets.empty()) {

			packet = pendingSendPackets.back();
			pendingSendPackets.pop_back();

		} else {
			//a bit of sleepi and restart while loop
			pendingSendPacketMutex.unlock();
			sf::sleep(sf::milliseconds(15));
			continue;
		}
		pendingSendPacketMutex.unlock();

		
		sf::Socket::Status status = tcpConnection.send(packet);

		if (status != sf::Socket::Done) {
			std::cout << "ERROR: sendTcpThreadLoop status(" << status << ")" << std::endl;
			std::cin.get();
		}



	}
	sendTcpThreadOnline = false;


}

void VortexNetwork::receiveTcpThreadLoop() {

	receiveTcpThreadOnline = true;
	tcpConnection.setBlocking(true);

	while (runReceiveTcpThreadLoop) {

		sf::Packet packet;
		sf::Socket::Status status = tcpConnection.receive(packet);

		if (status != sf::Socket::Done) {
			std::cout << "ERROR: receiveTcpThreadLoop status(" << status << ")" << std::endl;
			std::cin.get();
		}

		receivedPacketMutex.lock();
		receivedPackets.push_back(packet);
		receivedPacketMutex.unlock();
		newPacketsReady = true;

	}

	receiveTcpThreadOnline = false;

}

bool VortexNetwork::sendTcpPacket(sf::Packet packet) {

	if (!connectedByTCP) {
		std::cout << "ERROR: sendTcpPacket: !connectedByTCP" << std::endl;
		return false;
	}

	pendingSendPacketMutex.lock();
	pendingSendPackets.push_back(packet);
	pendingSendPacketMutex.unlock();



}
std::vector<sf::Packet> VortexNetwork::getTcpPackets() {

	receivedPacketMutex.lock();

	auto retunList = receivedPackets;
	receivedPackets.clear();
	newPacketsReady = false;
	receivedPacketMutex.unlock();

	return retunList;

}











bool VortexNetwork::connectToServer(sf::IpAddress targetIP) {

	std::cout << "Attemting to connect to (" << targetIP.toString() << ")" << std::endl;

	sf::Socket::Status status = tcpConnection.connect(targetIP, portNumGame);
	if (status != sf::Socket::Done) {
		std::cout << "ERROR: Unable to connect to server: connectToServer(" << targetIP.toString()<<")" << std::endl;
		std::cin.get();
		return false;
	}


	std::cout << "Connect succcessfull" << std::endl;

	startTcpConnectionHandlerThreads();
	iAmTheServer = false;

	return true;

}


void VortexNetwork::startOpenServerTCP() {

	if (serverAcceptThreadOnline) {
		std::cout << "ERROR: VortexNetwork::startServerTCP: serverAcceptThreadOnline!";
		std::cin.get();
		return;
	}

	runServerAcceptThreadLoop = true;
	serverAcceptThreadOnline = false;

	serverAcceptThread = std::thread(&VortexNetwork::serverAcceptClientThreadLoop, this);

}

void VortexNetwork::stopOpenServerTCP() {

	runServerAcceptThreadLoop = false;

}



void VortexNetwork::serverAcceptClientThreadLoop() {

	bool clientConnected = false;

	if (tcpListener.listen(portNumGame) != sf::Socket::Done) {
		// error...
		std::cout << "fatal error setup TCP" << std::endl;
	}

	tcpListener.setBlocking(true);

	serverAcceptThreadOnline = true;



	while (runServerAcceptThreadLoop) {

		std::cout << "SERVER LETER!\n";

		if (tcpListener.accept(tcpConnection) == sf::Socket::Done) {
			runServerAcceptThreadLoop = false;
			clientConnected = true;
			std::cout << "CLIENT CONNECT!\n";
		}

		sf::sleep(sf::milliseconds(100));



	}

	tcpListener.close();

	if (clientConnected) {
		startTcpConnectionHandlerThreads();
		iAmTheServer = true;
	}

	serverAcceptThreadOnline = false;

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

	std::vector<sf::IpAddress> returnList;

	int broadcastClientTimeoutMs = 800;

	for (int i = 0; i < incomingBroadcastIpList.size(); i++) {

		if (incomingBroadcastIpList[i].timeSinceLastPacket.getElapsedTime().asMilliseconds() > broadcastClientTimeoutMs) {

			//std::cout << "Removing due to old age\n";
			incomingBroadcastIpList.erase(incomingBroadcastIpList.begin() + i);
			i--;

		} else {

			returnList.push_back(incomingBroadcastIpList[i].ip);

		}



	}

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

	int broadcastValue = 1;

	std::cout << "broadcastThread Online" << std::endl;

	while (runBroadcastThreadLoop) {

		//std::cout << "Looking for broadcasts" << std::endl;

		//only send myself if TCP socet is awaiting connection
		if (showMeAsServer) {

			sf::Packet sendPacket;
			sendPacket << broadcastValue;

			//send my echo
			sf::IpAddress recipient = sf::IpAddress::Broadcast;
			if (udpSocketBroadcast.send(sendPacket, recipient, udpSocketBroadcast.getLocalPort()) != sf::Socket::Done) {
				std::cout << "Send error";
			}

		}



		//listen for echoes (including my own)
		sf::Packet recivePacket;
		unsigned short senderPortNum;
		sf::IpAddress senderAddress;

		do {

			auto packetStatus = udpSocketBroadcast.receive(recivePacket, senderAddress, senderPortNum);
			if (packetStatus != sf::Socket::Done) {
				//std::cout << "packetStatus: " << packetStatus << std::endl;;
				//std::cout << "receive broadcastloop error (" << packetStatus<<")";
				break;
			}
			
			int packetCode;

			recivePacket >> packetCode;

			//std::cout <<"NEW FROM BC: " << packetCode << " IP: " << senderAddress.toString() << std::endl;

			if (!ipInBroadcastList(senderAddress) && packetCode == broadcastValue) {
				broadcastSearchMutex.lock();

				incomingBroadcastIpList.push_back(broadcastIpObject(senderAddress));
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

	for (int i = 0; i < incomingBroadcastIpList.size(); i ++) {
		if (incomingBroadcastIpList[i].ip == ip) {
			incomingBroadcastIpList[i].timeSinceLastPacket.restart();
			return true;
		}
	}


	return false;


}
