
method(namespace, Model, Interactions, Subsystems, Styles,
    UnitTests := Module clone lexicalDo(
        scripts := self scripts
        TestScriptObjAnim := scripts TestScriptObjAnim(Model Graph, Subsystems Irrlicht, Interactions Node, Styles GameObjStyles, namespace Custom ScriptObjAnimator )
        TestCameraLookAt := scripts TestCameraLookAt(Model Graph, Interactions, Subsystems, Styles )
    )
)
