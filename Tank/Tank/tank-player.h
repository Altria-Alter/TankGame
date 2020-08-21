#pragma once
#include "common.h"
#include "tank-common.h"
#include "game-clock.h"

#define BOMB_SPEED 20 // �ڵ���ը�ٶ�

typedef enum {
	LEFT,
	UP,
	RIGHT,
	DOWN
}TANK_DIDIR;

typedef struct {
	bool mDied; // �������ֵ�Ƿ�����
	byte playerId; // ���ID��0/1
	byte mTankLevel; // ̹�˵ȼ�[1-4]
	IMAGE mTankImage[4][4][2]; // ���ּ����ĸ�����ÿ������������ʽʵ��̹���Ĵ�ת����Ч��
	int tankPlayerX, tankPlayerY; // ̹�����ĵ�����
	int tankWidth, tankHeight; // ̹�˵ĳ��Ϳ�
	TANK_DIDIR tankDir; // ̹�˷���0-��1-�ϡ�2-�ҡ�3-�£�����ԴͼƬ��Ӧ

	int mPlayerLife; // ���Ĭ������ֵΪ3
	int mPlayerIconLife_x, 						// ͼ������
		mPlayerIconLife_y;

	StarFourPoint mStar;			// �Ľ�����˸��
	// RingClass mRing;				// ����Ȧ�࣬�Ľ��ǳ���֮����ر���Ȧ
	// PropClass mProp;				// ������

	int mMoveSpeedDev[4] = {21, 19, 17, 15};	// �ĸ�����̹���ƶ�ʱ����
	int mBulletSpeedDev[4] = {17, 16, 15, 14 };	// ��ͬ�����ӵ�ʱ�����ٶ�
	TimeClock mTankMoveTimer;		// ̹���ƶ��ٶ�
	TimeClock mBulletTimer;		// �ӵ��ƶ��ٶ�
	TimeClock mBombTimer;		// �ӵ���ը�ٶ�	

}TankPlayer;

/**
	�����̹����Դ���г�ʼ��
*/
void tank_player_init(TankPlayer* tankPlayer, int playerID,
	int tankX, int tankY,
	int iconLife_x, int iconLife_y);