# microbitcode
This is code for a simple demonstration to teach embedded programming to children, using the BBC microbit.


##Downloading
This software can be compiled using the ARM mbed compiler BBC Microbit. Instructions from Lancaster Unversity are available at https://lancaster-university.github.io/microbit-docs/. RX must be on a microbit with a mic, and TX on a microbit with a buzzer.

##Usage
This is a simple tx-rx demo - needing a simple buzzer and a microphone. The better the mic. the better this will work. An image can be selected with the A and B keys, and sent by pressing them together. The reciever works for by listning for ones, and giving zero if it hears nothing (the example plays quiet zeroes for illustrative purposes, but does not detect them.

##Todo
This was a simple prototype written as an example. Potential extensions are as follows:

* Tx and Rx in each one - this will allow acknowledgment etc, and two way communication.
* Addressing - Rx send an address to another microbit - allows for a simple networking example to show children
* Parity checks etc - checking for data integrity - help reduce the effect of noise
* Encryption - to avoid sniffing by malicious microbits - teaches children the need for encryption

To be a useful lab exercise more noise avoidance is needed, and more interactivity would be better for small children.
