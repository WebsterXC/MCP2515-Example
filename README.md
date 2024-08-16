# MCP2515-Example
An example implementation of the Microchip MC2515 CAN Controller.

This project uses a PIC32MX130F064B to interface with the MCP2515. 

This software sends CAN message 0x18FABC33 with increasing values in the data bytes. It is configured for a bus speed of 250k.

Paired with an MCP2562 CAN transciever, this code has been tested working using both a Kvaser Leaf Lite and PCAN IPEH-002021.

All MPLABX project files are included. If you're looking for just the source code, it's in MCP2515-Example.X/src.
