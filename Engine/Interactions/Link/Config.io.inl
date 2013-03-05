method(namespace, Model, Subsystems, Constants, Styles,

    LinkInteractionModule := Module clone lexicalDo(
        scripts := self scripts
        LinkInteraction := scripts LinkInteraction(Model Interaction)
        CameraFollowObject := scripts optionalCall(CameraFollowObject, LinkInteraction, Model Link, Subsystems Irrlicht, Subsystems Avatar, Styles LinkStyles)
        SelectNode := scripts SelectNode(LinkInteraction, Model Link, Subsystems Irrlicht)

        BulletMouseDrag := scripts BulletMouseDrag(LinkInteraction, Model Node, Subsystems Irrlicht UserInterface MouseDragLinkAttribute, Styles LinkStyles, Subsystems Bullet Component)
        IrrlichtMouseDrag := scripts IrrlichtMouseDrag(LinkInteraction, Subsystems Irrlicht UserInterface MouseDragLinkAttribute, Subsystems Irrlicht NodeAttribute)
    )
)
