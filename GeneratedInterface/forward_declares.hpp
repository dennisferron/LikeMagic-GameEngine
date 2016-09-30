#pragma once

namespace GameBindings
{
	namespace irr
	{
		namespace io
		{
			struct ISceneUserDataSerializer;
			struct IAttributes;
			struct ScriptedDataSerializer;
		}

		namespace video
		{
			struct SMaterialLayer;
			struct IImage;
			struct IVideoDriver;
			struct SMaterial;
			struct SColor;
			struct SExposedVideoData;
			struct S3DVertex;
			struct vector_of_S3DVertex;
			struct E_DRIVER_TYPE;
			struct SColorf;
			struct E_MATERIAL_FLAG;
			struct E_TRANSFORMATION_STATE;
			struct E_COLOR_MATERIAL;
			struct E_MATERIAL_TYPE;
			struct E_VERTEX_TYPE;
			struct E_ANTI_ALIASING_MODE;
			struct ITexture;
		}

		namespace gui
		{
			struct IGUIEditBox;
			struct IGUIStaticText;
			struct SKeyInput;
			struct IGUIContextMenu;
			struct SUserEvent;
			struct EGUI_EVENT_TYPE;
			struct ICursorControl;
			struct EMOUSE_INPUT_EVENT;
			struct SMouseInput;
			struct IGUIEnvironment;
			struct IGUIFont;
			struct EEVENT_TYPE;
			struct SEvent;
			struct IGUIToolBar;
			struct IGUIElement;
			struct SLogEvent;
			struct IGUISpinBox;
			struct EKEY_CODE;
			struct IGUIButton;
			struct SJoystickEvent;
			struct SGUIEvent;
			struct EGUI_ALIGNMENT;
			struct E_MOUSE_BUTTON_STATE_MASK;
		}

		namespace core
		{
			struct ListOfAnim;
			struct recti;
			struct matrix4;
			struct irrFsStr;
			struct stringw;
			struct aabbox3df;
			struct EIntersectionRelation3D;
			struct plane3df;
			struct ListOfAnimConstIter;
			struct ListOfAnimIter;
			struct triangle3df;
			struct line3df;
			struct rectf;
			struct vector2df;
			struct vector2di;
			struct dimension2df;
			struct ArrayOfVector3df;
			struct dimension2du;
			struct vector3df;
			struct vector_of_vector3df;
		}

		namespace scene
		{
			struct IMeshManipulator;
			struct E_HARDWARE_MAPPING;
			struct SMeshBuffer;
			struct ITerrainSceneNode;
			struct ISceneNode;
			struct E_TERRAIN_PATCH_SIZE;
			struct SMesh;
			struct ITriangleSelector;
			struct IAnimatedMeshSceneNode;
			struct ILightSceneNode;
			struct ISceneNodeAnimator;
			struct IAnimatedMesh;
			struct ICameraSceneNode;
			struct IMeshSceneNode;
			struct ISceneManager;
			struct ISceneCollisionManager;
			struct IMeshBuffer;
			struct IGeometryCreator;
			struct E_BUFFER_TYPE;
			struct IMesh;
		}

		namespace custom
		{
			struct IEventReceiver;
			struct ScriptedSceneNode;
			struct OrientationHelperSceneNode;
			struct ScriptedEventReceiver;
		}

		struct SKeyMap;
		struct ITimer;
		struct IReferenceCounted;
		struct IrrlichtDevice;
	}

	namespace std
	{
		struct vector_of_float_iterator;
		struct vector_of_double_iterator;
		struct vector_of_int;
		struct vector_of_float;
		struct vector_of_short;
		struct vector_of_ushort;
		struct vector_of_double;
		struct vector_of_string;
		struct vector_of_uint;
	}

	namespace LM
	{
		struct TypeMirror;
		struct CallTarget;
		struct MarkableObjGraph;
		struct IMarkable;
		struct LangBlock;
		struct TypeIndex;
		struct Expr;
	}

	namespace desteer
	{
		namespace entity
		{
			struct IEntitySpace;
			struct IBaseEntity;
			struct ScriptedBaseEntity;
			struct IMobileEntity;
			struct ScriptedEntitySpace;
			struct ScriptedMobileEntity;
		}

		namespace controller
		{
			struct EBEHAVIOR_FLAG;
			struct ISteeringController;
			struct SimpleSteeringController;
		}

		struct BehaviorIterator;
		struct EntityGroup;
		struct MobGroup;
		struct MobIterator;
		struct EntityIterator;
		struct BehaviorGroup;
	}

	namespace TPS
	{
		struct ControlPoint;
		struct ControlPointPtr;
		struct ThinPlateQuilt;
		struct Vec;
		struct ThinPlateSpline;
	}

	namespace Custom
	{
		struct Shell;
		struct PhysicsAnimator;
		struct IrrlichtBulletDebugDrawer;
		struct MeshTools;
		struct LockAnimator;
		struct GearConstraint;
		struct SplitMeshResult;
		struct SceneNodePtrTest;
		struct FlagBits_of_ISceneNode;
		struct KinematicAnimator;
		struct ScriptObjAnimator;
		struct SoftBodyMeshSynchronizer;
		struct SurfaceQuadTree;
	}

	namespace Bullet
	{
		struct btSparseSdf_3;
		struct btHingeConstraint;
		struct btConeTwistConstraint;
		struct btTransform;
		struct btIndexedMesh;
		struct btStridingMeshInterface;
		struct btTriangleMesh;
		struct btCollisionObject;
		struct btPairCachingGhostObject;
		struct btIDebugDraw;
		struct btTypedConstraint;
		struct ScriptedContactResultCallback;
		struct btDbvtBroadphase;
		struct btTriangleMeshShape;
		struct btRotationalLimitMotor;
		struct btDispatcher;
		struct btTypedObject;
		struct btCollisionDispatcher;
		struct btSoftBodyHelpers;
		struct btSoftBodyWorldInfo;
		struct btSoftBody_Config;
		struct btConstraintSolver;
		struct PHY_ScalarType;
		struct btBvhTriangleMeshShape;
		struct btSequentialImpulseConstraintSolver;
		struct btDefaultMotionState;
		struct btHeightfieldTerrainShape;
		struct btSoftRigidDynamicsWorld;
		struct btCollisionWorld_ContactResultCallback;
		struct ScriptedClosestRayResultCallback;
		struct btCollisionWorld_ClosestRayResultCallback;
		struct DebugDrawModes;
		struct btCollisionWorld_RayResultCallback;
		struct btSoftBody;
		struct btDynamicsWorld;
		struct btCompoundShape;
		struct btDiscreteDynamicsWorld;
		struct btCollisionWorld;
		struct btConeShapeZ;
		struct ScriptedWorldManager;
		struct btMatrix3x3;
		struct btConeShapeX;
		struct btConeShape;
		struct btTriangleIndexVertexArray;
		struct btCapsuleShape;
		struct btCylinderShapeZ;
		struct btBoxShape;
		struct btGhostObject;
		struct btSliderConstraint;
		struct btRigidBodyConstructionInfo;
		struct btDefaultCollisionConstructionInfo;
		struct btSoftBodyRigidBodyCollisionConfiguration;
		struct btDefaultCollisionConfiguration;
		struct btBroadphaseInterface;
		struct btCollisionWorld_LocalShapeInfo;
		struct btConcaveShape;
		struct btGeneric6DofSpringConstraint;
		struct CollisionFilterGroups;
		struct btCollisionShape;
		struct btPoint2PointConstraint;
		struct btRigidBody;
		struct btSphereShape;
		struct btManifoldPoint;
		struct btMotionState;
		struct btCylinderShape;
		struct btCollisionConfiguration;
		struct btVector3;
		struct btGeneric6DofConstraint;
		struct btCollisionWorld_LocalRayResult;
		struct btStaticPlaneShape;
		struct btQuaternion;
		struct btMultimaterialTriangleMeshShape;
		struct btCylinderShapeX;
	}

	struct ScriptUtil;
	struct NativeArray_of_double;
	struct NativeArray_of_float;
	struct float_expr;
	struct double_expr;
	struct Delegate;
	struct char_expr;
	struct ushort_expr;
	struct long_expr;
	struct wchar_t_expr;
	struct short_expr;
	struct int_expr;
	struct uchar_expr;
	struct uint_expr;
	struct void_expr;
	struct bool_expr;
	struct string_expr;
	struct TypeSystem;
	struct ulong;
	struct wstring_expr;
	struct LangBlockExpr;
	struct BottomPtr;
}


namespace GameBindings {
    struct MissingType;
}
