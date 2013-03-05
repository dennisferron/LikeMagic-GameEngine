
method(NodeInteraction, Node, IrrlichtNodeAttribute, ScriptObjAnimator,

    AddScriptObjAnim := NodeInteraction clone lexicalDo(

        ScriptObjAnimator := ScriptObjAnimator

        setReferent(mapSubdomains)

        referent at("node") setTrigger(
            dispAttr : IrrlichtNodeAttribute
        )

        enter := method(
            anim := ScriptObjAnimator new(site)
            if (dispAttr sceneNode == nil,
                Exception raise("Irrlicht Node Attribute has no sceneNode")
            )
            dispAttr sceneNode addAnimator(anim)
            self
        )
    )

    Node registerInteraction(AddScriptObjAnim)

    return AddScriptObjAnim
)
