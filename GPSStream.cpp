#include <unistd.h>
#include <iostream>
#include <exception>
#include <cstring> // To enable the use of String variables in the GPS UART Stream ( ie. it grabs the lines of UART code outputted by the GPS module and stores them in a local variable)

#include "mraa.hpp"
using namespace std;

int main()
{
    // If you have a valid platform configuration use numbers to represent UART
    // device. If not use raw mode where std::string is taken as a constructor
    // parameter

    mraa::Uart* dev;
    try {
        dev = new mraa::Uart(0); //UART Constructor, takes a pin number which will map directly to the Linux UART number (check the Types.h file), this 'enables' the UART, nothing more
        // dev = new mraa::Uart(26); for Mini Breakout Board UART RX-1 (physical pin J18-13)
    } catch (std::exception& e) { // Catch any exceptions. If there are, output an error message
        cout << e.what() << "Failed to start UART. Likely invalid platform config" << endl;
    }

    try {
        dev = new mraa::Uart("/dev/ttyMFD1"); // UART Constructor, takes a string to the path of the serial interface needed.
        // dev = new mraa::Uart("/dev/ttyACM0"); for Mini Breakout Board UART RX-1 (physical pin J18-13)
    } catch (std::exception& e) { // Catch any exceptions. If there are, output an error message
        cout << "Error while setting up UART on MFD1 (Pin 0). Using Android Dev Board? Check connections" << endl;
        terminate();											// Do the setBaudRate function found in uart.hpp, and if it doesn't return a success, print the error message
    }
    	cout << endl << "UART initialized" << endl;				// Otherwise, if it returns a success, print the success message

    if (dev->setBaudRate(4800) != MRAA_SUCCESS) {
        std::cout << "Error setting Baud Rate on UART" << endl; // Do the setBaudRate function found in uart.hpp, and if it doesn't return a success, print the error message
    }
    	else cout << "Baud Rate set" << endl;					// Otherwise, if it returns a success, print the success message

    if (dev->setMode(8, MRAA_UART_PARITY_NONE, 1) != MRAA_SUCCESS) {
        std::cout << "Error setting parity on UART" << endl;	// Do the setMode function found in uart.hpp, and if it doesn't return a success, print the error message
    }
    	else cout << "Parity set" << endl;						// Otherwise, if it returns a success, print the success message

    if (dev->setFlowcontrol(false, false) != MRAA_SUCCESS) {
        std::cout << "Error setting flow control UART" << endl; // Do the setFlowControl function found in uart.hpp, and if it doesn't return a success, print the error message
    }
    	else cout << "Flow Control set" << endl;				// Otherwise, if it returns a success, print the success message

    sleep(1);
    cout << endl << "Success! ...probably" << endl << endl;
    sleep(1);

    int PinCount = mraa::getPinCount();


/*    UART DATA STREAMING*/

    cout << "=== Begin UART GPS Stream === " << endl << endl;
    sleep(1);

    for( ; ; ) // Sets up an infinite loop (For loop with no parameters)
    	{
          string UARTString1 = dev->readStr(73); // Create a string, and assign the ReadString function to it (found in mraa.hpp -> uart.hpp). Pass along the 73 character length parameter to the function
              cout << "Data: " << UARTString1 << endl; // Print the string and a line break

              string UARTString2 = dev->readStr(1); // These are all important to maintain the line output organization
              string UARTString3 = dev->readStr(1); // don't delete them
              string UARTString4 = dev->readStr(43);
              string UARTString5 = dev->readStr(1);
              string UARTString6 = dev->readStr(1);

          sleep(1);
    	}

    delete dev;

    return MRAA_SUCCESS;
}
