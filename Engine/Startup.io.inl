writeln("Engine startup")

LM_Protos := namespace
PredefinedValues := LM_Protos

Module := doRelativeFile("Module.io.inl")
Scripts := doRelativeFile("Scripts.io.inl")
Loader :=  doRelativeFile("Loader.io.inl")

writeln("io_vm is ", io_vm)
writeln("io_vm get_script_path is ", io_vm get_script_path)

thisScriptPath := io_vm get_script_path
writeln("thisScriptPath is ", thisScriptPath)

rootLoader := Loader clone setDirectory(
    Directory clone setPath(
        thisScriptPath
    )
)

Constants := Object clone lexicalDo(
    TAU := if(LM_Protos hasSlot("TAU"), LM_Protos TAU, 2*3.1459)    // Comes from Custom
    AllFilter := if(LM_Protos hasSlot("AllFilter"), LM_Protos AllFilter, 65535) // Comes from Irrlicht
    CameraFilter := 64
    FrameSeconds := 1 / 64
    timeStep := FrameSeconds
    mouseDraggableBitPos  := 31
    mouseDraggableBitMask := (1 << 31)
)

RootModule := Module clone

RootModule lexicalDo (

    // Don't use "WayUpDir" for new code; instead load textures from
    // the Irrlicht Component Assets object.  For other files,
    // figure out on case-by-case basis where the code should go.
    WayUpDir := method(assetPath, thisScriptPath .. "../" .. assetPath)

    // Convenience method
    vector3dfAsString := method(v,
        return "(" .. v get_X .. "," .. v get_Y .. "," .. v get_Z .. ")"
    )

    // Convenience method
    line3dfAsString := method(line,
        return vector3dfAsString(line get_start) .. "->" .. vector3dfAsString(line get_end)
    )
)

// When copying C++ example code the numbers are often appended with "f" for float.
// This is not usually the syntax in Io, but defining the f method on Number
// makes it so e.g. 1.23f resolves to 1.23 (in Io all numbers are doubles already).
Number f := method(self)

writeln("Loading scripts")
rootScripts := rootLoader loadAllScriptsExcept(list("Startup.io.inl", "Module.io.inl", "LikeMagic", "Loader.io.inl", "Scripts.io.inl"))
writeln("Done loading scripts")

writeln("Creating game protos")
rootScripts Config( RootModule, LikeMagicModule, Constants )
writeln("Done creating game protos")

e := try(
    //writeln("Running unit tests")
    // TODO:  Why is AddScriptObjAnim having type "Object"?
    //RootModule UnitTests TestScriptObjAnim clone run
    //RootModule UnitTests TestCameraLookAt clone run
    //writeln("Done running unit tests")
    nil
)
if (e != nil,
    writeln("Unit test failed with error: ", e)
    writeln("Unit test failed with error caughtMessage: ", e caughtMessage)
    if( e caughtMessage != nil,
        writeln("line number: ", e caughtMessage lineNumber)
    )
    if( e originalCall != nil,
        if( e originalCall target != nil,
            writeln("original call target was ", e originalCall target)
        )
    )
    e showStack
)

//Exception raise("Done running unit tests")

writeln("RootModule is ", RootModule)
graph := RootModule Model Graph clone

loadError := try(

writeln("Adding components to graph.")

graph addComponent(
    irrComp := RootModule Irrlicht Component clone
)
irrComp setGraph(graph)

graph addComponent(
    RootModule Bullet Component clone
)

avatarComp := RootModule Avatar Component clone
graph addComponent(
    avatarComp
)

editorGUI := RootModule EditorGUI Component clone
graph addComponent(
    editorGUI
    , RootModule Interactions Component LoadEditorGUI
)

time := RootModule Model Time clone
graph addComponent(time)

writeln("Done adding components to engine.")

RootModule lexicalDo(
    avatarCameraNode := graph addNode(Styles GameObjStyles EmptyStyle)
    avatarCameraNode addAttribute(Avatar Camera clone)

    playerNode := graph addNode(Avatar PlayerStyle)
    avatarComp attachControl(playerNode)

    graph addLink(Styles LinkStyles LookAtStyle, avatarCameraNode, playerNode)
)

)

if (loadError != nil,
    writeln("error: ", loadError)
    writeln("error caughtMessage: ", loadError caughtMessage)
    if( loadError caughtMessage != nil,
        writeln("line number: ", loadError caughtMessage lineNumber)
    )
    if( loadError originalCall != nil,
        if( loadError originalCall target != nil,
            writeln("original call target was ", loadError originalCall target)
        )
    )
    loadError showStack
)
