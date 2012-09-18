
#include "IoMessage.h"

#ifdef __cplusplus
extern "C" {
#endif

// Step Next and Step Out have (have to have) doppelganger
// run-modes.  This is because the command to step-next
// or step-out must be converted to a local variable
// and then the mode changed to a run-mode in order to
// not trigger step-breaks in the recursive calls.
// Although we could use plain run-mode for this purpose,
// we also want to avoid breaking again if a breakpoint
// lower down led to a change in the user command
// to not step next or step out.
typedef enum {
    StepMode_Run=0,
    StepMode_StopOnAnyMessage,
    StepMode_StepNext,
    StepMode_RunNext,
    StepMode_StepOut,
    StepMode_RunOut
} StepMode_t;

void iovm_set_pending_breakpoints(IoMessage *self);

StepMode_t iovm_hit_breakpoint(void* bp,
    void *target, void *locals, void *m);

StepMode_t iovm_step_stop(
    void *target, void *locals, void *m);

#ifdef __cplusplus
}
#endif
