method(module,

// Proto for interactions, provides the setTrigger method for clones to
// use to call out the combination of attributes which trigger them.
// When the triggering combination of attributes is added to a GameObject clone,
// a clone of the interaction is made, the trigger slots are set with the
// attributes that triggerred it, and then the activate method is called.
Interaction := Object clone lexicalDo(

    module := module

    subdomains ::= nil
    site ::= nil
    referent ::= nil

    mapSubdomains := method(
        newReferents := Map clone
        subdomains foreach(subdomain,
            newReferents atPut(subdomain, module Referent clone)
        )
        return newReferents
    )

    hasOneTrigger := method(subdomain, newObj,
        if(referent hasKey(subdomain),
            return referent at(subdomain) hasOneTrigger(newObj)
        ,
            return false
        )
    )

    isFullyTriggeredBy := method(activeObjects,
        referent foreach(subdomain, subRef,
            if( subRef triggers size > 0,
                if( activeObjects hasKey(subdomain) not,
                    return false
                ,
                    if( subRef isFullyTriggeredBy(activeObjects at(subdomain)) not,
                        return false
                    )
                )
            )
        )
        return true
    )

    getTriggers := method(
        result := list()
        referent foreach(subdomain, subRef,
            subRef triggers foreach(t,
                result append(t findProto type)
            )
        )
        return result
    )

    with := method(activeObjects,
        if( referent detect(subdomain, subRef, subRef triggers size > 0) not,
            Exception raise("interaction has no triggers in any subdomain")
        )

        referent foreach(subdomain, subRef,
            if (subRef triggers size > 0,
                if( activeObjects hasKey(subdomain) not,
                    Exception raise("Interaction expects subdomain '" .. subdomain .. "' but it does not have a key in activeObjects " .. activeObjects keys asString)
                )
                if( activeObjects at(subdomain) == nil,
                    Exception raise("Interaction expects subdomain '" .. subdomain .. "' but its value is nil in activeObjects " .. activeObjects keys asString)
                )
                subRef fillSlots(self, activeObjects at(subdomain))
            )
        )

        self enter
        return self
    )
)

)
