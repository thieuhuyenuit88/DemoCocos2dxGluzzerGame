// Special thanks
// Ebyan Alvarez-Buylla
// http://www.nolithius.com/game-development/cocos2d-iphone-repeating-sprite

#include "TiledSprite.h"

TiledSprite::TiledSprite(void)
{
}


TiledSprite::~TiledSprite(void)
{
}

bool TiledSprite::init(){
	return true;
}

TiledSprite* TiledSprite::initWithSprite(Sprite* p_sprite, int p_width, int p_height){
	auto tileSprite = new TiledSprite;
	if (tileSprite->init())
	{
		// Only bother doing anything if the sizes are positive
		if (p_width > 0 && p_height > 0)
		{
			Rect spriteBounds = p_sprite->getTextureRect();
			int sourceX = spriteBounds.origin.x;
			int sourceY = spriteBounds.origin.y;
			int sourceWidth = spriteBounds.size.width;
			int sourceHeight = spriteBounds.size.height;

			Texture2D* texture = p_sprite->getTexture();

			//Case 1: both width and height are smaller than source sprite, just clip
			if (p_width <= sourceWidth && p_height <= sourceHeight)
			{
				Sprite* sprite = Sprite::createWithTexture(texture, Rect(sourceX, sourceY + sourceHeight - p_height, p_width, p_height));
				sprite->setAnchorPoint(Vec2(0, 0));
				tileSprite->addChild(sprite);
			}

			//Case 2: only width is larger than source sprite
			else if (p_width > sourceWidth && p_height <= sourceHeight)
			{
				//Stamp sideways until we can
				int ix = 0;
				while (ix < p_width - sourceWidth)
				{
					Sprite* sprite = Sprite::createWithTexture(texture, Rect(sourceX, sourceY + sourceHeight - p_height, sourceWidth, p_height));
					sprite->setAnchorPoint(Vec2(0, 0));
					sprite->setPosition(ix, 0);
					tileSprite->addChild(sprite);

					ix += sourceWidth;
				}

				//Stamp the last one
				Sprite* sprite = Sprite::createWithTexture(texture, Rect(sourceX, sourceY + sourceHeight - p_height, p_width - ix, p_height));
				sprite->setAnchorPoint(Vec2(0, 0));
				sprite->setPosition(ix, 0);
				tileSprite->addChild(sprite);
			}

			//Case 3: only height is larger than source sprite
			else if (p_height >= sourceHeight && p_width <= sourceWidth)
			{
				// Stamp down until we can
				int iy = 0;
				while (iy < p_height - sourceHeight)
				{
					Sprite* sprite = Sprite::createWithTexture(texture, Rect(sourceX, sourceY, p_width, sourceHeight));
					sprite->setAnchorPoint(Vec2(0, 0));
					sprite->setPosition(0, iy);
					tileSprite->addChild(sprite);

					iy += sourceHeight;
				}

				// Stamp the last one
				int remainingHeight = p_height - iy;
				Sprite* sprite = Sprite::createWithTexture(texture, Rect(sourceX, sourceY + sourceHeight - remainingHeight, p_width, remainingHeight));
				sprite->setAnchorPoint(Vec2(0, 0));
				sprite->setPosition(0, iy);
				tileSprite->addChild(sprite);
			}

			//Case 4: both width and height are lager than source sprite
			else{
				// Stamp down until we can
				int iy = 0;
				while (iy < p_height - sourceHeight)
				{
					TiledSprite* sprite = TiledSprite::initWithSprite(p_sprite, p_width, sourceHeight);
					sprite->setAnchorPoint(Vec2(0, 0));
					sprite->setPosition(0, iy);
					tileSprite->addChild(sprite);

					iy += sourceHeight;
				}

				//Stamp the last one
				TiledSprite* sprite = TiledSprite::initWithSprite(p_sprite, p_width, p_height - iy);
				sprite->setAnchorPoint(Vec2(0, 0));
				sprite->setPosition(0, iy);
				tileSprite->addChild(sprite);
			}
		}
	}
	
	return tileSprite;
}