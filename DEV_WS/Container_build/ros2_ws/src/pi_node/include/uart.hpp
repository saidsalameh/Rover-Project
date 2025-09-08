#include <string>
#include <stdexcept>
#include <queue>
#include <mutex>
#include <thread>
#include <iostream> // For cout in the example
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

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
        options.c_cflag &= ~CSIZE;    // Clear character size bits
        options.c_cflag |= CS8;       // 8 data bits
        options.c_cflag &= ~CRTSCTS;  // Disable hardware flow control
        options.c_cflag |= CREAD | CLOCAL; // Enable receiver, ignore modem controls

        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Raw input mode
        options.c_oflag &= ~OPOST; // Raw output mode

        options.c_cc[VMIN] = 0;  // read() returns immediately with any data
        options.c_cc[VTIME] = 1; // 0.1 second inter-character timer

        if (tcsetattr(serialPort, TCSANOW, &options) != 0) {
            close(serialPort);
            throw std::runtime_error("Error configuring serial port");
        }
    }

    void receiverThread() {
        uint8_t byte;
        while (rx_Running) {
            // Read one byte at a time
            ssize_t bytesRead = read(serialPort, &byte, 1);
            if (bytesRead == 1) {
                std::lock_guard<std::mutex> lock(bufferMutex);
                rx_buffer.push(byte);
            } else if (bytesRead < 0) {
                // Handle read error (e.g., break condition)
                break;
            }
            // Short sleep to prevent CPU spinning (optional)
            usleep(1000);
        }
    }

public:
    RaspberryUART(const std::string& path, int baud) 
        : devicePath(path), baudRate(baud) {
        setupSerialPort();
        // Start the receiver thread automatically
        rx_Running = true;
        rx_Thread = std::thread(&RaspberryUART::receiverThread, this);
    }

    ~RaspberryUART() {
        rx_Running = false;
        if (rx_Thread.joinable()) {
            rx_Thread.join();
        }
        if (serialPort != -1) {
            close(serialPort);
        }
    }

    // Check if data is available
    bool dataAvailable() {
        std::lock_guard<std::mutex> lock(bufferMutex);
        return !rx_buffer.empty();
    }

    // Read a single byte from the buffer
    bool readByte(uint8_t &byte) {
        std::lock_guard<std::mutex> lock(bufferMutex);
        if (rx_buffer.empty()) {
            return false;
        }
        byte = rx_buffer.front();
        rx_buffer.pop();
        return true;
    }

    // Read a line of text (until newline or buffer full)
    std::string readLine() {
        std::string line;
        uint8_t byte;
        while (readByte(byte)) {
            if (byte == '\n' || byte == '\r') {
                break;
            }
            line += static_cast<char>(byte);
        }
        return line;
    }
};
