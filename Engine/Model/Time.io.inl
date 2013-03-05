method(

Time := Object clone lexicalDo(

	events ::= nil
	deviceTimer ::= nil
	currentTime := 0
	lastTime := 0

    shouldRun ::= nil

    beforeFrame ::= nil
    beforePhysics ::= nil
    onPhysics ::= nil
    afterPhysics ::= nil
    beforeGraphics ::= nil
    onGraphics ::= nil
    afterGraphics ::= nil
    afterFrame ::= nil

	init := method(
        setEvents(List clone)

        setBeforeFrame(List clone)
        setBeforePhysics(List clone)
        setOnPhysics(List clone)
        setAfterPhysics(List clone)
        setBeforeGraphics(List clone)
        setOnGraphics(List clone)
        setAfterGraphics(List clone)
        setAfterFrame(List clone)
    )

    setDeviceTimer := method(value,
        deviceTimer = value
        currentTime = deviceTimer call
        lastTime = currentTime
        self
    )

	Event := Object clone do(
		atTime ::= nil
		action ::= nil
	)

	_processEvents := method(
		tempList := events clone
		tempList foreach(e,
			if(e atTime <= currentTime,
				nextTime := e action call
				if(nextTime > 0, setTimeout(nextTime, e action))
				events remove(e)
			)
		)

		/*
		while(events first != nil and events first atTime <= currentTime,
			e := events removeFirst
			nextTime := e action call
			if(nextTime > 0, setTimeout(nextTime, e action))
		)
		*/
	)

	_getEventPos := method(atTime,
		// Linear search; change to better algorithm if adding events gets slow.
		events foreach(i, v,
			if(v atTime >= atTime,
				return i
			)
		)
		return 0
	)

	setTimeout := method(delay, action,
		atTime := currentTime + delay
        events insertAt(
            Event clone setAtTime(atTime) setAction(action),
            _getEventPos(atTime)
        )
	)

	elapsed := method(currentTime - lastTime)

    runLoop := method(

        if( deviceTimer == nil,
            Exception raise("No deviceTimer set up in Time component.")
        )

        //Profiler profile(
            while(shouldRun call,

                lastTime = currentTime
                currentTime = deviceTimer call

                doEvent(beforeFrame)

                _processEvents

                doEvent(beforePhysics)
                doEvent(onPhysics)
                doEvent(afterPhysics)

                doEvent(beforeGraphics)
                doEvent(onGraphics)
                doEvent(afterGraphics)

                doEvent(afterFrame)
            )
        //)  // end Profiler profile
    )

    doEvent := method(handlerList,
        handlerList foreach(handler,
            handler call(currentTime - lastTime, currentTime, lastTime)
        )
    )
)

)
