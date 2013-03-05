
method(namespace_irr, EnumMap,

EventDispatch := Object clone lexicalDo(

    appendProto(namespace_irr)
    appendProto(namespace_irr core)
    appendProto(namespace_irr custom)

    EnumMap := EnumMap

    eventReceiver ::= nil

    menu ::= nil

    handlerMap ::= nil
)


EventDispatch init := method(

    setHandlerMap(EnumMap clone)

    setEventReceiver(
        ScriptedEventReceiver new(
            block(event, handlerMap at(event get_EventType) ?call(event); false)
        )
    )

)

EventDispatch addHandler := method(enum, handler,
    handlerMap atPut(enum, handler)
)

return EventDispatch

)
