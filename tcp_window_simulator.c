#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 6

typedef struct {
    int data;
    int ackMsg;
} Packet;

void sender(Packet *packets, int numPackets) {
    int baseVal = 0;
    int nextInSequence = 0;


    while (baseVal < BUFFER_SIZE) {
        for (int i = baseVal; (i < BUFFER_SIZE + baseVal) && (i < numPackets); i++) {
            printf("Sender: Sending packet %d\n", i);
        }

        for (int i = baseVal; i < baseVal + BUFFER_SIZE && i < numPackets; i++) {
            printf("Sender: Waiting for ACK of packet %d\n", i);
            if (rand() % 2 == 0) {
                packets[i].ackMsg = 1;
                printf("Sender: Received ACK for packet %d\n", i);
            }
        }

        while (baseVal < numPackets && packets[baseVal].ackMsg) {
            baseVal++;
        }
    }
    printf("Sender: All packets sent and acknowledged.\n");
}

void receiver(Packet *packets, int numPackets) {
    int expectedSeqNum = 0;

    while (expectedSeqNum < numPackets) {
        for (int i = 0; i < BUFFER_SIZE; i++) {
            printf("Receiver: Waiting for packet %d\n", expectedSeqNum + i);
            if (rand() % 2 == 0) {
                packets[expectedSeqNum + i].ackMsg = 1;
                printf("Receiver: Received packet %d\n", expectedSeqNum + i);
            }
        }

        for (int i = 0; i < BUFFER_SIZE; i++) {
            if (packets[expectedSeqNum + i].ackMsg) {
                printf("Receiver: Sending ACK for packet %d\n", expectedSeqNum + i);
            }
        }
        expectedSeqNum += BUFFER_SIZE;

    }
    printf("Receiver: All packets received and ACKs sent.\n");
}

void testTCPWindowSimulator() {
    int numPackets = 10;

    Packet packets[numPackets];

    for (int i = 0; i < numPackets; i++) {
        packets[i].data = i;
        packets[i].ackMsg = 0;
    }

    sender(packets, numPackets);
    receiver(packets, numPackets);
}

int main() {
    testTCPWindowSimulator();
    return 0;
}