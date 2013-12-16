/*
copyright
	Jonathan Wright, 2006
licence
	BSD revised
*/

#ifndef IOMESSAGE_OPSHUFFLE_DEFINED
#define IOMESSAGE_OPSHUFFLE_DEFINED 1

#include "IoMessage.h"


IoMessage *IoMessage_opShuffle(IoMessage *self, IoObject *locals, IoMessage *m);
void IoMessage_opShuffle_(IoMessage *self);

#endif
