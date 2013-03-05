
method(

    // Structure Description Language -
    // This Io DSL allows you to specify nested, hierarchical
    // compound structures of 3d objects.  Example:
    // myStructure := Structure build(
    //      headStyle neckJoint bodyStyle(
    //          leftShoulder armStyle, rightShoulder armStyle, leftHip legStyle, rightHip legStyle
    //      ) tailJoint tailStyle
    // )
    //
    // Simple juxtaposition indicates connections should be made; messages with parenthesis indicate one or more substructures
    // to attach.  The joins are the union of the argument list and the atom following it, so the
    // following two forms result in the same structure:
    //      head(leftEye, rightEye)
    //      head(leftEye) rightEye
    // It does matter though if anything further is following the last atom.  The following two are NOT the same:
    //      head(leftEye, rightEye) neck  // a head with two eyes on a neck
    //      head(leftEye) rightEye neck  // a head with one eye, attached to another eye and that eye has a neck.

    Structure := Object clone lexicalDo(

        style ::= nil
        embedObj ::= nil
        attachments ::= nil

        init := method(
            setStyle("root")
            setAttachments(List clone)
        )

        _parseArgs := method(args, sender,
            if (args != nil,
                args foreach(a,
                    attachments append(Structure clone _parseMessages(a, sender))
                )
            )
            self
        )

        // until programmers stop acting like obfuscation is morally hazardous,
        // they’re not artists, just kids who don’t want their food to touch.  --_why the lucky stiff
        _parseMessages := method(m, sender,
            if (m == nil,  Exception raise("Error in structure; nil message encountered."))
            if (m name == "", Exception raise("Error in structure, Message has no name"))

            // Handle embedding existing objects in structures by checking if it's a style or a GameObject.
            term := sender perform(m name)
            if( term hasProto(GameObject) ,
                setEmbedObj(term)
                setStyle(nil)
            ,
                setStyle(term clone)
                setEmbedObj(nil)
            )
            _parseArgs(m arguments, sender)

            loop(
                m = m nextIgnoreEndOfLines; if (m == nil, return self)
                //writeln("m name = ", m name, "m = ", m)
                if (m name == "", self _parseArgs(m arguments, sender); continue)
                if (m name beginsWithSeq("set") or m name == "do", style doMessage(m clone setNext(nil)); continue)
                break
            )

            attachments append(Structure clone _parseMessages(m, sender))

            return self
        )

        build := method(
            argList := List clone
            for (i, 0, call argCount - 1, argList append(call argAt(i)))
            s := Structure clone _parseArgs(argList, call sender)
        )

        print := method(
            write(if (style == nil, "nil", style))
            write("(")
            attachments foreach(i, a, write(if(i>0, ", ", ""), a))
            write(")")
        )

        move := method(x, y, z,
            if (style hasProto(GameObjStyle),
                style setPos(x + style x, y + style y, z + style z)
            )
            attachments foreach(a, a move(x,y,z))
        )
    )
)
