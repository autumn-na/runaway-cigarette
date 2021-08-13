#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#define INIT_PLAYER_X 50
#define INIT_PLAYER_Y 260
#define INIT_BLOCK_X 400
#define INIT_BLOCK_Y 260

enum
{
	NONE,
	PLAYING,
	GAMEOVER
};

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
	Sprite* spr_nonebanner = Sprite::create("nonebanner.png");
	Sprite* spr_playingbanner = Sprite::create("playingbanner.png");
	Sprite* spr_background_1 = Sprite::create("background1.png");
	Sprite* spr_background_2 = Sprite::create("background1.png");
	Sprite* spr_player = Sprite::create("student_0.png");
	Sprite* spr_bird = Sprite::create("tabacco_0.png");

	Sprite* spr_but_play = Sprite::create("playbutton.png");
	Sprite* spr_but_replay = Sprite::create("replaybutton.png");
	Sprite* spr_but_skip = Sprite::create("skipbutton.png");

	Point pos_player;
	Point pos_bird;
	Point t_location;

	Rect rect_play;
	Rect rect_replay;
	Rect rect_skip;

	Label* lab_gameover;
	Label* lab_score;
	Label* lab_runaway;

	Show* act_show;
	Hide* act_hide;

	bool player_alive;

	int game_state;

	int touch_num = 1;
	int distance;

	int player_x;
	int player_y;

	int move_x;
	int move_time;

    static cocos2d::Scene* createScene();
    virtual bool init();

	bool onTouchBegan(Touch* touch, Event* pEvent);

	virtual void update(float delta);

	void initSpr();
	void initChild();
	void initLabel();
	void initListener();
	void initAnimation();
	void initBG();

	void changeStateNone();
	void changeStatePlaying();
	void changeStateGameover();

	void cheerUp(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
