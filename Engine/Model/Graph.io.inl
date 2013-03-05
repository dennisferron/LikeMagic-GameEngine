method(module, namespace_std,

Graph := Object clone lexicalDo(

    appendProto(namespace_std)

    module := module

	components ::= nil
	domain ::= nil

	// This list really just ensures the Nodes get marked
	objList ::= nil

    // possible interactions shared among all instances
    possibleInteractions := list()

    addNode := method(style,
        node := module Node clone with(style)
        node setGraph(self)
        objList append(node)
        components foreach(c,
            if(c hasSlot("addNode"),
                c addNode(node)
            )
        )
        return node
    )

    addLink := method(style, fromNode, toNode,
        link := module Link clone with(style)
        link setFromNode(fromNode)
        link setToNode(toNode)
        link setGraph(self)

        // TODO: Maybe component addLink can be replaced with an interaction!
        components foreach(c,
            if(c hasSlot("addLink"),
                c addLink(link)
            )
        )
        return link
    )

    removeLink := method(link,
        // TODO: notify components to remove link attributes
        nil
    )

    registerInteraction := method(interaction,
        possibleInteractions append(interaction)
    )

    addComponent := method(newComp, expectedInteraction,
        components append(newComp)
        domain addObject("component", newComp, expectedInteraction)
        self
    )
)


Graph init := method(

    writeln("Begin Graph init")

    setDomain(module Domain clone setSite(self))

    setObjList(list())
    setComponents(list())

    // TODO:  Decouple Time proto from irrComponent
	//setTime(Time clone setDeviceTimer(irrComp deviceTimer))

	//setPlayer(Player clone create(self))

    //setMenu(nil)

    // Have to add engine to irr component before keyboard and mouse can be inited
    // (see todo below)
    //irrComp setEngine(self)

    // TODO:  Refactor this, currently Keyboard knows too much about Engine
    //setKeyboard(irrComp keyboard)
    //setMouse(irrComp keyboard)
)

Graph playSound := method(file,
    if(sound != nil,
        sound play2D(file, false, false, false, ESM_AUTO_DETECT, false)
    )
)

Graph createCamera := method(lockObj, irrComp createCamera(lockObj))

Graph dispose := method(
    //objList foreach(obj, obj dispose)
    //device drop
    nil
)


Graph removeConstraint := method(constraint,
    bltComp removeConstraint(constraint)
)

Graph addConstraint := method(style, objA, objB,
    bltComp addConstraint(style, objA, objB)
)


Graph nodeToGameObj := method(node, irrComp nodeToGameObj(node))

Graph removeObj := method(obj,
    objList remove(obj)
    irrComp removeObj(obj)
)

Graph addStructure := method(structure, leftHandSide,

    //writeln("structure style ", structure style)

    if (structure style == "root") then(
        return addStructure(structure attachments at(0))
    ) elseif (
        structure style == nil and structure embedObj == nil
    ) then (
        Exception raise("style is nil!")
    ) elseif (
        // This is a nested structure object in the place of a constraint or object style.
        structure style type == "Structure"
    ) then(
        result := addStructure(structure style, leftHandSide)       // add nested structure as a unit
        structure attachments foreach(a, addStructure(a, result))  // connect attachments that are outside the nested structure
        return result

    ) elseif(
        // A constraint connects the left hand side with all its right hand side attachments
        structure style hasProto(ConstraintStyle)
    ) then(
        // TODO: Disable this check when constraint style is attached to world on one end.
        if (leftHandSide == nil, Exception raise("Nothing to connect constraint to on left hand side."))
        structure attachments foreach(a,
            c := addConstraint(
                structure style, leftHandSide, addStructure(a)
            )
        )
        return structure

    ) else(
        // An object style becomes the left hand side for its attachments and returns as a right hand side.

        // Handle existing Nodes embedded in structures, else use style.
        if( structure embedObj != nil,
            obj := structure embedObj
        ,
            obj := addObj(structure style)
        )

        if (obj == nil, Exception raise("Failed to add object in structure."))

		// When the left hand side is an object and not a constraint, add it as a child object (but only if it is kinematic).
		// (If the left hand side is a constraint, this object gets added after the method returns.)
		if (leftHandSide != nil and leftHandSide style hasProto(GameObjStyle) and obj style isKinematic,
			leftHandSide addChild(obj))

        structure attachments foreach(a, addStructure(a, obj))
        return obj
    )
)

return Graph

)
