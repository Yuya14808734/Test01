#include "TextureCalculation.h"
#include <stdio.h>

//--------------------------------------------------
//�T�v		:�������Ă���e�N�X�`���̈ʒu��Float2�ŕԂ�
//
//StartPos	:�ŏ��ɕ\���������摜�̔ԍ�
//EndPos	:�Ō�ɕ\���������摜�̔ԍ�
//wight		:���̉摜�̖���
//hight		:�c�̉摜�̖���
//Update	:�摜���X�V�������t���[��
//--------------------------------------------------

TextureMove::TextureMove(void)
{
	StartNum = 1;		//�ŏ��̉摜�̖���
	EndNum = 1;			//�Ō�̉摜�̖���
	Unum = 1;			//�c�̉摜�̐�
	Vnum = 1;			//���̉摜�̐�
	UpdateNum = 1;		//�ς���t���[���̐�
	XU = 0.0f;			//�c���W
	YV = 0.0f;			//�����W

	InitMove = false;		//�e�N�X�`���𓮂�����������������
	InitScroll = false;		//�e�N�X�`�����X�N���[�����鏉������������
	UWight = 1.0f;		//�摜�����ɕ��������E���ɓ�������
	VHight = 1.0f;		//�摜���c�ɕ��������E�c�ɓ�������
	XSpeed = 0.0f;
	YSpeed = 0.0f;
	FpsCount = 0;		//�t���[���𐔂���
	NowNum = 1;			//������ԍ�
	NumAdd = 1;			//������(�o�b�N����Ƃ��ɕ��̐��ɂȂ�)
}

TextureMove::~TextureMove(void)
{

}

void TextureMove::InitTexturePosition(int StartPos, int EndPos, int wight, int hight, int Update)
{
	//�ŏ��ɔz��̔ԍ��ɂ���
	StartPos--;
	EndPos--;

	//�ŏ��̔ԍ�������
	StartNum = StartPos;
	//�Ō�̔ԍ�������
	EndNum = EndPos;
	//���̉摜����������
	Unum = wight;
	//�c�̉摜����������
	Vnum = hight;
	//�ǂ̊Ԋu�œ���ւ�邩������
	UpdateNum = Update;

	//�摜�ꖇ�̉��E�c�̒��������Ă���
	UWight = 1.0f / Unum;
	VHight = 1.0f / Vnum;

	//�n�܂�̈ʒu
	XU = (StartNum % Unum) * UWight;
	YV = (StartNum / Unum) * VHight;

	NowNum = StartNum;
	NumAdd = 1;

	//�����Ɠ��������������܂���
	InitMove = true;
	//�X�N���[�����鏉�����͂��Ă��܂���
	InitScroll = false;
}

//�摜�̃|�W�V���������Ă���
void TextureMove::InitTexturePosition(int TexturePosition, int wight, int hight)
{
	//�摜�ꖇ�̉��E�c�̒��������Ă���
	UWight = 1.0f / wight;
	VHight = 1.0f / hight;
	XU = (TexturePosition % wight) * UWight;
	YV = (TexturePosition / hight) * VHight;
	//�������������͂��Ă��܂���B
	InitMove = false;
	InitScroll = false;
}

void TextureMove::InitTextureScrollPosition(float XMoveSpeed, float YMoveSpeed, float XStartPos, float YStartPos,float XWight,float YHight)
{
	//�������������͂��Ă��܂���B
	InitMove = false;
	//�X�N���[�����鏉�����͂��܂����B
	InitScroll = true;

	XSpeed = XMoveSpeed;
	YSpeed = YMoveSpeed;
	XU = XStartPos;
	YV = YStartPos;
	UWight = XWight;
	VHight = YHight;

}

void TextureMove::UpdatePositionLoop(void)
{
	if (InitMove)
	{
		//�J�E���g���w��̐����ɂȂ�������(�Ō�)
		if (FpsCount % UpdateNum == UpdateNum - 1)
		{
			//�A�b�v�f�[�g
			XU += UWight;
			NowNum++;

			//�Ō�̉摜�𒴂�����
			if (XU >= 1.0f)
			{
				XU = 0.0f;
				YV += VHight;

				if (YV >= 1.0f)
				{
					YV = 0.0f;
				}
			}
			

			//�����Ō�̈ʒu�܂ōs������
			if (NowNum > EndNum)
			{
				//�n�܂�̈ʒu
				XU = (StartNum % Unum) * UWight;
				YV = (StartNum / Unum) * VHight;

				//�ŏ��̈ʒu�ƍŌ�̈ʒu�̍�����ꂻ�̌�ɍŏ��̈ꖇ������
				NowNum = StartNum;
			}

		}//if

		FpsCount++;
		//return 
	}
	else
	{
		printf("���[�v�̏�����������Ă��܂���B");
	}
}


void TextureMove::UpdatePositionBack(void)
{
	if (InitMove)
	{
		//�����n�߂鎞��(�ŏ�)
		if (FpsCount % UpdateNum == 0)
		{
			//�A�b�v�f�[�g
			//���̐������ڂ������Ă���
			XU = (NowNum % Unum) * UWight;
			//�c�̐������ڂ������Ă���
			YV = (NowNum / Unum) * VHight;

			NowNum += NumAdd;

			//�Ōォ�ŏ��̈ʒu�ɖ߂�����߂�
			if (NowNum == EndNum || NowNum == StartNum)
			{
				NumAdd *= -1;
			}

		}//if

		FpsCount++;
	}
	else
	{
		printf("�o�b�N�̏�����������Ă��܂���B");
	}
}

void TextureMove::UpdatePositionScroll(float NowXSpeed,float NowYSpeed)
{
	if (InitScroll)
	{
		XU += NowXSpeed;
		YV += NowYSpeed;

		if (XU >= 1.0f)
		{
			XU = 0.0f;
		}
		if (YV >= 1.0f)
		{
			YV = 0.0f;
		}
		if (XU < 0.0f)
		{
			XU = 1.0f;
		}
		if (YV < 0.0f)
		{
			YV = 1.0f;
		}
	}
	else
	{
		printf("�X�N���[���̏�����������Ă��܂���B");
	}
}

void TextureMove::UpdatePositionScroll(void)
{
	UpdatePositionScroll(XSpeed, YSpeed);
}

float TextureMove::ReturnPosX(void)
{
	printf("%f\n", XU);
	return XU;
}

float  TextureMove::ReturnPosY(void)
{
	printf("%f\n", YV);
	return YV;
}

float TextureMove::ReturnWightX(void)
{
	printf("%f\n",UWight );
		return UWight;
}
float TextureMove::ReturnHightY(void)
{
	printf("%f\n", VHight);
	getchar();
	return VHight;
}