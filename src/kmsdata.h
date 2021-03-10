#ifndef KMSDATA_SERVER_H
#define KMSDATA_SERVER_H

#include "config.h"

#ifndef NO_INTERNAL_DATA

    #include "types.h"

    extern uint8_t DefaultKmsData[];
    __pure size_t getDefaultKmsDataSize();

#endif // NO_INTERNAL_DATA

#endif // KMSDATA_SERVER_H

