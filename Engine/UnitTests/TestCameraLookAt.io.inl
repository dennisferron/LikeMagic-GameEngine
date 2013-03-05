method(Graph, Interactions, Subsystems, Styles,

    TestCameraLookAt := Object clone lexicalDo(

        Graph := Graph
        Irrlicht := Subsystems Irrlicht
        Avatar := Subsystems Avatar
        Time := Subsystems Time
        Interactions := Interactions
        Styles := Styles

        run := method(
            graph := Graph clone
            graph addComponent(
                irrComp := Irrlicht Component clone
            )
            graph addComponent(
                avatarComp := Avatar Component clone
            )
            graph addComponent(
                timeComp := Time clone
            )

            avatarCameraNode := graph addNode(Styles GameObjStyles EmptyStyle)

            writeln("Check IrrlichtCamera")
            avatarCameraNode addAttribute(Avatar Camera clone, Interactions Node IrrlichtCamera)
            writeln("done checking IrrlichtCamera")

            playerNode := graph addNode(Avatar PlayerStyle)
            avatarComp attachControl(playerNode)

            link := graph addLink(Styles LinkStyles LookAtStyle, avatarCameraNode, playerNode)

            writeln("check CameraFollowObject")
            link domain checkInteraction(Interactions Link CameraFollowObject)
            writeln("done checking CameraFollowObject")

            writeln("unit test done")
        )
    )
)
