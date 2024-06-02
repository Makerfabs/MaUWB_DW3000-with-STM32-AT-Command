/*
For ESP32 UWB AT Demo


Use 2.0.0   Wire
Use 1.11.7   Adafruit_GFX_Library
Use 1.14.4   Adafruit_BusIO
Use 2.0.0   SPI
Use 2.5.7   Adafruit_SSD1306

*/

// User config          ------------------------------------------

// define the esp version of your device:
// #define ESP32S3
#define ESP32

// tag ID (tid):
#define UWB_INDEX 0

#define TAG
// #define ANCHOR

#define FREQ_850K
// #define FREQ_6800K

#define UWB_TAG_COUNT 32

// User config end       ------------------------------------------

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#define SERIAL_LOG Serial
#define SERIAL_AT mySerial2

HardwareSerial SERIAL_AT(2);

#ifdef ESP32
#define RESET 32

#define IO_RXD2 18
#define IO_TXD2 19

#define I2C_SDA 4
#define I2C_SCL 5

#endif

#ifdef ESP32S3
#define RESET 16

#define IO_RXD2 18
#define IO_TXD2 17

#define I2C_SDA 39
#define I2C_SCL 38

#endif

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
    pinMode(RESET, OUTPUT);
    digitalWrite(RESET, HIGH);

    SERIAL_LOG.begin(115200);

    SERIAL_LOG.print(F("Hello! ESP32-S3 AT command V1.0 Test"));
    SERIAL_AT.begin(115200, SERIAL_8N1, IO_RXD2, IO_TXD2);

    SERIAL_AT.println("AT");
    Wire.begin(I2C_SDA, I2C_SCL);
    delay(1000);
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    { // Address 0x3C for 128x32
        SERIAL_LOG.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    display.clearDisplay();

    logoshow();

    sendData("AT?", 2000, 1);
    sendData("AT+RESTORE", 5000, 1);

    sendData(config_cmd(), 2000, 1);
    sendData(cap_cmd(), 2000, 1);

    sendData("AT+SETRPT=1", 2000, 1);
    sendData("AT+SAVE", 2000, 1);
    sendData("AT+RESTART", 2000, 1);
}

long int runtime = 0;

String response = "";
String rec_head = "AT+RANGE";

void loop()
{

    // put your main code here, to run repeatedly:
    while (SERIAL_LOG.available() > 0)
    {
        SERIAL_AT.write(SERIAL_LOG.read());
        yield();
    }
    while (SERIAL_AT.available() > 0)
    {
        char c = SERIAL_AT.read();

        if (c == '\r')
            continue;
        else if (c == '\n' || c == '\r')
        {
            SERIAL_LOG.println(response);

            response = "";
        }
        else
            response += c;
    }
}

// SSD1306

void logoshow(void)
{
    display.clearDisplay();

    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);             // Start at top-left corner
    display.println(F("MaUWB DW3000"));

    display.setCursor(0, 20); // Start at top-left corner
    // display.println(F("with STM32 AT Command"));

    display.setTextSize(2);

    String temp = "";

#ifdef TAG
    temp = temp + "T" + UWB_INDEX;
#endif
#ifdef ANCHOR
    temp = temp + "A" + UWB_INDEX;
#endif
#ifdef FREQ_850K
    temp = temp + "   850k";
#endif
#ifdef FREQ_6800K
    temp = temp + "   6.8M";
#endif
    display.println(temp);

    display.setCursor(0, 40);

    temp = "Total: ";
    temp = temp + UWB_TAG_COUNT;
    display.println(temp);

    display.display();

    delay(2000);
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    // command = command + "\r\n";

    SERIAL_LOG.println(command);
    SERIAL_AT.println(command); // send the read character to the SERIAL_LOG

    long int time = millis();

    while ((time + timeout) > millis())
    {
        while (SERIAL_AT.available())
        {

            // The esp has data so display its output to the serial window
            char c = SERIAL_AT.read(); // read the next character.
            response += c;
        }
    }

    if (debug)
    {
        SERIAL_LOG.println(response);
    }

    return response;
}

String config_cmd()
{
    String temp = "AT+SETCFG=";

    // Set device id
    temp = temp + UWB_INDEX;

    // Set device role
#ifdef TAG
    temp = temp + ",0";
#endif
#ifdef ANCHOR
    temp = temp + ",1";
#endif

    // Set frequence 850k or 6.8M
#ifdef FREQ_850K
    temp = temp + ",0";
#endif
#ifdef FREQ_6800K
    temp = temp + ",1";
#endif

    // Set range filter
    temp = temp + ",1";

    return temp;
}

String cap_cmd()
{
    String temp = "AT+SETCAP=";

    // Set Tag capacity
    temp = temp + UWB_TAG_COUNT;

    //  Time of a single time slot
#ifdef FREQ_850K
    temp = temp + ",15";
#endif
#ifdef FREQ_6800K
    temp = temp + ",10";
#endif

    return temp;
}