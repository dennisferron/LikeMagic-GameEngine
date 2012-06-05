//##########################################################################################################################

// OrientationHelperSceneNode.h file

//##########################################################################################################################



/**

 * Orientation Helper Scene Node for Irrlicht

 * (c) 2010, Markus Mayer <https://launchpad.net/~sunside>

 */



/* This program is free software. It comes without any warranty, to

 * the extent permitted by applicable law. You can redistribute it

 * and/or modify it under the terms of the Creative Commons

 * Attribution 3.0 Unported license.

 * See http://creativecommons.org/licenses/by/3.0/ for more details. */



#include <irrlicht.h>

using namespace irr;



class OrientationHelperSceneNode : public scene::ISceneNode

{

public:

	OrientationHelperSceneNode(f32 size, scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);

	virtual ~OrientationHelperSceneNode(void) {}

	virtual void render();

	inline virtual const core::aabbox3d<f32>& getBoundingBox() const { return boundingBox; }



	inline virtual void OnRegisterSceneNode() {

		if (!isVisible()) return;



		SceneManager->registerNodeForRendering(this);

		ISceneNode::OnRegisterSceneNode();

	}



	//! Rotates the node, so that it's Z direction matches the given vector

	/**

	* @direction		The direction vector

	* @worldUp		The world up vector

	*/

	void rotateZToDirection(const core::vector3df &direction, const core::vector3df &worldUp);



	//! Rotates the node, so that it's Z direction matches the given vector

	/**

	* @direction		The camera to take the target direction vector from

	* @worldUp		The world up vector

	*/

	inline void rotateZToDirection(const scene::ICameraSceneNode *camera, const core::vector3df &worldUp) {

		core::vector3df direction = (camera->getTarget() - camera->getPosition()).normalize();

		rotateZToDirection(direction, worldUp);

	}



	//! Rotates the node, so that it's Z direction matches the given vector

	/**

	* @direction		The camera to take the target direction and world up vector from

	*/

	inline void rotateZToDirection(const scene::ICameraSceneNode *camera) {

		core::vector3df worldUp = camera->getUpVector();

		rotateZToDirection(camera, worldUp);

	}



private:



	core::aabbox3d<f32> boundingBox;

	f32 size;

	video::SMaterial boxMaterial;

};
