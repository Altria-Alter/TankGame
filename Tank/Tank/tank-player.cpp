#include "tank-player.h"
#include "game-clock.h"

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

	// ��䲻ͬ����̹�ˡ������Ӧ��ͼƬ��Դ
	int level, dir;
	switch (playerID)
	{
	case 0:
	case 1:
	{
		TCHAR c[50] = {0};
		for (level = 0; level < 4; level++) {		
		{
			for (dir = 0; dir < 4; dir++) // ��ʾ������������
				_stprintf_s(c, L"./res/big/%dPlayer/m%d-%d-1.gif", playerID, level, dir); // ͬһ����ͼ��1
				loadimage(&tankPlayer->mTankImage[level][dir][0], c);
				_stprintf_s(c, L"./res/big/%dPlayer/m%d-%d-2.gif", playerID, level, dir); // ͬһ����ͼ��2
				loadimage(&tankPlayer->mTankImage[level][dir][1], c);
			}			
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
	tankPlayer->tankDir = UP;

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
	tankPlayer->mStar.starState = Star_Out; // �Ľ��Ǹճ���

	// ��ʼ��̹���ƶ����ӵ��ٶȡ���ը�ٶȼ�����
	clock_init(&tankPlayer->mTankMoveTimer, tankPlayer->mMoveSpeedDev[tankPlayer->mTankLevel]);
	clock_init(&tankPlayer->mBulletTimer, tankPlayer->mBulletSpeedDev[tankPlayer->mTankLevel]);
	clock_init(&tankPlayer->mBombTimer, BOMB_SPEED);

}