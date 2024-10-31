#ifndef MESHNETWORK_H
#define MESHNETWORK_H

#include "painlessMesh.h"

class MeshNetwork {
  private:
    Scheduler userScheduler;

  public:
    painlessMesh mesh;
    void init(TSTRING ssid, TSTRING password, uint16_t port);
    void update();

};

#endif