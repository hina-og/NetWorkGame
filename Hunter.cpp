#include "Hunter.h"
#include "Camera.h"
#include "Stage.h"
#include"Player.h"


Hunter::Hunter(GameObject* parent)
{
}

void Hunter::Initialize()
{
	hArrow_ = LoadGraph("Assets//arrow.png");
	assert(hArrow_ >= 0);
	speed_ = 2;
	x = initPosX;
	y = initPosY;

	state_ = CANLOOK;
}

void Hunter::Update()
{
	Camera* cam = (Camera*)FindObject("Camera");

	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
	{
		cam->camX += speed_;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
	{
		cam->camX -= speed_;
	}
	if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
	{
		cam->camY += speed_;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
	{
		cam->camY -= speed_;
	}

	switch (state_)
	{
	case NONE:
	{
		break;
	}
	case SPEEDUP:
	{
		
		break;
	}
	case CANLOOK:
	{
		Player* pPl = GetParent()->FindGameObject<Player>();
		/*VECTOR Graphvec;
		Graphvec = {(float)initPosX -  (float)initPosX,0.0f,-(float)initPosY - (float)initPosY };*/
		VECTOR Enemyvec;
		Enemyvec = { pPl->GetPosition().x - ((float)x - cam->camX) ,0.0f,pPl->GetPosition().y - (float)y - cam->camY };

		angle_ = atan2(Enemyvec.z, Enemyvec.x);
		break;
	}
	default:
		break;
	}
}

void Hunter::Draw()
{
	Camera* cam = (Camera*)FindObject("Camera");
	if (cam->isZoom_)
	{
		DrawCircle(initPosX, initPosY, STAGE::TILE_SIZE / 2 * cam->camDist, GetColor(255, 0, 0), TRUE);
	}
	else
	{
		DrawCircle(x - cam->camX, y - cam->camY, STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), TRUE);
	}

	switch (state_)
	{
	case NONE:
	{
		break;
	}
	case SPEEDUP:
	{
		break;
	}
	case CANLOOK:
	{
		DrawRotaGraph(initPosX - cam->camX, initPosY - cam->camY, 1.0, angle_, hArrow_, TRUE, FALSE);
		break;
	}
	default:
		break;
	}
}

void Hunter::Release()
{
}