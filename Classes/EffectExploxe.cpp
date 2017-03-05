#include "EffectExploxe.h"
#include "Constants.h"

EffectExploxe::EffectExploxe(void)
{
}


EffectExploxe::~EffectExploxe(void)
{
}

EffectExploxe* EffectExploxe::Create(Layer* layer){
	auto effectExplode = new EffectExploxe;
	if (effectExplode && effectExplode->Init(layer))
	{
		effectExplode->autorelease();
		return effectExplode;
	}
	CC_SAFE_DELETE(effectExplode);
	return nullptr;
}

bool EffectExploxe::Init(Layer* layer){
	piece1 = Sprite::create("Piece.png");
	piece1->setPosition(0, 40);
	this->addChild(piece1);

	piece2 = Sprite::create("Piece.png");
	piece2->setPosition(0, 13);
	this->addChild(piece2);

	piece3 = Sprite::create("Piece.png");
	piece3->setPosition(0, -13);
	this->addChild(piece3);

	piece4 = Sprite::create("Piece.png");
	piece4->setPosition(0, -40);
	this->addChild(piece4);

	piece5 = Sprite::create("Piece.png");
	this->addChild(piece5);

	piece1->setColor(Color3B(227,220,112));
	piece2->setColor(Color3B(227,220,112));
	piece3->setColor(Color3B(227,220,112));
	piece4->setColor(Color3B(227,220,112));
	piece5->setColor(Color3B(227,220,112));

	layer->addChild(this, kZGuzzler);

	return true;
}

void EffectExploxe::StartExploxe(){
	auto moveBy1 = MoveBy::create(0.75f, Vec2(100, 173));
	auto moveByNext1 = MoveBy::create(8, Vec2(100, 100));
	auto actionSequence1 = Sequence::create(moveBy1, moveByNext1, nullptr);

	auto moveBy2 = MoveBy::create(0.75f, Vec2(150, 87));
	auto moveByNext2 = MoveBy::create(8, Vec2(150, 87));
	auto actionSequence2 = Sequence::create(moveBy2, moveByNext2, nullptr);

	auto moveBy3 = MoveBy::create(0.75f, Vec2(150, -87));
	auto moveByNext3 = MoveBy::create(8, Vec2(150, -87));
	auto actionSequence3 = Sequence::create(moveBy3, moveByNext3, nullptr);

	auto moveBy4 = MoveBy::create(0.75f, Vec2(100, -173));
	auto moveByNext4 = MoveBy::create(8, Vec2(100, -173));
	auto actionSequence4 = Sequence::create(moveBy4, moveByNext4, nullptr);

	auto moveBy5 = MoveBy::create(0.75f, Vec2(180, 0));
	auto moveByNext5 = MoveBy::create(8, Vec2(180, 0));
	auto actionSequence5 = Sequence::create(moveBy5, moveByNext5, nullptr);

	piece1->runAction(actionSequence1);
	piece2->runAction(actionSequence2);
	piece3->runAction(actionSequence3);
	piece4->runAction(actionSequence4);
	piece5->runAction(actionSequence5);
}

void EffectExploxe::StopExploxe(){
	piece1->stopAllActions();
	piece2->stopAllActions();
	piece3->stopAllActions();
	piece4->stopAllActions();
	piece5->stopAllActions();
}

void EffectExploxe::SetSpeedExploxe(float timeDuration){

}
