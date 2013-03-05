method(

Referent := Object clone lexicalDo(

    Trigger := Object clone do(
        findProto ::= nil
        withSlot ::= ""
        triggeredBy := method(r, r hasProto(findProto))
    )

    triggers ::= nil

    init := method(
        setTriggers(list())
    )

    setTrigger := method(
        for(i, 0, call argCount - 1,
            arg := call argAt(i)
            slot := arg name
            colon := arg next name
            if (colon != ":",
                Exception raise("Expected ':' following ", slot)
            )
            proto := arg next next doInContext(call sender)
            triggers append(Trigger clone setFindProto(proto) setWithSlot(slot))
        )
    )

    hasOneTrigger := method(rep,
        triggers select(t, t triggeredBy(rep)) size > 0
    )

    isFullyTriggeredBy := method(objs,
        if( objs == nil,
            Exception raise("error, objs list argument to referent isFullyTriggeredBy cannot be nil")
        )
        triggers select(t,
            objs select(
                obj, t triggeredBy(obj)
            ) size > 0
        ) size == triggers size
    )

    fillSlots := method(target, objs,
        if( objs == nil ,
            Exception raise("Referent fillSlots, objs list cannot be nil!")
        )
        triggers foreach(t,
            foundObj := false
            objs foreach(obj,
                if(t triggeredBy(obj),
                    target setSlot(t withSlot, obj)
                    foundObj = true
                )
            )
            if(foundObj not,
                Exception raise("Error, failed to find an object for interaction slot " .. t withSlot)
            )
        )
        return target
    )
)

)
