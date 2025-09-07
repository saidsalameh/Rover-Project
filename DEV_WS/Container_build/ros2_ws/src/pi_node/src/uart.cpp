#include <string>
#include <stdexcept>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "uart.hpp"

class RaspberryUART {
private:
    int serialPort = -1;
    std::string devicePath;
    int baudRate;
    std::thread rx_Thread;
    bool rx_Running = false;
    std::queue<uint8_t> rx_buffer;
    std::mutex bufferMutex;

    void setupSerialPort() {
        serialPort = open(devicePath.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
        if (serialPort == -1) {
            throw std::runtime_error("Failed to open device: " + devicePath);
        }

        struct termios options;
        tcgetattr(serialPort, &options);

        speed_t baud;
        switch (baudRate) {
            case 9600:   baud = B9600; break;
            case 19200:  baud = B19200; break;
            case 38400:  baud = B38400; break;
            case 57600:  baud = B57600; break;
            case 115200: baud = B115200; break;
            default:
                throw std::invalid_argument("Unsupported baud rate");
        }

        cfsetispeed(&options, baud);
        cfsetospeed(&options, baud);

        options.c_cflag &= ~PARENB;   // No parity
        options.c_cflag &= ~CSTOPB;   // 1 stop bit
        options.c_cflag &= ~CSIZE;    // character size map
        options.c_cflag |= CS8;       // 8 data bits
        options.c_cflag &= ~CRTSCTS;  // Disable hardware flow control
        options.c_cflag |= CREAD | CLOCAL;

        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        options.c_oflag &= ~OPOST;

        // OPOST : Enable implementation-defined output processing

        options.c_cc[VMIN] = 0;
        options.c_cc[VTIME] = 1;

        tcsetattr(serialPort, TCSANOW, &options);
    }

    void receiverThread(){
        uint8_t local_rx_buffer[256];

        while(rx_Running){
            size_t bytesRead = read(serialPort,rx_buffer,sizeof(rx_buffer));
            if(bytesRead > 0){
                std::lock_guard<std::mutex> lock(bufferMutex);
                for(int i = 0; i < bytesRead; i++){
                    rx_buffer.push(local_rx_buffer[i]);
                }
                
            }
            // need to define a signal
            // std::this_thread::sleep_until
        }

    }

public:
    RaspberryUART(const std::string& path, int baud) 
        : devicePath(path), baudRate(baud) {
        setupSerialPort();
    }

    ~RaspberryUART() {
        if (serialPort != -1) {
            close(serialPort);
        }
    }
};
