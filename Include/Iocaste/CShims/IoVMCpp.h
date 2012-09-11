
#include "IoMessage.h"

#ifdef __cplusplus
extern "C" {
#endif

void iovm_set_pending_breakpoints(IoMessage *self);
void iovm_hit_breakpoint(void* bp,
    void *self, void *locals, void *m);

#ifdef __cplusplus
}
#endif
