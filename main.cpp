// Compile using g++ -std=c++11 main.cpp -o i2c
#include <iostream>
#include <unistd.h>   // close
#include <fcntl.h>    // O_RDWR
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>  // I2C_SLAVE

using namespace std;

int main(void) {
  const std::string DEVICE = "/dev/i2c-1";
  const unsigned int BUFFER_SIZE = 10;

  int i2cfile;
  if ((i2cfile = open(DEVICE.c_str(), O_RDWR)) < 0) {
      cout << "Could not open bus" << endl;
      exit(1);
  }
  cout << "Successfully opened the i2c bus" << endl;

  const int SLAVE_ADDRESS = 0x48;          // The I2C address of the slave device
  if (ioctl(i2cfile, I2C_SLAVE, SLAVE_ADDRESS) < 0) {
      cout << "Failed to acquire bus access and/or talk to slave." << endl;
      exit(1);
  }
  cout << "Ready to communicate with slave device" << endl;

    char buffer[] = { 0x03 };

    if (write(i2cfile, buffer, 0) != 0) {
        cout << "Failed to write to the i2c device." << endl;
    } else {
        cout << "Successfully wrote to the i2c device." << endl;
        cout << std::hex << "0x" << (int)buffer[0] << endl;
    }

for(int i = 0; i < 10; i++){

        cout << std::hex << "0x" << (int)buffer[i] << endl;
    }

  close(i2cfile);

  return 0;
}