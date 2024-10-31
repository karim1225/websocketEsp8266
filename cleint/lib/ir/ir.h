#include <cstdint>
#ifndef IR_H
#define IR_H

class Ir {
public:
    Ir(int irSendPin, int irRecvPin);
    void init();
    void send(uint16_t sAddress,uint8_t sCommand);
    void startReciveTask();

private:
    void IRReciveTask();
};

#endif
