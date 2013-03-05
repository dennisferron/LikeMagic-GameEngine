method(LinkInteraction, Link, Irrlicht, Avatar, Styles,

    // TODO:  Make this allow following any node using a generic position attribute.

    CameraFollowObject := LinkInteraction clone lexicalDo(

        setReferent(mapSubdomains)

        referent at("fromNode") setTrigger(
            camera : Irrlicht Camera
        )

        referent at("toNode") setTrigger(
            dispAttr : Irrlicht NodeAttribute
        )

        referent at("style") setTrigger(
            lookAt : Styles LookAtStyle
        )

        enter := method(
            camera setTargetIrrAttrib(dispAttr)
            self
        )
    )

    Link registerInteraction(CameraFollowObject)

    return CameraFollowObject
)
