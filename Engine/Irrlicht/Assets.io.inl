method(irr_core,

    Assets := Object clone lexicalDo(

        appendProto(irr_core)

        assetPath ::= nil
        driver ::= nil

        getPath := method(assetFile,
            assetPath .. "/" .. assetFile
        )

        // Note:  This returns an ITexture, while the other method returns and IImage.
        loadTextureFromFile := method(filename,
            path := getPath(filename)
            fsStr := irrFsStr tmpFromCStr(path)
            texture := driver getTexture(fsStr)
            return texture
        )

        // Note:  This returns an ITexture, while the other method returns and IImage.
        loadImageFromFile := method(filename,
            path := getPath(filename)
            fsStr := irrFsStr tmpFromCStr(path)
            image := driver createImageFromFileWithPath(fsStr)
            return image
        )
    )
)
