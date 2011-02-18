#include <PacketListener.h>
#include <IpEndpointName.h>
#include <UdpSocket.h>
#include <ostream>
#include <iostream>
#include <cstdio>

class Handler : public PacketListener {
public:
    Handler();
    void ProcessPacket( const char *data, int size, const IpEndpointName &remoteEndpoint );
    UdpListeningReceiveSocket *socket;
    UdpTransmitSocket *send1socket;
    UdpTransmitSocket *send2socket;
};

int main(int argc, char **argv)
{
    new Handler;
}

Handler::Handler()
{
    try {
            socket = new UdpListeningReceiveSocket(IpEndpointName( IpEndpointName::ANY_ADDRESS, 3334 ), this );
    } catch (std::exception &e) {
            socket = NULL;
    }

    if (socket!=NULL) {
            if (!socket->IsBound()) {
                    delete socket;
                    socket = NULL;
            } else std::cout << "listening to TUIO messages on UDP port " << 3334 << std::endl;
    }

    try {
                send1socket = new UdpTransmitSocket(IpEndpointName(127,0,0,1, 3333));
                send2socket = new UdpTransmitSocket(IpEndpointName(131,175,18,221, 3333));
        } catch (std::exception &e) {
                std::cout << "could not create socket" << std::endl;
                socket = NULL;
        }

    socket->Run();
    
}

void Handler::ProcessPacket(const char* data, int size, const IpEndpointName& remoteEndpoint)
{
    send1socket->Send(data, size);
    send2socket->Send(data, size);
}

