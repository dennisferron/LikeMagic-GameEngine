// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

namespace LikeMagic {

class Namespace;
typedef boost::intrusive_ptr<Namespace> NamespacePtr;

void intrusive_ptr_add_ref(Namespace* p);
void intrusive_ptr_release(Namespace* p);

}
