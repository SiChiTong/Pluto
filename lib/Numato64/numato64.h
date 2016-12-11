#ifndef NUMATO64_H
#define NUMATO64_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QTimer>

#define DEFAULT_NUMATO64_PORT "/dev/ttyACM0"
#define DEFAULT_BAUDRATE      115200
namespace Pluto
{

class Numato64 : public QObject
{
    Q_OBJECT

public:
    //-------------------------------------------------------------------
    // Public Api
    //-------------------------------------------------------------------

    // Constructor
    Numato64(QObject *parent=0);

    class Status
    {
    public:
        int analog[24];    // 0-23  analog inputs
        bool digital[40];  // 24-63 digital i/o
    };

    // Connects to the board.
    int connectToBoard(QString portName="", int baudrate=0);

    // Disconnects from the board.
    int disconnectFromBoard();

    // Returns true if connected to board else false.
    bool isConnected();

    // Returns the Status object containing updated data.
    Status getUpdatedData();

    //-------------------------------------------------------------------
    // Public Signals
    //-------------------------------------------------------------------

signals:

    // Emitted when new analog and digital io data is available.
    void updateAvailable();



    //-------------------------------------------------------------------
    // Private
    //-------------------------------------------------------------------

private:
    bool mConnected;
    Status mStatus;
    QString mPortName;
    int mBaudrate;
    QSerialPort *mSerialPort;
    QTimer mStatusTimer;

    void _readUpdate();
    void _queryUpdate();
};

}
#endif // NUMATO64_H
