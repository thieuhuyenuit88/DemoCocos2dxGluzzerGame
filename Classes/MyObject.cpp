#include "MyObject.h"


MyObject::MyObject(void): Node()
{
	oID = 0;
	oDirect = 0;
	curSTT = 0;
	prevSTT = 0;
	oPos.set(0, 0);
	oVelloc.set(0, 0);
	oAccel.set(0, 0);
	oSize.set(0, 0);
	timeUpdate = timeAnimate = deltaTimeUpdate = 0;
}


MyObject::~MyObject(void)
{
}

Rect MyObject::BoundingBoxConvertedToNodeSpace(Node *other){
	// Get the bottomLeft and topRight corners of the other node's bounding box
	// in the other node's coordinate space.
	Rect boundinBox = other->getBoundingBox();
	Point bottomLeft = Point(boundinBox.origin.x, boundinBox.origin.y);
	Point topRight = Point(boundinBox.origin.x + boundinBox.size.width, boundinBox.origin.y + boundinBox.size.height);

	// Convert bottomLeft and topRight to the global coordinate space.
	Point worldSpaceBottomLeft = other->getParent()->convertToWorldSpace(bottomLeft);
	Point worldSpaceTopRight = other->getParent()->convertToWorldSpace(topRight);

	// Convert worldSpaceBottomLeft and worldSpaceTopRight into this node's
	// local coordinate space.
	Point nodeSpaceBottomLeft = this->getParent()->convertToNodeSpace(worldSpaceBottomLeft);
	Point nodeSpaceTopRight = this->getParent()->convertToNodeSpace(worldSpaceTopRight);

	// Finally, construct the bounding box in this node's local coordinate space
	// and return it.
	float width = nodeSpaceTopRight.x - nodeSpaceBottomLeft.x;
	float height = nodeSpaceTopRight.y - nodeSpaceBottomLeft.y;
	return Rect(nodeSpaceBottomLeft.x, nodeSpaceBottomLeft.y, width, height);
}

Rect MyObject::getFullBoundingBox(){
	Vector<Node*> stack;
	float leftMost = this->getBoundingBox().origin.x;
	float rightMost = leftMost + this->getBoundingBox().size.width;
	float lowest = this->getBoundingBox().origin.y;
	float highest = lowest + this->getBoundingBox().size.height;

	for (Node* child: this->getChildren())
	{
		stack.pushBack(child);
	}

	while (stack.size() > 0)
	{
		Node *node = stack.back();
		stack.popBack();
		Rect bb = this->BoundingBoxConvertedToNodeSpace(node);
		float nodeLeftMost = bb.origin.x;
		float nodeRightMost = bb.origin.x + bb.size.width;
		float nodeLowest = bb.origin.y;
		float nodeHighest = bb.origin.y  + bb.size.height;

		leftMost = std::min(leftMost, nodeLeftMost);
		rightMost = std::max(rightMost, nodeRightMost);
		lowest = std::min(lowest, nodeLowest);
		highest = std::max(highest, nodeHighest);
		for (Node* child: node->getChildren())
		{
			stack.pushBack(child);
		}
	}

	float width = rightMost - leftMost;
	float height = highest - lowest;
	return Rect(leftMost, lowest, width, height);
}