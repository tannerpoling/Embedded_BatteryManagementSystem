This embedded system project utilizes two Arduino boards, the Mega and the Uno, to act as the respective System and Peripheral Controllers of a Battery Management System. 
The System Controller employs a Real-Time Operating System (RTOS) to schedule, execute, and interrupt various system tasks, allocating resources and communicating with the Peripheral Controller via Serial, as well as storing measurements using the in-built EEPROM. 
The Peripheral Controller powers a touchscreen display, displaying measurements from the System Controller and sending any user input to the System Controller. 

Additionally created UML diagrams to document the inner-workings and use-cases of the embedded system.
