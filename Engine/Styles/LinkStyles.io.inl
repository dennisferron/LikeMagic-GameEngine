method(LinkStyle,

    LinkStyles := Module clone lexicalDo(
        LookAtStyle := LinkStyle clone setJointType("lookAt")
        MouseDragStyle := LinkStyle clone setJointType("mouseDrag")
    )
)
