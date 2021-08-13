#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	SimpleAudioEngine::getInstance()->playBackgroundMusic("awesomeness.wav");

	player_alive = true;
	move_x = 75;
	move_time = 20;
	distance = 0;

	initLabel();
	initChild();
	initSpr();
	initListener();
	initAnimation();
	initBG();
	
	changeStateNone();

	this->scheduleUpdate();

	this->schedule(schedule_selector(HelloWorld::cheerUp), 1);

    return true;
}
void HelloWorld::initSpr()
{
	spr_nonebanner->setPosition(270, 700);
	spr_nonebanner->setScale(2.5f);

	spr_playingbanner->setAnchorPoint(Vec2(0, 0));
	spr_playingbanner->setPosition(0, 700);
	spr_playingbanner->setScale(1.3f);

	spr_player->setPosition(Vec2(INIT_PLAYER_X, INIT_PLAYER_Y));
	spr_player->setAnchorPoint(ccp(0, 0));
	spr_player->setScale(1.0f);

	spr_bird->setPosition(Vec2(INIT_BLOCK_X, INIT_BLOCK_Y));
	spr_bird->setAnchorPoint(ccp(0, 0));
	spr_bird->setScale(1.0f);

	spr_but_play->setPosition(Vec2(270, 160));
	spr_but_replay->setPosition(Vec2(170, 160));
	spr_but_skip->setPosition(Vec2(370, 160));
}

void HelloWorld::initChild()
{
	this->addChild(spr_nonebanner, 2);

	this->addChild(spr_playingbanner, 2);

	this->addChild(spr_background_1, 0);
	this->addChild(spr_background_2, 0);

	this->addChild(spr_player, 0);
	this->addChild(spr_bird, 0);

	this->addChild(spr_but_play, 1);
	this->addChild(spr_but_replay, 1);
	this->addChild(spr_but_skip, 1);

	//this->addChild(lab_runaway, 3);
	this->addChild(lab_score, 3);
	this->addChild(lab_gameover, 3);
}

void HelloWorld::initLabel()
{
	lab_score = Label::createWithSystemFont("", "", 32);
	lab_score->setAnchorPoint(Vec2(0, 0));
	lab_score->setColor(Color3B::BLACK);
	lab_score->setPosition(Vec2(10, 715));

	lab_gameover = Label::createWithSystemFont("Game Over", "Thonburi", 64);
	lab_gameover->setColor(Color3B::BLACK);
	lab_gameover->setPosition(Point(270, 480));
}

void HelloWorld::initListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
}

void HelloWorld::initAnimation()
{
	auto player_ani = Animation::create();
	player_ani->setDelayPerUnit(0.1f);

	for (int i = 0; i < 8; i ++)
	{
		player_ani->addSpriteFrameWithFileName(StringUtils::format("student_%d.png", i));
	}

	auto bird_ani = Animation::create();
	bird_ani->setDelayPerUnit(0.1f);

	for (int i = 0; i < 7; i++)
	{
		bird_ani->addSpriteFrameWithFileName(StringUtils::format("tabacco_%d.png", i));
	}

	auto act_player_ani = RepeatForever::create(Animate::create(player_ani));
	spr_player->runAction(act_player_ani);

	auto act_bird_ani = RepeatForever::create(Animate::create(bird_ani));
	spr_bird->runAction(act_bird_ani);
}

void HelloWorld::initBG()
{
	spr_background_1->setPosition(Vec2(0, 0));
	spr_background_1->setAnchorPoint(Vec2(0, 0));
	spr_background_2->setPosition(Vec2(-540, 0));
	spr_background_2->setAnchorPoint(Vec2(0, 0));

	auto act_BGA_1 = Sequence::create(
									MoveTo::create(5, Vec2(540, 0)),
									Place::create(Vec2(0, 0)),
									NULL			
									);
	auto act_BGA_2 = Sequence::create(
									MoveTo::create(5, Vec2(0, 0)),
									Place::create(Vec2(-540, 0)),
									NULL
									);

	auto act_BGA_1_repeat = RepeatForever::create(act_BGA_1);
	auto act_BGA_2_repeat = RepeatForever::create(act_BGA_2);

	spr_background_1->runAction(act_BGA_1_repeat);
	spr_background_2->runAction(act_BGA_2_repeat);
}

void HelloWorld::changeStateNone()
{
	spr_bird->stopAllActions();
	initAnimation();

	SimpleAudioEngine::getInstance()->playBackgroundMusic("awesomeness.wav");

	player_alive = true;
	distance = 0;

	game_state = NONE;

//	lab_runaway->runAction(Show::create());
	lab_gameover->runAction(Hide::create());
	lab_score->runAction(Hide::create());
	
	spr_player->runAction(Show::create());
	spr_player->setPosition(Vec2(INIT_PLAYER_X, INIT_PLAYER_Y));

	spr_bird->setPosition(Vec2(INIT_BLOCK_X, INIT_BLOCK_Y));

	spr_but_play->runAction(Show::create());
	spr_but_replay->runAction(Hide::create());
	spr_but_skip->runAction(Hide::create());

	spr_nonebanner->runAction(Show::create());
	spr_playingbanner->runAction(Hide::create());
}

void HelloWorld::changeStatePlaying()
{
	player_alive = true;
	distance = 0;

	game_state = PLAYING;

	SimpleAudioEngine::getInstance()->playBackgroundMusic("background.wav");

	spr_player->stopAllActions();
	spr_bird->stopAllActions();
	initAnimation();

//	lab_runaway->runAction(Hide::create());
	lab_gameover->runAction(Hide::create());
	lab_score->runAction(Show::create());

	spr_player->runAction(Show::create());
	spr_player->setPosition(Vec2(INIT_PLAYER_X, INIT_PLAYER_Y));

	spr_bird->setPosition(Vec2(INIT_BLOCK_X, INIT_BLOCK_Y));

	spr_but_play->runAction(Hide::create());
	spr_but_replay->runAction(Hide::create());
	spr_but_skip->runAction(Hide::create());

	spr_nonebanner->runAction(Hide::create());
	spr_playingbanner->runAction(Show::create());

}

void HelloWorld::changeStateGameover()
{
	stopAllActions();
	
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("ThisGameIsOver.wav");

	game_state = GAMEOVER;

	player_alive = false;

//	lab_runaway->runAction(Hide::create());
	lab_gameover->runAction(Show::create());
	lab_score->runAction(Show::create());

	spr_player->runAction(Hide::create());

	spr_but_play->runAction(Hide::create());
	spr_but_replay->runAction(Show::create());
	spr_but_skip->runAction(Show::create());

	lab_gameover->runAction(Show::create());

	spr_nonebanner->runAction(Hide::create());
	spr_playingbanner->runAction(Show::create());

	touch_num = 1;
}

void HelloWorld::update(float delta)
{
	Node::update(delta);

	if (game_state == PLAYING)
	{
		distance++;
	}

	pos_player = spr_player->getPosition();
	pos_bird = spr_bird->getPosition();

	lab_score->setString(StringUtils::format("%d m", distance / 10));

	if (player_alive == true)
	{
		if (spr_player ->boundingBox().intersectsRect(spr_bird->boundingBox()))
		{
			changeStateGameover();
		}
	}

	if (game_state == PLAYING)
	{
		spr_bird->runAction(Place::create(spr_bird->getPosition() - Vec2((float)(touch_num / 2), 0.f)));

		if (touch_num == 1)
		{
			spr_bird->runAction(Place::create(spr_bird->getPosition() - Vec2(1.0f, 0.f)));
		}
	}
}

void HelloWorld::cheerUp(float dt)
{
	spr_bird->setColor(Color3B(255-dt, 255-dt, 255-dt));
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* pEvent)
{
	SimpleAudioEngine::getInstance()->playEffect("click.wav", false);

	if (game_state == PLAYING)
	{
		if (player_alive == true)
		{
			distance += move_x / 6;

			spr_bird->setAnchorPoint(Vec2(0, 0));

			auto action = Place::create(Vec2(pos_bird.x + move_x, pos_bird.y));
			spr_bird->runAction(action);

			touch_num++;
		}
	}

	rect_play = spr_but_play->getBoundingBox();
	rect_replay = spr_but_replay->getBoundingBox();
	rect_skip = spr_but_skip->getBoundingBox();

	t_location = touch->getLocation();
	
	if (rect_play.containsPoint(t_location))
	{
		if (game_state == NONE)
		{
			changeStatePlaying();
		}
	}

	if (rect_replay.containsPoint(t_location))
	{
		if (game_state == GAMEOVER)
		{
			touch_num = 1;
			changeStatePlaying();
		}
	}

	if (rect_skip.containsPoint(t_location))
	{
		if (game_state == GAMEOVER)
		{
			changeStateNone();
		}
	}
	
	return true;
}
