//TODO: Why is gameObj nil in mouse drag method?
//It is because the AddScriptObjAnim interaction is never entered
//TODO: Why is this interaction not working?
method(Graph, Irrlicht, NodeInteractions, Styles, ScriptObjAnimator,

    TestScriptObjAnim := Object clone lexicalDo(

        Graph := Graph
        Irrlicht := Irrlicht
        NodeInteractions := NodeInteractions
        Styles := Styles
        ScriptObjAnimator := ScriptObjAnimator

        run := method(
            graph := Graph clone
            graph addComponent(
                irrComp := Irrlicht Component clone
            )
            node := graph addNode(Styles BallStyle clone)
            attr := node findAttribute(Irrlicht NodeAttribute)
            anim := ScriptObjAnimator findIn(attr sceneNode)
            if(anim == nil,
                Exception raise("Did not find script obj anim on scene node")
            ,
                writeln("Successfully got script obj anim from scene node ", anim)
            )
        )
    )
)
