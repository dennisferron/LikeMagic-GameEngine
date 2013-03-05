method(

    UserInterfaceRepresentation := Object clone lexicalDo(

        style ::= nil
        isMouseDraggable ::= false

        with := method(style,
            setStyle(style)
            setIsMouseDraggable(style isMouseDraggable)
        )
    )

)
