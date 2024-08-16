# MCP2515-Example
An example implementation of the Microchip MC2515 CAN Controller.

This project uses a PIC32MX130F064B to interface with the MCP2515. 

This software repeatedly sends CAN message 0x18FABC33 with increasing values in the data bytes. It is configured for a bus speed of 250k assuming an oscillator frequency of 10MHz. Paired with an MCP2562 CAN transciever, this code has been tested working using both a Kvaser Leaf Lite and PCAN IPEH-002021.

This project was breadboarded; to aid in debugging, the PIC32 also initializes UART2 to send data to an MCP2221A USB transciever (115200 baud). I've provided a short Powershell script that will read this terminal output, but you may need to edit 'COM3' to whatever your USB-UART bridge ends up enumerating to.

All MPLABX project files are included. If you're looking for just the source code, it's in _MCP2515-Example.X/src_.

I have also included the breadboard schematic. It is a **bare-minimum** implementation that gets things to work - it leaves a lot of room for improvement. Yes, all capacitors and resistors are required (ask me how I know).

# Kvaser CAN King Output
![CAN King Output](https://github.com/WebsterXC/MCP2515-Example/blob/main/schematics/CANKing_Output.PNG)
