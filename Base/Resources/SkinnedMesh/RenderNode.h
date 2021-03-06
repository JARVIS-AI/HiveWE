#pragma once

/**
  * Node in skeletal hierarcy.
  * Based on RenderNode class in MatrixEater
  * that was based on "src/viewer/node.js" in Ghostwolf's
  * viewer.
  */

#define GLM_FORCE_CXX17
#define GLM_FORCE_RADIANS
#define GLM_FORCE_SILENT_WARNINGS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "MDX.h"

class RenderNode {

  public:
	RenderNode() = default;
	RenderNode(mdx::Node node, glm::vec3 pivot);
	mdx::Node node;
	RenderNode* parent;
	glm::vec3 pivot;
	// local space
	glm::vec3 localLocation;
	glm::quat localRotation = glm::quat(1.f, 0.f, 0.f, 0.f);
	glm::vec3 localScale = glm::vec3(1, 1, 1);
	glm::mat4 localMatrix = glm::mat4(1.f);
	// world space (not including game unit X/Y, mdx-m3-viewer's name)
	glm::vec3 worldLocation;
	glm::quat worldRotation = glm::quat(1.f, 0.f, 0.f, 0.f);
	glm::vec3 worldScale = glm::vec3(1, 1, 1);
	glm::mat4 worldMatrix = glm::mat4(1.f);
	// inverse world space
	glm::vec3 inverseWorldLocation;
	glm::quat inverseWorldRotation;
	glm::vec3 inverseWorldScale;
	// cached flags from node, could be removed for RAM
	bool dontInheritTranslation;
	bool dontInheritScaling;
	bool dontInheritRotation;

	// for some reason MatrixEater didn't have
	// dontInheritTranslation and dontInheritRotation????
	bool billboarded;
	bool billboardedX;
	bool billboardedY;
	bool billboardedZ;
	// state flags
	bool visible;
	bool dirty;
	bool wasDirty;

	//void setTransformation(glm::vec3 location, glm::quat rotation, glm::vec3 scale);
	void resetTransformation();
	void recalculateTransformation();
	// void* is a thing from javascript we don't know
	// what it is yet, still reading, just pass null
	// until we need it
	void update(void* scene);
};