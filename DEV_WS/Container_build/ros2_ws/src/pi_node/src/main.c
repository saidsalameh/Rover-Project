#include <iostream>
#include <string>
// Include your header from the 'include' directory
#include "uart.hpp"

int main() {
    try {
        // Initialize UART - use the correct device for your Pi
        // Common options: "/dev/ttyS0", "/dev/serial0", "/dev/ttyAMA0"
        RaspberryUART uart("/dev/serial0", 115200);
        
        std::cout << "Listening for UART data on /dev/serial0. Press Ctrl+C to exit." << std::endl;
        
        while (true) {
            // Check for and print any complete lines received
            if (uart.dataAvailable()) {
                std::string line = uart.readLine();
                if (!line.empty()) {
                    std::cout << "Received: " << line << std::endl;
                }
            }
            // Small sleep to prevent high CPU usage
            usleep(10000); // Sleep for 10 milliseconds
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
