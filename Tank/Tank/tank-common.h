#pragma once
// ��Ҫ���������һЩ���̹����з�̹�˹�ͬʹ�õ�һЩ���ܣ��磺̹��λ�ú��ӱ�ǡ��ӵ��ṹ���ӵ���ը��̹�˱�ը�����/�л��Ľ�����˸���������

#include "common.h"

// �Ľ�����˸���л�������ҵ��Ľ�����˸��������
enum Star_State {
	Star_Timing,		// ֻ���ڵл�, ��ʾ��ǰ��û�г����Ľ���, ���ڼ�ʱ֮��
	Star_Failed,		// ���ڵл�, ��ʾ��ǰλ�õл�����ʧ��
	Star_Out,			// �Ľ��Ǹոճ���
	Star_Showing,		// ������˸�Ľ���
	Star_Stop,			// �ո�ֹͣ��˸
	Tank_Out			// ̹���Ѿ�����
};


typedef struct {
	IMAGE mStarImage[4]; // �����Ľ���ͼƬ
	byte mStarIndex; // �����±�
	int mStarCounter; // �������೤��ѭ�����һ��ͼ��
	Star_State starState;				// �Ľ�����ʧ��ʱ��̹�˳���, ֹͣ�����Ľ�����˸ͼ
}StarFourPoint;