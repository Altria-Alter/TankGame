#include "tank-player.h"
#include "game-clock.h"

extern HDC center_hdc; // �м���Ϸ���򣬷ֿ����Ʒ�����и���

/**
	�����̹����Դ���г�ʼ��
*/
void tank_player_init(TankPlayer* tankPlayer, int playerID, 
	int tankX, int tankY, 
	int iconLife_x, int iconLife_y) 
{	
	tankPlayer->mDied = false;
	tankPlayer->playerId = playerID;
	tankPlayer->mTankLevel = 1;
	tankPlayer->mTankMoving = false;

	// ��䲻ͬ����̹�ˡ������Ӧ��ͼƬ��Դ
	int level, dir;
	TCHAR c[50] = { 0 };
	switch (playerID)
	{
	case 0:
	case 1:		
		for (level = 0; level < 4; level++)
		{
			for (dir = 0; dir < 4; dir++) // ��ʾ������������
			{
				_stprintf_s(c, L"./res/big/%dPlayer/m%d-%d-1.gif", playerID, level, dir); // ͬһ����ͼ��1
				loadimage(&tankPlayer->mTankImage[level][dir][0], c);
				_stprintf_s(c, L"./res/big/%dPlayer/m%d-%d-2.gif", playerID, level, dir); // ͬһ����ͼ��2
				loadimage(&tankPlayer->mTankImage[level][dir][1], c);
			}
		}
		break;
	default:
		break;
	}

	// ���ó�ʼ�����ͳ���
	tankPlayer->tankPlayerX = tankX;
	tankPlayer->tankPlayerY = tankY;
	tankPlayer->tankWidth = TANK_WIDTH;
	tankPlayer->tankHeight = TANK_HEIGHT;
	tankPlayer->tankDir = DIR_UP;

	tankPlayer->mPlayerLife = 3; // Ĭ������ֵ
	tankPlayer->mPlayerIconLife_x = iconLife_x;
	tankPlayer->mPlayerIconLife_y = iconLife_y;

	// ��ʼ���Ľ�����Դ��״̬
	TCHAR buf[100] = {0};
	// �����Ľ�����˸
	for (int i = 0; i < 4; i++)
	{
		_stprintf_s(buf, _T("./res/big/star%d.gif"), i);
		loadimage(&tankPlayer->mStar.mStarImage[i], buf);
	}
	tankPlayer->mStar.starState = Star_Begin; // �Ľ��Ǹճ���
	tankPlayer->mStar.mStarCounter = 0;
	tankPlayer->mStar.mStarIndex = 0;
	tankPlayer->mStar.mStarIndexDir = 1; // ��ʼ�±�����С���

	// ��ʼ��������
	TCHAR cir_buf[100];
	for (int i = 0; i < 2; i++)
	{
		_stprintf_s(cir_buf, _T("./res/big/ring%d.gif"), i);
		loadimage(&tankPlayer->mProtecCircle.protecImage[i], cir_buf);
	}	
	tankPlayer->mProtecCircle.needShow = true;
	tankPlayer->mProtecCircle.imageIndex = 0;
	tankPlayer->mProtecCircle.timerCount = 0;

	// ��ʼ��̹���ƶ����ӵ��ٶȡ���ը�ٶȼ�����
	clock_init(&tankPlayer->mTankMoveTimer, tankPlayer->mMoveSpeedDev[tankPlayer->mTankLevel]);
	clock_init(&tankPlayer->mBulletTimer, tankPlayer->mBulletSpeedDev[tankPlayer->mTankLevel]);
	clock_init(&tankPlayer->mBombTimer, BOMB_SPEED);

}

/**
	���̹���Ľ�����˸��ֻ���ڽ����¹ؿ���һ��ʱ�Ż�����Ľ��ǣ���Ϸ������ֻ����ֱ���Ȧ
*/
void tank_player_show_star(TankPlayer* tankPlayer) {
	if (tankPlayer->mStar.starState == Star_End) { // ���̹���Ѿ���������ʾ�Ľ���
		return;
	}

	if (tankPlayer->mStar.mStarCounter % 2 == 0) { // ��ѭ�������ż���μ����������Ľ���ͼƬ
		if (tankPlayer->mStar.mStarIndex > 3) {
			tankPlayer->mStar.mStarIndexDir = -1; // ��ʼ�ɴ��С
		}
		else if (tankPlayer->mStar.mStarIndex < 0) {
			tankPlayer->mStar.mStarIndexDir = 1; // ��ʼ��С���
		}

		tankPlayer->mStar.mStarIndex += tankPlayer->mStar.mStarIndexDir;
	}
	if (tankPlayer->mStar.mStarCounter++ > 25) {
		tankPlayer->mStar.starState = Star_End; // �Ľ�����˸���
		return;
	}

	// ���ռ�����±�����Ľ���ͼƬ����
	TransparentBlt(center_hdc, 
		tankPlayer->tankPlayerX - BOX_SIZE, tankPlayer->tankPlayerY - BOX_SIZE, BOX_SIZE * 2, BOX_SIZE*2,
		GetImageHDC(&tankPlayer->mStar.mStarImage[tankPlayer->mStar.mStarIndex]),
		0, 0, BOX_SIZE * 2, BOX_SIZE * 2,
		0x000000);
}

/**
	�������̹��
*/
void tank_player_draw_tank(TankPlayer* tankPlayer) {
	if (tankPlayer->mStar.starState != Star_End) { // ������ڻ����Ľ����򷵻�
		return;
	}

	int dirIndex = 0;
	if (tankPlayer->mTankMoving) { // ���̹�����ƶ��������ͬһ����ͼƬ�л�ʵ�ֶ�̬�Ĵ�Ч��
		dirIndex = dirIndex == 0 ? 1 : 0;
	}
	IMAGE tank = tankPlayer->mTankImage[tankPlayer->mTankLevel][tankPlayer->tankDir][dirIndex];
	TransparentBlt(center_hdc, tankPlayer->tankPlayerX - BOX_SIZE, tankPlayer->tankPlayerY - BOX_SIZE,
		BOX_SIZE * 2, BOX_SIZE * 2,
		GetImageHDC(&tank),
		0, 0,
		BOX_SIZE * 2, BOX_SIZE * 2,
		0x000000);

	// �ж��Ƿ���ʾ����������
	if (tankPlayer->mProtecCircle.needShow) {
		tankPlayer->mProtecCircle.timerCount++;
		if (tankPlayer->mProtecCircle.timerCount > 215) { // ����Ȧ��Чʱ�䵽
			tankPlayer->mProtecCircle.needShow = false;
			tankPlayer->mProtecCircle.timerCount = 0;
		}
		else {
			tankPlayer->mProtecCircle.imageIndex = tankPlayer->mProtecCircle.timerCount / 4 % 2; // ÿ��һ��ʱ���ٽ���ͼƬ�л����൱��ÿѭ���ĸ����ڽ����л�
			TransparentBlt(center_hdc, tankPlayer->tankPlayerX - BOX_SIZE, tankPlayer->tankPlayerY - BOX_SIZE,
				BOX_SIZE * 2, BOX_SIZE * 2,
				GetImageHDC(&tankPlayer->mProtecCircle.protecImage[tankPlayer->mProtecCircle.imageIndex]),
				0, 0,
				BOX_SIZE * 2, BOX_SIZE * 2,
				0x000000);
		}		
	}
}