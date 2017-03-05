#include "BackgroundLayer.h"
#include "Constants.h"

BackgroundLayer::BackgroundLayer(void)
{
}


BackgroundLayer::~BackgroundLayer(void)
{
}

bool BackgroundLayer::init(){
	Color4B colorBG = Color4B(0, 114, 188, 255);

	if(!LayerColor::initWithColor(colorBG)){
		return false;
	}

	/*cloud1 = Sprite::create("Cloud.png");
	cloud1->setPosition(Vec2(140, 548));
	this->addChild(cloud1, kZIndexCloud);

	cloud2 = Sprite::create("Cloud.png");
	cloud2->setFlippedX(true);
	cloud2->setPosition(Vec2(450, 568));
	this->addChild(cloud2, kZIndexCloud);

	cloud3 = Sprite::create("Cloud.png");
	cloud3->setFlippedY(true);
	cloud3->setPosition(Vec2(890, 508));
	this->addChild(cloud3, kZIndexCloud);

	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	Size frameSize = glview->getFrameSize();

	tree = Sprite::create("Tree.png");
	tree->setAnchorPoint(Vec2(.5f, 0));

	if(frameSize.height <= 320)
	{
		tree->setPosition(Vec2(130, 115));
	}else
	{
		tree->setPosition(Vec2(130, 128));
	}

	this->addChild(tree, kZindexTree);

	lamp = Sprite::create("Lamp.png");
	lamp->setAnchorPoint(Vec2(.5f, 0));

	if(frameSize.height <= 320)
	{
		lamp->setPosition(Vec2(750, 115));
	}else{
		lamp->setPosition(Vec2(750, 128));
	}

	this->addChild(lamp, kZIndexCloud);*/

	//create clouds
	CreateClouds();

	//start scroll clouds
	StartClouds();
	return true;
}

void BackgroundLayer::onEnter(){
	LayerColor::onEnter(); 
}

void BackgroundLayer::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags){
	LayerColor::draw(renderer, transform, flags);
}

void BackgroundLayer::SetColorBG(Color4B color){
	Color3B color3B = Color3B(color.r, color.g, color.b);
	this->setColor(color3B);
}

CCloud* BackgroundLayer::AddCloud(const float speed, const Vec2 position,
			  const int zIndex, char* fileName){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCloud *cloud = CCloud::createWithFile(fileName);
	cloud->SetSpeedAndWidth(speed, visibleSize.width);
	cloud->setPosition(position);
	this->addChild(cloud, zIndex);

	clouds.pushBack(cloud);
	return cloud;
}

void BackgroundLayer::StartClouds(){
	for(auto cloud: this->clouds){
		cloud->Start();
	}
}

void BackgroundLayer::StopClouds(){
	for(auto cloud: this->clouds){
		cloud->Stop();
	}
}

void BackgroundLayer::CreateClouds(){
	clouds = Vector<CCloud*>(30);

	auto cloud1 = AddCloud(kSpeedScrollCloud, Vec2(140, 548), kZIndexCloud, "Cloud.png");
	cloud1->setFlippedY(true);

	auto cloud2 = AddCloud(kSpeedScrollCloud, Vec2(640, 568), kZIndexCloud, "Cloud.png");
	cloud2->setFlippedX(true);

	auto cloud3 = AddCloud(kSpeedScrollCloud, Vec2(1024, 508), kZIndexCloud, "Cloud.png");

	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	Size frameSize = glview->getFrameSize();

	if(frameSize.height <= 320)
	{
		auto tree = AddCloud(kSpeedScrollTree, Vec2(130, 115), kZindexTree, "Tree.png");
		tree->setAnchorPoint(Vec2(.5f, 0));

		auto lamp = AddCloud(kSpeedScrollTree, Vec2(650, 115), kZindexTree, "Lamp.png");
		lamp->setAnchorPoint(Vec2(.5f, 0));

		auto tree1 = AddCloud(kSpeedScrollTree, Vec2(1024, 115), kZindexTree, "Tree.png");
		tree1->setAnchorPoint(Vec2(.5f, 0));
	}
	else{
		auto tree = AddCloud(kSpeedScrollTree, Vec2(130, 128), kZindexTree, "Tree.png");
		tree->setAnchorPoint(Vec2(.5f, 0));

		auto lamp = AddCloud(kSpeedScrollTree, Vec2(650, 128), kZindexTree, "Lamp.png");
		lamp->setAnchorPoint(Vec2(.5f, 0));

		auto tree1 = AddCloud(kSpeedScrollTree, Vec2(1024, 128), kZindexTree, "Tree.png");
		tree1->setAnchorPoint(Vec2(.5f, 0));
	}
}