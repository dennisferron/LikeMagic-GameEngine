
//metadoc State copyright Steve Dekorte 2002
//metadoc State license BSD revised

#include "Common_inline.h"

// booleans --------------------------------------------------------

#define SIOSYMBOL(stringConstant) IoState_symbolWithCString_(self, stringConstant)

#define IOASSERT(value, message) \
if (!(value)) { IoState_error_(IOSTATE, m, "Io Assertion '%s'", message); }

#define IOCOLLECTOR (IOSTATE->collector)

#define IONIL(self) (IOSTATE->ioNil)
#define ISNIL(self) (self == IOSTATE->ioNil)

// booleans --------------------------------------------------------

#define ISBOOL(self) (((self)==IOSTATE->ioFalse) \
				   || ((self)==IOSTATE->ioNil)   \
				   || ((self)==IOSTATE->ioTrue))

#define IOSUCCESS(self) IOTRUE(self)
#define ISSUCCESS(self) ISTRUE(self)

#define IOFAILURE(self) IOFALSE(self)
#define ISFAILURE(self) ISFALSE(self)

//inline IoObject *IOBOOL(IoObject *self, int b);

#if !defined(IoObjectDataDefined)
typedef struct IoObjectData IoObjectData;
#endif

IoObject *IOTRUE(IoObject *self);
int ISTRUE(IoObject *self);
IoObject *IOFALSE(IoObject *self);
int ISFALSE(IoObject *self);
IoObject *IOBOOL(IoObject *self, int b);

// collector --------------------------------------------------------

IoObject *IoState_retain_(IoState *self, IoObject *v);
void IoState_stopRetaining_(IoState *self, IoObject *v);
void *IoState_unreferencedStackRetain_(IoState *self, IoObject *v);
void *IoState_stackRetain_(IoState *self, IoObject *v);
void IoState_addValue_(IoState *self, IoObject *v);
void IoState_addValueIfNecessary_(IoState *self, IoObject *v);
void IoState_pushCollectorPause(IoState *self);
void IoState_popCollectorPause(IoState *self);
void IoState_clearRetainStack(IoState *self);
uintptr_t IoState_pushRetainPool(void *self);
void IoState_clearTopPool(void *self);
void IoState_popRetainPool(void *self);
void IoState_popRetainPool_(void *self, uintptr_t mark);
void IoState_popRetainPoolExceptFor_(void *state, void *obj);

// message args --------------------------------------------------------

#define IOMESSAGEDATA(self) ((IoMessageData *)IoObject_dataPointer(self))

IoObject *IoMessage_locals_quickValueArgAt_(IoMessage *self, IoObject *locals, int n);
IoObject *IoMessage_locals_valueArgAt_(IoMessage *self, IoObject *locals, int n);
IoObject *IoMessage_locals_firstStringArg(IoMessage *self, IoObject *locals);

// --------------------------

void IoState_break(IoState *self, IoObject *v);
void IoState_continue(IoState *self);
void IoState_eol(IoState *self);
void IoState_return(IoState *self, IoObject *v);
void IoState_resetStopStatus(IoState *self);
int IoState_handleStatus(IoState *self);
IoObject *IoState_stopStatusObject(IoState *self, int stopStatus);
int IoState_stopStatusNumber(IoState *self, IoObject *obj);
