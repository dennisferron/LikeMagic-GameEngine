


IoObject *IoState_tryToPerform(IoState *self,
							  IoObject *target,
							  IoObject *locals,
							  IoMessage *m)
{
	IoCoroutine *tryCoro = IoCoroutine_newWithTry(self, target, locals, m);

	if (IoCoroutine_rawException(tryCoro) != self->ioNil)
	{
		IoState_exception_(self, tryCoro);
	}

	return IoCoroutine_rawResult(tryCoro);

	return IoMessage_locals_performOn_(m, locals, target);
}

void IoCoroutine_try(IoCoroutine *self, IoObject *target, IoObject *locals, IoMessage *message)
{
}

IoCoroutine *IoCoroutine_newWithTry(void *state,
									IoObject *target,
									IoObject *locals,
									IoMessage *message)
{
	IoCoroutine *self = IoCoroutine_new(state);

	//IoCoroutine_try(self, target, locals, message);
	IoCoroutine *currentCoro = (IoCoroutine *)IoState_currentCoroutine((IoState *)IOSTATE);
	IoCoroutine_rawSetRunTarget_(self, target);
	IoCoroutine_rawSetRunLocals_(self, locals);
	IoCoroutine_rawSetRunMessage_(self, message);
	IoCoroutine_rawSetParentCoroutine_(self, currentCoro);
	IoCoroutine *self = (IoCoroutine *)context;

	IoObject *result;

	IoState_setCurrentCoroutine_(IOSTATE, self);
	//printf("%p-%p start\n", (void *)self, (void *)DATA(self)->cid);
	result = IoMessage_locals_performOn_(IOSTATE->mainMessage, self, self);

	IoCoroutine_rawSetResult_(self, result);
	IoCoroutine_rawReturnToParent(self);

    // return from newwithTry
    return self;
}

void IoCoroutine_rawRun(IoCoroutine *self)
{
}

void IoCoroutine_coroStart(void *context) // Called by Coro_Start()
{
	IoCoroutine *self = (IoCoroutine *)context;
	IoObject *result;

	IoState_setCurrentCoroutine_(IOSTATE, self);
	//printf("%p-%p start\n", (void *)self, (void *)DATA(self)->cid);
	result = IoMessage_locals_performOn_(IOSTATE->mainMessage, self, self);

	IoCoroutine_rawSetResult_(self, result);
	IoCoroutine_rawReturnToParent(self);
}
