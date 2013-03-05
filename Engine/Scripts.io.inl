method(Module,

    Scripts := Object clone do(

        Module := Module

        directoryName ::= ""

        EmptyEnvironment := Object clone

        load := method(name, path,
            env := EmptyEnvironment clone
            env doIt := env doFile(path)
            env scripts := self
            writeln("Scripts loading ", name, " at ", path)
            self setSlot(name,
                block(
                    scriptResult := env performWithArgList("doIt", call evalArgs)
                    if(getLocalSlot("scriptResult") isActivatable,
                       Exception raise("Looks like you returned a method by mistake in script " .. name .. " " .. path)
                    ,
                        if (name != "Config" and scriptResult type != name,
                            Exception raise("Expected object of type " .. name .. " instead got object of type " .. scriptResult type .. " from " .. path)
                        )
                    )
                    return scriptResult
                ) setIsActivatable(true)
            )
        )

        _configure := method(call_, requirement, methodName, methodDescription, argListStart,

            writeln(requirement asCapitalized .. " " .. methodDescription .. " of " .. directoryName)

            missingArgs := list()
            values := list()

            for(i, argListStart, call_ argCount - 1,
                hasError := false
                value := nil
                try( value = call_ evalArgAt(i) ) catch(Exception, hasError = true)
                values append(value)
                if( hasError or value == nil,
                    missingArgs append(requirement asCapitalized .. " " .. methodDescription .. " of '" .. directoryName .. "' needs argument '" ..  call_ argAt(i) code .. "'.  ")
                )
            )

            if (missingArgs size > 0,
                if( requirement == "required",
                    Exception raise(missingArgs join("\n"))
                ,
                    writeln(missingArgs join("\n"))
                )
            )

            return self performWithArgList(methodName, values)
        )

        requiredConfig := method(
            _configure(call, "required", configMethodName, "configuration", 0)
        )

        optionalConfig := method(
            _configure(call, "optional", configMethodName, "configuration", 0)
        )

        requiredSlot := method(
            _configure(call, "required", "_configSlot", "slot " .. call evalArgAt(0), 0)
        )

        optionalSlot := method(
            _configure(call, "optional", "_configSlot", "slot " .. call evalArgAt(0), 0)
        )

        requiredCall := method(
            methodName := call argAt(0) name
            _configure(call, "required", methodName, "call to " .. methodName, 1)
        )

        optionalCall := method(
            methodName := call argAt(0) name
            _configure(call, "optional", methodName, "call to " .. methodName, 1)
        )

        _configSlot := method(name, value,
            if( name == nil,
                Exception raise("Slot name was nil.")
            ,
                self setSlot(name, value)
            )
        )

        configMethodName ::= "Config"

        Config := method(
            Exception raise("No configuration script defined for " .. directoryName)
        )
    )
)
