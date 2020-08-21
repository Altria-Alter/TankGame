#include "tank-common.h"

/**
	�Ľ���ͼƬ��Դ��ʼ��
*/
void star_load_resource(StarFourPoint* starFourPoint) {
	TCHAR buf[100];
	// �����Ľ�����˸
	for (int i = 0; i < 4; i++)
	{
		_stprintf_s(buf, _T("./res/big/star%d.gif"), i);
		loadimage(&starFourPoint->mStarImage[i], buf);
	}
}

/**
	�ṹ��������Գ�ʼ��
*/
void star_init(StarFourPoint* starFourPoint) {
	starFourPoint->mStarIndex = 3;
	starFourPoint->mStarCounter = 0;
	starFourPoint->starState = Star_Out; // �Ľ��Ǹճ���
}