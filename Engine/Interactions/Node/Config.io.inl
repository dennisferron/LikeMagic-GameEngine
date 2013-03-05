method(namespace, Model, Subsystems, Constants,

  NodeInteractionModule := Module clone lexicalDo(
    scripts := self scripts
    NodeInteraction := scripts NodeInteraction(Model Interaction)
    AddScriptObjAnim := scripts optionalCall(AddScriptObjAnim, NodeInteraction, Model Node, Subsystems Irrlicht NodeAttribute, namespace Custom ScriptObjAnimator           )
    MotionState := scripts requiredCall(MotionState,  NodeInteraction, Model Node, Subsystems Irrlicht, Subsystems Bullet )
    IrrlichtCamera := scripts optionalCall(IrrlichtCamera, NodeInteraction, Model Node, Subsystems Irrlicht, Subsystems Avatar,   Subsystems Time         )
    PlayerNoPhysSleep := scripts optionalCall(PlayerNoPhysSleep, NodeInteraction, Model Node, Subsystems Avatar,  Subsystems Bullet                   )
    PlayerPhysics := scripts optionalCall(PlayerPhysics, NodeInteraction, Model Node, Subsystems Avatar,  Subsystems Bullet,   Subsystems Time,  Constants  )
  )
)
