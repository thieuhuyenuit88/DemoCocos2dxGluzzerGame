#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MyObject: public Node
{
protected:
	/*ID object*/
	int oID;

	/*Status object*/
	int curSTT, prevSTT;

	/*Direct object*/
	int oDirect;

	/*Position*/
	cocos2d::Point oPos;

	/*Velocity*/
	cocos2d::Point oVelloc;

	/*Accel*/
	cocos2d::Point oAccel;

	/*Size*/
	cocos2d::Point oSize;

	/*Time update*/
	float timeUpdate;

	/*Time Animation*/
	float timeAnimate;

	/*delta time*/
	float deltaTimeUpdate;

	Rect BoundingBoxConvertedToNodeSpace(Node *other);	
public:
	MyObject(void);
	virtual ~MyObject(void);

	void setVX(float vx){
		oVelloc.x = vx;
	}

	void setVY(float vy){
		oVelloc.x = vy;
	}

	void setVXVY(float vx, float vy){
		oVelloc.set(vx, vy);
	}

	void setX(float x){
		oPos.x = x;
	}

	void setY(float y){
		oPos.y = y;
	}

	void setXY(float x, float y){
		oPos.set(x, y);
	}

	void setDirect(int dir){
		oDirect = dir;
	}

	void setID(int id){
		oID = id;
	}

	void setCurSTT(int curStt){
		curSTT = curStt;
	}

	void setPrevSTT(int prevStt){
		prevSTT = prevStt;
	}

	void setSize(float width, float height){
		oSize.set(width, height);
	}

	void setSizeWidth(float width){
		oSize.x = width;
	}

	void setSizeHeight(float height){
		oSize.y = height;
	}

	void setAccelX(float accelX){
		oAccel.x = accelX;
	}

	void setAccelY(float accelY){
		oAccel.y = accelY;
	}

	void setAccel(float accelX, float accelY){
		oAccel.set(accelX, accelY);
	}

	void setTimeUpdate(float timeUpdate){
		this->timeUpdate = timeUpdate;
	}

	void setTimeAnime(float timeAnimate){
		this->timeAnimate = timeAnimate;
	}

	void setTimeDeltaTimeUpdate(float deltaTimeUpdate){
		this->deltaTimeUpdate = deltaTimeUpdate;
	}

	float getVX(){
		return oVelloc.x;
	}

	float getVY(){
		return oVelloc.y;
	}

	Point getVelloc(){
		return oVelloc;
	}

	float getAccelX(){
		return oAccel.x;
	}

	float getAccelY(){
		return oAccel.y;
	}

	Point getAccel(){
		return oAccel;
	}

	float getTimeUpdate(){
		return timeUpdate;
	}

	float getTimeAnimate(){
		return timeAnimate;
	}

	float getDeltaTimeUpdate(){
		return deltaTimeUpdate;
	}

	int getDirect(){
		return oDirect;
	}

	int getID(){
		return oID;
	}

	int getCurSTT(){return curSTT;}
	int getPrevSTT(){return prevSTT;}

	float getSizeWidth(){return oSize.x;}
	float getSizeHeight(){return oSize.y;}
	cocos2d::Point getSize(){return oSize;}

	float getPosX(){return oPos.x;}
	float getPosY(){return oPos.y;}
	cocos2d::Point getPos(){return oPos;}

	virtual bool Init(cocos2d::Layer *layer){ return true; }
	/*virtual void ProcessCollision(MyObject* obj) = 0;*/

	virtual void UpdateAnimation(float deltaTime){}
	virtual void UpdateMove(float deltaTime){}
	virtual void UpdateStatus(float deltaTime){}
	virtual void Update(float deltaTime) {}

	virtual void Release() = 0;

	cocos2d::Rect getFullBoundingBox();
};

