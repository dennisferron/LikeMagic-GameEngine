// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/Bindings.hpp"

#include <irrlicht.h>

#include "LikeMagic/BindingMacros.hpp"

using namespace LikeMagic;
using namespace irr::core;
using namespace irr;

#include <iostream>
using namespace std;

namespace Bindings { namespace Irrlicht {

void add_bindings_core()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_irr = register_namespace("irr", global_ns);
    TypeMirror& ns_irr_core = register_namespace("core", ns_irr);

    LM_STATIC_FUNC_NAME(core, "isnotzero", isnotzero)

    typedef irr::core::string<fschar_t> irrFsStr;
    LM_CLASS(ns_irr_core, irrFsStr)
    LM_CONSTR(irrFsStr,"new")
    LM_CONSTR(irrFsStr, "new", const fschar_t*)
    LM_CONSTR(irrFsStr, "newFromCStr", const fschar_t*)

    LM_CLASS(ns_irr_core, stringw)
    LM_CONSTR(stringw,"new")
    LM_CONSTR(stringw, "new", const wchar_t*)

    LM_CLASS(ns_irr_core, dimension2du)
    LM_CONSTR(dimension2du,"new")
    LM_CONSTR(dimension2du, "new", int, int)
    LM_FUNC(dimension2du, (set)(getArea))
    LM_FIELD(dimension2du, (Width)(Height))

    LM_CLASS(ns_irr_core, dimension2df)
    LM_CONSTR(dimension2df,"new")
    LM_CONSTR(dimension2df, "new", float, float)
    LM_FUNC(dimension2df, (set)(getArea))
    LM_FIELD(dimension2df, (Width)(Height))

    LM_CLASS(ns_irr_core, recti)
    LM_CONSTR(recti, "new", int, int, int, int)
    LM_CONSTR(recti, "newWithXYXY", int, int, int, int)

    LM_CLASS(ns_irr_core, rectf)
    LM_CONSTR(rectf, "new", float, float, float, float)
    LM_CONSTR(rectf, "newWithXYXY", float, float, float, float)
    LM_CONSTR(rectf, "newPosSize", vector2df const&, dimension2df const&)
    LM_FIELD(rectf, (UpperLeftCorner)(LowerRightCorner))
    LM_FUNC(rectf, (getWidth)(getHeight))

    LM_CLASS(ns_irr_core, vector2di)
    LM_CONSTR(vector2di,"new")
    LM_CONSTR(vector2di, , int, int)
    LM_CONSTR(vector2di, "newWithXY", int, int)
    LM_FIELD(vector2di, (X)(Y))

    LM_CLASS(ns_irr_core, vector2df)
    LM_CONSTR(vector2df,"new")
    LM_CONSTR(vector2df, , float, float)
    LM_CONSTR(vector2df, "newWithXY", f32, f32)
    LM_FIELD(vector2df, (X)(Y))

    LM_CLASS(ns_irr_core, matrix4)
    LM_CONSTR(matrix4,"new")
    LM_CONSTR(matrix4, "new", matrix4::eConstructor)
    LM_CONSTR(matrix4, "new", matrix4 const&, matrix4::eConstructor)
    LM_FUNC(matrix4, (getRotationDegrees))
    LM_FUNC_OVERLOAD_CONST(matrix4, "transformVect", transformVect, void, vector3df&)
    LM_FUNC_OVERLOAD_CONST(matrix4, "transformVect", transformVect, void, vector3df&, vector3df const&)
    LM_FUNC_OVERLOAD_CONST(matrix4, "transformVectOfFloats", transformVect, void, f32*, vector3df const&)

    LM_CLASS(ns_irr_core, line3df)
    LM_FIELD(line3df, (start)(end))
    LM_FUNC(line3df, (getClosestPoint)(getIntersectionWithSphere)(getLength)(getLengthSQ)(getMiddle)(getVector)(isPointBetweenStartAndEnd))
    LM_OP(line3df, (!=)(+)(+=)(-)(-=)(==))

    LM_CLASS(ns_irr_core, triangle3df)
    LM_CONSTR(triangle3df,"new")
    LM_CONSTR(triangle3df, "new", vector3df, vector3df, vector3df)
    LM_FIELD(triangle3df, (pointA)(pointB)(pointC))
    LM_FUNC(triangle3df,
            (closestPointOnTriangle)(getArea)(getIntersectionOfPlaneWithLine)(getIntersectionWithLimitedLine)(getIntersectionWithLine)
            (getNormal)(getPlane)(isFrontFacing)(isPointInside)(isPointInsideFast)(isTotalInsideBox)(isTotalOutsideBox)(set)
    )
    LM_OP(triangle3df, (==)(!=))

    LM_CLASS(ns_irr_core, vector3df)
    LM_CONSTR(vector3df,"new")
    LM_CONSTR(vector3df, "new", float)
    LM_CONSTR(vector3df, "new", float, float, float)
    LM_CONSTR(vector3df, "newWithXYZ", float, float, float)
    LM_CONSTR(vector3df, "newFromVector3df", vector3df const&)
    LM_FIELD(vector3df, (X)(Y)(Z))
    LM_FUNC(vector3df, (dotProduct)(crossProduct)(equals)(getAs4Values)(getDistanceFrom)
            (getDistanceFromSQ)(getHorizontalAngle)(getInterpolated)(getInterpolated_quadratic)(getLength)(getLengthSQ)(getSphericalCoordinateAngles)
            (interpolate)(invert)(isBetweenPoints)(normalize)(rotateXYBy)(rotateXZBy)(rotateYZBy)(rotationToDirection)(setLength))
    LM_OP(vector3df, (==)(!=)(<)(>)(<=)(>=))

    LM_OP_OVERLOAD(vector3df, const, +, vector3df, vector3df const&)
    LM_OP_OVERLOAD(vector3df, const, -, vector3df, vector3df const&)
    LM_OP_OVERLOAD(vector3df, const, *, vector3df, vector3df const&)
    LM_OP_OVERLOAD(vector3df, const, /, vector3df, vector3df const&)

    LM_OP_OVERLOAD(vector3df, , +=, vector3df&, vector3df const&)
    LM_OP_OVERLOAD(vector3df, , -=, vector3df&, vector3df const&)
    LM_OP_OVERLOAD(vector3df, , *=, vector3df&, vector3df const&)
    LM_OP_OVERLOAD(vector3df, , /=, vector3df&, vector3df const&)

    LM_FUNC_OVERLOAD(vector3df, "set", set, vector3df&, vector3df const&)
    LM_FUNC_OVERLOAD(vector3df, "set", set, vector3df&, float, float, float)

    typedef std::vector<vector3df> vector_of_vector3df;
    LM_CLASS(ns_irr_core, vector_of_vector3df)

    LM_CLASS(ns_irr_core, aabbox3df)
    LM_CONSTR(aabbox3df,"new")
    LM_CONSTR(aabbox3df, "new",vector3df)
    LM_CONSTR(aabbox3df, "newWithOnePoint", vector3df)
    LM_CONSTR(aabbox3df, "new",vector3df, vector3df)
    LM_CONSTR(aabbox3df, "newWithMinMax",vector3df, vector3df)
    LM_CONSTR(aabbox3df, "new", f32, f32, f32, f32, f32, f32)
    LM_CONSTR(aabbox3df, "newWithMinMaxXYZ", f32, f32, f32, f32, f32, f32)
    LM_FIELD(aabbox3df, (MaxEdge)(MinEdge))
    LM_OP(aabbox3df, (!= )(==))
    LM_FUNC(aabbox3df,
        (addInternalBox)
        (classifyPlaneRelation)
        (getArea)
        (getCenter)
        (getEdges)
        (getExtent)
        (getInterpolated)
        (getVolume)
        (intersectsWithBox)
        (isEmpty)
        (isFullInside)
        (isPointInside)
        (isPointTotalInside)
        (repair)
    )

/* todo: bind aabbox3df overloads:
void addInternalPoint(const vector3d<T>& p)
void addInternalPoint(T x, T y, T z)
void 	reset (const vector3d< T > &initValue)
void 	reset (const aabbox3d< T > &initValue)
void 	reset (T x, T y, T z)
bool 	intersectsWithLine (const vector3d< T > &linemiddle, const vector3d< T > &linevect, T halflength) const
bool 	intersectsWithLine (const line3d< T > &line) const
*/

    typedef irr::core::list<irr::scene::ISceneNodeAnimator*> ListOfAnim;
    LM_CLASS(ns_irr_core, ListOfAnim)
    LM_FUNC(ListOfAnim, (clear)(empty)(erase)(getSize)(insert_after)(insert_before)(push_back)(push_front)(size)(swap))
    LM_FUNC_OVERLOAD_CONST(ListOfAnim, "begin_c", begin, ListOfAnim::ConstIterator)
    LM_FUNC_OVERLOAD(ListOfAnim, "begin_nc", begin, ListOfAnim::Iterator)
    LM_FUNC_OVERLOAD_CONST(ListOfAnim, "end_c", end, ListOfAnim::ConstIterator)
    LM_FUNC_OVERLOAD(ListOfAnim, "end_nc", end, ListOfAnim::Iterator)
    LM_FUNC_OVERLOAD_CONST(ListOfAnim, "getLast_c", getLast, ListOfAnim::ConstIterator)
    LM_FUNC_OVERLOAD(ListOfAnim, "getLast_nc", getLast, ListOfAnim::Iterator)

    typedef ListOfAnim::Iterator ListOfAnimIter;
    LM_CLASS(ns_irr_core, ListOfAnimIter)
    LM_OP(ListOfAnimIter, (*))
    LM_OP_OVERLOAD(ListOfAnimIter, , ++, ListOfAnimIter, s32)
    LM_OP_OVERLOAD(ListOfAnimIter, , --, ListOfAnimIter, s32)
    //LM_OP_OVERLOAD(ListOfAnimIter, , ++, ListOfAnimIter&)
    //LM_OP_OVERLOAD(ListOfAnimIter, , --, ListOfAnimIter&)
    LM_OP_OVERLOAD(ListOfAnimIter, const, +, ListOfAnimIter, s32)
    LM_OP_OVERLOAD(ListOfAnimIter, const, -, ListOfAnimIter, s32)

    typedef ListOfAnim::ConstIterator ListOfAnimConstIter;
    LM_CLASS(ns_irr_core, ListOfAnimConstIter)
    LM_OP(ListOfAnimConstIter, (*))
    LM_OP_OVERLOAD(ListOfAnimConstIter, , ++, ListOfAnimConstIter, s32)
    LM_OP_OVERLOAD(ListOfAnimConstIter, , --, ListOfAnimConstIter, s32)
    //LM_OP_OVERLOAD(ListOfAnimConstIter, , ++, ListOfAnimConstIter&)
    //LM_OP_OVERLOAD(ListOfAnimConstIter, , --, ListOfAnimConstIter&)
    LM_OP_OVERLOAD(ListOfAnimConstIter, const, +, ListOfAnimConstIter, s32)
    LM_OP_OVERLOAD(ListOfAnimConstIter, const, -, ListOfAnimConstIter, s32)

    typedef irr::core::array<irr::core::vector3df> ArrayOfVector3df;
    LM_CLASS(ns_irr_core, ArrayOfVector3df)
    LM_CONSTR(ArrayOfVector3df,"new")
    LM_CONSTR(ArrayOfVector3df, "newWithSize", u32)
    LM_CONSTR(ArrayOfVector3df, "newCopy", ArrayOfVector3df)
    LM_FUNC(ArrayOfVector3df, (allocated_size)(binary_search_multi)(clear)(const_pointer)(empty)(insert)
            (linear_reverse_search)(linear_search)(pointer)(push_back)(push_front)(reallocate)(set_free_when_destroyed)
            (set_pointer)(set_sorted)(set_used)(setAllocStrategy)(size)(sort)(swap))

    LM_FUNC_OVERLOAD_CONST(ArrayOfVector3df, "binary_search", binary_search, s32, const vector3df&, s32, s32)
    LM_FUNC_OVERLOAD_CONST(ArrayOfVector3df, "binary_search_c", binary_search, s32, const vector3df&)
    LM_FUNC_OVERLOAD(ArrayOfVector3df, "binary_search_nc", binary_search, s32, const vector3df&)
    LM_FUNC_OVERLOAD(ArrayOfVector3df, "erase", erase, void, u32, s32)
    LM_FUNC_OVERLOAD(ArrayOfVector3df, "erase", erase, void, u32)
    LM_FUNC_OVERLOAD_BOTH(ArrayOfVector3df, getLast, vector3df&)

    LM_OP(ArrayOfVector3df, (!=)(==))
    LM_FUNC_OVERLOAD(ArrayOfVector3df, "squareBrackets", operator [], vector3df&, u32)

    LM_CLASS(ns_irr_core, plane3df)
    LM_CONSTR(plane3df,"new")
    LM_CONSTR(plane3df,"newFromNormalAndDistance", vector3df const&, f32 const)
    LM_CONSTR(plane3df,"newFromPoints", vector3df const&, vector3df const&, vector3df const&)
    LM_CONSTR(plane3df,"newFromPxPyPzNxNyNz", f32, f32, f32, f32, f32, f32)
    LM_CONSTR(plane3df,"newFromPointAndNormal", vector3df const&, vector3df const&)
    LM_FIELD(plane3df, (D)(Normal))
    LM_FUNC(plane3df, (classifyPointRelation)(existsIntersection)(getDistanceTo)(getIntersectionWithLimitedLine)(getIntersectionWithLine)
            (getIntersectionWithPlane)(getIntersectionWithPlanes)(getKnownIntersectionWithLine)(getMemberPoint)(isFrontFacing)(recalculateD))
    LM_OP(plane3df, (!=)(==))
    LM_FUNC_OVERLOAD(plane3df, "setPlaneFromPoints", setPlane, void, vector3df const&, vector3df const&, vector3df const&)
    LM_FUNC_OVERLOAD(plane3df, "setPlaneFromNormalAndDistance", setPlane, void, vector3df const&, f32)
    LM_FUNC_OVERLOAD(plane3df, "setPlaneFromPointAndNormal", setPlane, void, vector3df const&, vector3df const&)

    // Used by classifyPointRelation in plane3df
    LM_CLASS(ns_irr_core, EIntersectionRelation3D)
}

}}
