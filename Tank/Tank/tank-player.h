#pragma once
#include "common.h"
#include "tank-common.h"
#include "game-clock.h"

typedef struct {
	bool mDied; // �������ֵ�Ƿ�����
	byte playerId; // ���ID��0/1
	byte mTankLevel; // ̹�˵ȼ�[1-4]
	IMAGE mTankImage[4][4][2]; // ���ּ����ĸ�����ÿ������������ʽʵ��̹���Ĵ�ת����Ч��
	int tankPlayerX, tankPlayerY; // ̹�����ĵ�����
	int tankWidth, tankHeight; // ̹�˵ĳ��Ϳ�
	byte tankDir; // ̹�˷���0-�ϡ�1-�ҡ�2-�¡�3-��

	int mPlayerLife; // ���Ĭ������ֵΪ3
	int mPlayerLife_x, 						// ͼ������
		mPlayerLife_y;

	StarFourPoint mStar;			// �Ľ�����˸��
	// RingClass mRing;				// ����Ȧ�࣬�Ľ��ǳ���֮����ر���Ȧ
	// PropClass mProp;				// ������

	TimeClock mTankTimer;		// ̹���ƶ��ٶ�
	TimeClock mBulletTimer;		// �ӵ��ƶ��ٶ�
	TimeClock mBombTimer;		// �ӵ���ը�ٶ�
	int mMoveSpeedDev[4];	// �ĸ�����̹���ƶ�ʱ����
	int mBulletSpeedDev[4];	// ��ͬ�����ӵ�ʱ�����ٶ�

	IMAGE mEmermyScoreImg[4];	// 100\200.. ��, ��ͬ�л���ըλ����ʾ�ķ���

	// �Ҳ���Ϣ��
	IMAGE m12PImage;   // 1P\2P ͼ��
	IMAGE mPlayerTankIcoImage;
	IMAGE mPlayerTankIcoImage;				// ���̹��ͼ��
	int   mPlayerTankIcoImage_x,			// ͼ������
		mPlayerTankIcoImage_y;
	IMAGE mBlackNumberImage;				// 0123456789 ��ɫ����
}TankPlayer;