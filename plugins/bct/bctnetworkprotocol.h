#ifndef BCT_NETWORK_PROTOCOL
#define BCT_NETWORK_PROTOCOL

#include <QString>
#include <QByteArray>
#include <qdatastream.h>

typedef struct{
        bool            isValid;
        quint32         timestamp;
        quint16         tree;
        quint16         control;
        double          value;
}UdpMessage;

class QIODevice;

namespace BctNetProtocol
{

        // TCP

        int                                     tcpSender(QIODevice *socket,
                                                                  const QByteArray &message);

        void                            tcpPacker(QByteArray *inData,
                                                                  const QByteArray &message);

        QString                         tcpReceiver(QIODevice *socket);



        // UDP

        int                                     udpSender(QIODevice *socket,
                                                                  const UdpMessage &message);

        void                            udpPacker(QByteArray *inData,
                                                                  const UdpMessage &message);

        UdpMessage                      udpReceiver(QIODevice *socket);
}

QDataStream &operator<<(QDataStream &, const UdpMessage &);

#endif