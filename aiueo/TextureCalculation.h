//#pragma once

#ifndef _H_TEXTURECALCULATION_
#define _H_TEXTURECALCULATION_

//#include "object.h"

class TextureMove
{
	private:

		int StartNum;		//�ŏ��̉摜�̖���
		int EndNum;			//�Ō�̉摜�̖���
		int Unum;			//�c�̉摜�̐�
		int Vnum;			//���̉摜�̐�
		int UpdateNum;		//�ς���t���[���̐�
		float XU;			//�c���W
		float YV;			//�����W

		bool InitMove;		//�e�N�X�`���𓮂�����������������
		bool InitScroll;	//�e�N�X�`�����X�N���[�����鏉������������
		float UWight;		//�摜�����ɕ��������E���ɓ�������
		float VHight;		//�摜���c�ɕ��������E�c�ɓ�������
		float XSpeed;
		float YSpeed;
		int FpsCount;		//�t���[���𐔂���
		int NowNum;			//������ԍ�
		int NumAdd;			//������(�o�b�N����Ƃ��ɕ��̐��ɂȂ�)
		
		
		
	public:
		TextureMove(void);
		~TextureMove(void);
		
		void  InitTexturePosition(int StartNum, int EndNum, int wight, int hight, int Update);
		void  InitTexturePosition(int TexturePosition, int wight, int hight);
		void  InitTextureScrollPosition(float XMoveSpeed, float YMoveSpeed,float XStartPos,float YStartPos, float XWight, float YHight);
		void  UpdatePositionLoop(void);
		void  UpdatePositionBack(void);
		void  UpdatePositionScroll(void);
		void  UpdatePositionScroll(float XSpeed,float YSpeed);
		float ReturnPosX(void);
		float ReturnPosY(void);
		float ReturnWightX(void);
		float ReturnHightY(void);
		//
};
#endif // _H_TEXTURECALCULATION_


