#ifndef VLMCS_H_
#define VLMCS_H_

#include "config.h"
#include "types.h"
#include "rpc.h"
#include "kms.h"

int SendActivationRequest(const RpcCtx sock, RESPONSE *baseResponse, REQUEST *baseRequest, RESPONSE_RESULT *result, BYTE *const hwid);

#endif /* VLMCS_H_ */

