#ifndef SHARED_RES_H
#define SHARED_RES_H

struct ResourceFile;

namespace Game {
namespace Resources {
    ResourceFile& Graphics();
    ResourceFile& Main();
    ResourceFile& Scenario();
    ResourceFile& Movies();
    ResourceFile& Sfx();
    ResourceFile& Speech();
    ResourceFile& World();
}
}

#endif // SHARED_RES_H
