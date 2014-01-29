writeln("Loader.io")

method(Scripts,

    Loader := Object clone lexicalDo(

        Scripts := Scripts

        directory := nil
        setDirectory := method(value,
            directory = value
            scripts setDirectoryName(directory path)
            self
        )

        scripts ::= nil

        init := method(
            setScripts(Scripts clone)
        )

        _loadScript := method(fName, path,
            method_name := fName clone removeSuffix(".io.inl")
            //writeln("Loader loading ", method_name, " at ", path)
            scripts load(method_name, path)
        )

        _loadDirectory := method(subDir,
            subDirLoader := self clone setDirectory(subDir)
            self scripts setSlot(subDir name,
                subDirLoader loadAllScriptsExcept
            )
        )

        loadAllScriptsExcept := method(exceptNames,
            if( exceptNames == nil, exceptNames = list())
            exceptNames append(".git")
            directory directories map(i, i name) sort foreach(dName,
                if (exceptNames contains(dName) not,
                    _loadDirectory(directory directoryNamed(dName))
                )
            )
            directory fileNames sort foreach(fName,
                if(exceptNames contains(fName) not and fName endsWithSeq(".io.inl"),
                    _loadScript(fName, directory fileNamed(fName) path)
                )
            )
            return scripts
        )
    )
)
