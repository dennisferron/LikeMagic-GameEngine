
method(SharedTypes, PredefinedValues,


    GuiEvents := Object clone lexicalDo(

        appendProto(SharedTypes)
        appendProto(PredefinedValues)

        guiIdMap ::= nil

        _curId := 1000
        nextId := method(
            _curId = _curId + 1
            return _curId
        )

        init := method(
            setGuiIdMap(IdMap clone)
        )

        handle := method(event,
            id := event get_GUIEvent get_Caller getID
            evType := event get_GUIEvent get_EventType
            if(evType == EGET_BUTTON_CLICKED,
                guiEl := guiIdMap at(id)
                if (guiEl != nil,
                    if (guiEl hasSlot("onClick"),
                        guiEl onClick call(event)
                    )
                )
            )
        )

        register := method(guiEl,
            id := nextId
            guiEl setID(id)
            guiIdMap atPut(id, guiEl)
        )
    )
)
