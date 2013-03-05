method(Constants, Structure, SColor,
    Styles := Module clone lexicalDo(
        scripts := self scripts
        MountStyle := scripts MountStyle()
        LinkStyle := scripts LinkStyle()
        LinkStyles := scripts LinkStyles(LinkStyle)
        ConstraintStyle := scripts ConstraintStyle(Constants, MountStyle, LinkStyle)
        ConstraintStyles := scripts ConstraintStyles(ConstraintStyle)
        GameObjStyle := scripts GameObjStyle(Constants, Structure, SColor)
        GameObjStyles := scripts GameObjStyles(GameObjStyle)
    )
)
