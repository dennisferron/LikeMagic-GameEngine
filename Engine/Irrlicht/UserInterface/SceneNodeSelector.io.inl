
method(

SceneNodeSelector := Object clone lexicalDo(

    sceneNode ::= nil

    select := method(attr,
        setSceneNode(attr)
    )

    deselect := method(attr,
        if(sceneNode == attr,
            setSceneNode(nil)
        ,
            writeln("Deselected wrong scene node (or in wrong order). Current selection was: ", sceneNode, " asked to deselect ", attr)
        )
    )
)

)
