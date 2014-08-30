#pragma once

namespace GameBindings
{
	namespace desteer
	{
		namespace entity
		{
			struct ScriptedMobileEntity;
			struct ScriptedBaseEntity;
			struct IMobileEntity;
			struct IBaseEntity;
			struct ScriptedEntitySpace;
			struct IEntitySpace;
		}

		namespace controller
		{
			struct SimpleSteeringController;
			struct EBEHAVIOR_FLAG;
			struct ISteeringController;
		}

		struct MobIterator;
		struct EntityIterator;
		struct EntityGroup;
		struct MobGroup;
		struct BehaviorIterator;
		struct BehaviorGroup;
	}

	namespace Custom
	{
		struct SplitMeshResult;
		struct IrrlichtBulletDebugDrawer;
		struct SceneNodePtrTest;
		struct SurfaceQuadTree;
		struct Shell;
		struct FlagBits_of_ISceneNode;
		struct MeshTools;
		struct SoftBodyMeshSynchronizer;
		struct GearConstraint;
		struct ScriptObjAnimator;
		struct KinematicAnimator;
		struct PhysicsAnimator;
		struct LockAnimator;
	}

	namespace Bullet
	{
		struct btCollisionDispatcher;
		struct btCollisionWorld;
		struct btCylinderShape;
		struct btConcaveShape;
		struct btBoxShape;
		struct btSphereShape;
		struct btStaticPlaneShape;
		struct btCollisionShape;
		struct btPairCachingGhostObject;
		struct PHY_ScalarType;
		struct btRigidBody;
		struct btCollisionWorld_LocalRayResult;
		struct btTransform;
		struct btRigidBodyConstructionInfo;
		struct btDefaultCollisionConstructionInfo;
		struct btSoftBodyRigidBodyCollisionConfiguration;
		struct DebugDrawModes;
		struct btCylinderShapeX;
		struct btSequentialImpulseConstraintSolver;
		struct btCollisionWorld_ContactResultCallback;
		struct btVector3;
		struct btRotationalLimitMotor;
		struct btPoint2PointConstraint;
		struct btConeTwistConstraint;
		struct btHingeConstraint;
		struct btTypedObject;
		struct btIndexedMesh;
		struct btTriangleMesh;
		struct btStridingMeshInterface;
		struct btSoftBodyHelpers;
		struct btSoftBody;
		struct btIDebugDraw;
		struct btMatrix3x3;
		struct btDispatcher;
		struct btConstraintSolver;
		struct btMultimaterialTriangleMeshShape;
		struct btBvhTriangleMeshShape;
		struct btDbvtBroadphase;
		struct btCollisionWorld_LocalShapeInfo;
		struct ScriptedClosestRayResultCallback;
		struct btHeightfieldTerrainShape;
		struct btCollisionObject;
		struct btCollisionWorld_ClosestRayResultCallback;
		struct btCollisionWorld_RayResultCallback;
		struct btDynamicsWorld;
		struct btBroadphaseInterface;
		struct btSoftBodyWorldInfo;
		struct btCompoundShape;
		struct btCapsuleShape;
		struct btCylinderShapeZ;
		struct btGhostObject;
		struct btDefaultCollisionConfiguration;
		struct btCollisionConfiguration;
		struct CollisionFilterGroups;
		struct btGeneric6DofConstraint;
		struct btQuaternion;
		struct btDefaultMotionState;
		struct btManifoldPoint;
		struct btConeShape;
		struct btSoftBody_Config;
		struct btSoftRigidDynamicsWorld;
		struct btTriangleMeshShape;
		struct btConeShapeX;
		struct btTypedConstraint;
		struct btGeneric6DofSpringConstraint;
		struct btDiscreteDynamicsWorld;
		struct ScriptedWorldManager;
		struct btSparseSdf_3;
		struct ScriptedContactResultCallback;
		struct btTriangleIndexVertexArray;
		struct btMotionState;
		struct btSliderConstraint;
		struct btConeShapeZ;
	}

	namespace irr
	{
		namespace io
		{
			struct ISceneUserDataSerializer;
			struct IAttributes;
			struct ScriptedDataSerializer;
		}

		namespace core
		{
			struct ArrayOfVector3df;
			struct vector2di;
			struct recti;
			struct ListOfAnimConstIter;
			struct dimension2df;
			struct line3df;
			struct stringw;
			struct vector2df;
			struct matrix4;
			struct ListOfAnimIter;
			struct aabbox3df;
			struct rectf;
			struct triangle3df;
			struct ListOfAnim;
			struct EIntersectionRelation3D;
			struct vector_of_vector3df;
			struct dimension2du;
			struct plane3df;
			struct irrFsStr;
			struct vector3df;
		}

		namespace scene
		{
			struct SMesh;
			struct IAnimatedMeshSceneNode;
			struct ITriangleSelector;
			struct IMeshManipulator;
			struct ICameraSceneNode;
			struct ITerrainSceneNode;
			struct ILightSceneNode;
			struct IMeshSceneNode;
			struct ISceneNode;
			struct IGeometryCreator;
			struct IAnimatedMesh;
			struct IMeshBuffer;
			struct ISceneManager;
			struct E_TERRAIN_PATCH_SIZE;
			struct E_BUFFER_TYPE;
			struct SMeshBuffer;
			struct E_HARDWARE_MAPPING;
			struct IMesh;
			struct ISceneNodeAnimator;
			struct ISceneCollisionManager;
		}

		namespace gui
		{
			struct IGUIFont;
			struct IGUIEnvironment;
			struct IGUIEditBox;
			struct IGUIStaticText;
			struct IGUIButton;
			struct IGUIElement;
			struct SUserEvent;
			struct SLogEvent;
			struct SKeyInput;
			struct SMouseInput;
			struct IGUISpinBox;
			struct SGUIEvent;
			struct SEvent;
			struct EMOUSE_INPUT_EVENT;
			struct IGUIToolBar;
			struct EEVENT_TYPE;
			struct EKEY_CODE;
			struct EGUI_ALIGNMENT;
			struct E_MOUSE_BUTTON_STATE_MASK;
			struct IGUIContextMenu;
			struct ICursorControl;
			struct SJoystickEvent;
			struct EGUI_EVENT_TYPE;
		}

		namespace video
		{
			struct S3DVertex;
			struct E_TRANSFORMATION_STATE;
			struct E_MATERIAL_TYPE;
			struct ITexture;
			struct IVideoDriver;
			struct SMaterialLayer;
			struct SColorf;
			struct E_DRIVER_TYPE;
			struct SMaterial;
			struct E_MATERIAL_FLAG;
			struct IImage;
			struct SExposedVideoData;
			struct SColor;
			struct E_COLOR_MATERIAL;
			struct E_VERTEX_TYPE;
			struct E_ANTI_ALIASING_MODE;
			struct vector_of_S3DVertex;
		}

		namespace custom
		{
			struct IEventReceiver;
			struct ScriptedSceneNode;
			struct OrientationHelperSceneNode;
			struct ScriptedEventReceiver;
		}

		struct IrrlichtDevice;
		struct IReferenceCounted;
		struct ITimer;
		struct SKeyMap;
	}

	namespace TPS
	{
		struct ThinPlateQuilt;
		struct ControlPoint;
		struct Vec;
		struct ControlPointPtr;
		struct ThinPlateSpline;
	}

	namespace LM
	{
		struct TypeIndex;
		struct Expr;
		struct IMarkable;
		struct MarkableObjGraph;
		struct TypeMirror;
		struct LangBlock;
		struct CallTarget;
	}

	namespace std
	{
		struct vector_of_string;
		struct vector_of_ushort;
		struct vector_of_short;
		struct vector_of_float_iterator;
		struct vector_of_double;
		struct vector_of_int;
		struct vector_of_uint;
		struct vector_of_float;
		struct vector_of_double_iterator;
	}

	struct BottomPtr;
	struct LangBlockExpr;
	struct float_expr;
	struct ushort_expr;
	struct NativeArray_of_double;
	struct TypeSystem;
	struct short_expr;
	struct wchar_t_expr;
	struct long_expr;
	struct char_expr;
	struct Delegate;
	struct uchar_expr;
	struct bool_expr;
	struct ulong;
	struct NativeArray_of_float;
	struct string_expr;
	struct int_expr;
	struct wstring_expr;
	struct ScriptUtil;
	struct double_expr;
	struct void_expr;
	struct uint_expr;
}


namespace GameBindings {
    struct MissingType;
}
