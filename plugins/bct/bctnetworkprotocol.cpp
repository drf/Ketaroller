#include "bctnetworkprotocol.h"

#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QDebug>

namespace BctNetProtocol
{
        /************************************************************************/
        /* TCP                                                                  */
        /************************************************************************/

        int tcpSender(QIODevice *socket, const QByteArray &message)
        {
                QByteArray buff;
                tcpPacker(&buff, message);
                return socket->write(buff);
        }

        void tcpPacker(QByteArray *buff, const QByteArray &message)
        {
                QDataStream wr(buff, QIODevice::WriteOnly);
                wr.setVersion(QDataStream::Qt_4_6);

                // Leave 4 bytes empty
                wr << (quint32)0;

                qDebug() << QString(message);
                // Add the message
                wr << QString(message);

                // Go to the beginning...
                wr.device()->seek(0);

                // ... and write the packet size.
                wr << (quint32)(buff->size() - sizeof(quint32));
        }

        QString tcpReceiver(QIODevice *socket)
        {
                QDataStream inStream(socket);
                inStream.setVersion(QDataStream::Qt_4_6);

                if (socket->bytesAvailable() < (int)sizeof(quint32))
                        return QString("-1");

                qint32 blocksize = 0;
                inStream >> blocksize;

                while (socket->bytesAvailable() < blocksize)
                {
                        socket->waitForReadyRead(50);
                }

                QString tmp;
                inStream >> tmp;

                return tmp;
        }

        /************************************************************************/
        /* UDP                                                                  */
        /************************************************************************/

        int udpSender(QIODevice *socket, const UdpMessage &message)
        {
                QByteArray buff;
                QDataStream ws(&buff, QIODevice::WriteOnly);

                ws << message;

                return socket->write(buff);
        }

        void udpPacker(QByteArray *buff, const UdpMessage *message)
        {
                QDataStream wr(buff, QIODevice::WriteOnly);
                wr.setVersion(QDataStream::Qt_4_0);

                wr << message->timestamp;
                wr << message->tree;
                wr << message->control;
                wr << message->value;
        }

        UdpMessage udpReceiver(QIODevice *socket)
        {
                QDataStream inStream(socket);
                inStream.setVersion(QDataStream::Qt_4_0);

                UdpMessage message = {false, 0, 0, 0, 0.0};

                while (socket->bytesAvailable() < 16)
                {
                        socket->waitForReadyRead(10);
                }

                quint32 timestamp = 0;
                inStream >> message.timestamp;

                if (message.timestamp > 0)
                        message.isValid = true;
                else
                        return message;

                inStream >> message.tree;
                inStream >> message.control;
                inStream >> message.value;

                return message;
        }
}

QDataStream& operator<<(QDataStream& stream, const UdpMessage& message)
{
    stream << message.control << message.timestamp << message.tree << message.value;

    return stream;
}

