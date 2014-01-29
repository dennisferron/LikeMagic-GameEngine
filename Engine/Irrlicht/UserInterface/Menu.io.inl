method(namespace_irr,

    Menu := Object clone lexicalDo(

        // Wait, why does a "menu" depend so heavily on irrlicht types?
        appendProto(namespace_irr)
        appendProto(namespace_irr core)
        appendProto(namespace_irr gui)
        appendProto(namespace_irr video)

        SColor := namespace_irr video SColor

        context ::= nil
        path ::= nil
        engine ::= nil
        parent ::= nil
        items ::= nil
        font ::= nil
        lineH ::= 50
        selectedLine ::= 0
        selectedColor ::= SColor tmp(255, 255, 255, 255)
        regularColor ::= SColor tmp(120, 120, 120, 120)

        create := method(engine, path, parent,
            setEngine(engine)
            setPath(path)
            setParent(parent)
            setItems(list())
            setFont(engine gui getBuiltInFont)
            load
            return self
        )

        load := method(
            dir := Directory at(WayUpDir(path))
            if (dir != nil,
                setItems(list())
                dir files foreach(f,
                    if (f name == "Context.io",
                        setContext(doFile(f path))
                    ,
                        items append(f name)
                    )
                )
                dir directories foreach(d, items append(d name))
            )
            items sortInPlace
            setSelectedLine(0)
        )

        doKey := method(key,

            if (key == KEY_ESCAPE or key == KEY_BACK,
                if (parent != nil,
                    parent load
                )
                return parent
            )

            // Some of the keys assume the size of the items list is nonzero.
            if (items size > 0,
                if (key == KEY_DOWN,
                    setSelectedLine( (selectedLine+1) % items size)
                    return self
                )

                if (key == KEY_UP,
                    setSelectedLine( (selectedLine+items size-1) % items size)
                    return self
                )

                if (key == KEY_RETURN,
                    itemPath := WayUpDir(path .. "/" .. items at(selectedLine))
                    if (File exists(itemPath),
                        f := File clone setPath(itemPath)
                        isDirectory := f isDirectory
                        if (isDirectory,
                            return self clone create(engine, path .. "/" .. items at(selectedLine), self)
                        ,
                            context doFile(itemPath)
                            return self
                        )
                    )
                )
            )
            return self
        )

        draw := method(
            borderX := engine windowSizeX / 5
            borderY := engine windowSizeY / 5
            top := borderY
            bottom := engine windowSizeY - borderY
            left := borderX
            right := engine windowSizeX - borderX

            engine driver draw2DRectangle(
                recti tmp(left, top, right, bottom), // const core::rect< s32 > &pos,
                SColor tmp(200, 30, 60, 30), // SColor colorLeftUp,
                SColor tmp(200, 30, 90, 60), // SColor colorRightUp,
                SColor tmp(200, 50, 50, 90), // SColor colorLeftDown,
                SColor tmp(200, 60, 30, 90), // SColor colorRightDown,
                nil //const core::rect< s32 > *clip
            )

            lineY := (engine windowSizeY - lineH * items size) / 2
            items foreach(i, item,
                str := trimItem(item)
                font draw(
                    stringw tmp(str),
                    recti tmp(0, lineY, engine windowSizeX, lineY + lineH),
                    if(i == selectedLine, selectedColor, regularColor),
                    true, // horizontal center
                    true, // vertical center
                    nil // clip
                )
                lineY = lineY + lineH
            )
        )

        trimItem := method(item,
            zero := "0" at(0)
            nine := "9" at(0)
            space := " " at(0)
            pos := 0
            loop(
                char := item at(pos)
                if (char < zero or char > nine,
                    break
                )
                pos = pos + 1
                if(pos >= item size,
                    pos = 0
                    break
                )
            )
            loop(
                char := item at(pos)
                if (char != space,
                    break
                )
                pos = pos + 1
                if(pos >= item size,
                    pos = 0
                    break
                )
            )
            return item inclusiveSlice(pos)
        )

    )

)
