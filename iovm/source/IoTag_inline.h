//metadoc Tag copyright Steve Dekorte 2002
//metadoc Tag license BSD revised

#include "Common_inline.h"

// state

void IoTag_state_(IoTag *self, void *state);
void *IoTag_state(IoTag *self);

// activate

void IoTag_activateFunc_(IoTag *self, IoTagActivateFunc *func);
IoTagActivateFunc *IoTag_activateFunc(IoTag *self);

// clone

void IoTag_cloneFunc_(IoTag *self, IoTagCloneFunc *func);
IoTagCloneFunc *IoTag_cloneFunc(IoTag *self);

// cleanup

void IoTag_cleanupFunc_(IoTag *self, IoTagFreeFunc *func);
IoTagCleanupFunc *IoTag_cleanupFunc(IoTag *self);

// io_free

void IoTag_freeFunc_(IoTag *self, IoTagFreeFunc *func);
IoTagFreeFunc *IoTag_freeFunc(IoTag *self);

// mark

void IoTag_markFunc_(IoTag *self, IoTagMarkFunc *func);
IoTagMarkFunc *IoTag_markFunc(IoTag *self);

// compare

void IoTag_compareFunc_(IoTag *self, IoTagCompareFunc *func);
IoTagCompareFunc *IoTag_compareFunc(IoTag *self);

// stream write

void IoTag_writeToStreamFunc_(IoTag *self, IoTagWriteToStreamFunc *func);
IoTagWriteToStreamFunc *IoTag_writeToStreamFunc(IoTag *self);

// stream alloc

void IoTag_allocFromStreamFunc_(IoTag *self, IoTagAllocFromStreamFunc *func);
IoTagAllocFromStreamFunc *IoTag_allocFromStreamFunc(IoTag *self);

// stream alloc

void IoTag_readFromStreamFunc_(IoTag *self, IoTagReadFromStreamFunc *func);
IoTagReadFromStreamFunc *IoTag_readFromStreamFunc(IoTag *self);

// notification

void IoTag_notificationFunc_(IoTag *self, IoTagNotificationFunc *func);
IoTagNotificationFunc *IoTag_notificationFunc(IoTag *self);

// perform

void IoTag_performFunc_(IoTag *self, IoTagPerformFunc *func);
IoTagPerformFunc *IoTag_performFunc(IoTag *self);
