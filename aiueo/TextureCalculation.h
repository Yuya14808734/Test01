//#pragma once

#ifndef _H_TEXTURECALCULATION_
#define _H_TEXTURECALCULATION_

//#include "object.h"

class TextureMove
{
	private:

		int StartNum;		//最初の画像の枚数
		int EndNum;			//最後の画像の枚数
		int Unum;			//縦の画像の数
		int Vnum;			//横の画像の数
		int UpdateNum;		//変えるフレームの数
		float XU;			//縦座標
		float YV;			//横座標

		bool InitMove;		//テクスチャを動かす初期化をしたか
		bool InitScroll;	//テクスチャをスクロールする初期化をしたか
		float UWight;		//画像を横に分けた幅・横に動く距離
		float VHight;		//画像を縦に分けた幅・縦に動く距離
		float XSpeed;
		float YSpeed;
		int FpsCount;		//フレームを数える
		int NowNum;			//今いる番号
		int NumAdd;			//足す数(バックするときに負の数になる)
		
		
		
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


