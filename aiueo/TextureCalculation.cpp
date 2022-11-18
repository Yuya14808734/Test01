#include "TextureCalculation.h"
#include <stdio.h>

//--------------------------------------------------
//概要		:分割しているテクスチャの位置をFloat2で返す
//
//StartPos	:最初に表示したい画像の番号
//EndPos	:最後に表示したい画像の番号
//wight		:横の画像の枚数
//hight		:縦の画像の枚数
//Update	:画像を更新したいフレーム
//--------------------------------------------------

TextureMove::TextureMove(void)
{
	StartNum = 1;		//最初の画像の枚数
	EndNum = 1;			//最後の画像の枚数
	Unum = 1;			//縦の画像の数
	Vnum = 1;			//横の画像の数
	UpdateNum = 1;		//変えるフレームの数
	XU = 0.0f;			//縦座標
	YV = 0.0f;			//横座標

	InitMove = false;		//テクスチャを動かす初期化をしたか
	InitScroll = false;		//テクスチャをスクロールする初期化をしたか
	UWight = 1.0f;		//画像を横に分けた幅・横に動く距離
	VHight = 1.0f;		//画像を縦に分けた幅・縦に動く距離
	XSpeed = 0.0f;
	YSpeed = 0.0f;
	FpsCount = 0;		//フレームを数える
	NowNum = 1;			//今いる番号
	NumAdd = 1;			//足す数(バックするときに負の数になる)
}

TextureMove::~TextureMove(void)
{

}

void TextureMove::InitTexturePosition(int StartPos, int EndPos, int wight, int hight, int Update)
{
	//最初に配列の番号にする
	StartPos--;
	EndPos--;

	//最初の番号を入れる
	StartNum = StartPos;
	//最後の番号を入れる
	EndNum = EndPos;
	//横の画像枚数を入れる
	Unum = wight;
	//縦の画像枚数を入れる
	Vnum = hight;
	//どの間隔で入れ替わるかを入れる
	UpdateNum = Update;

	//画像一枚の横・縦の長さを入れている
	UWight = 1.0f / Unum;
	VHight = 1.0f / Vnum;

	//始まりの位置
	XU = (StartNum % Unum) * UWight;
	YV = (StartNum / Unum) * VHight;

	NowNum = StartNum;
	NumAdd = 1;

	//ちゃんと動く初期化をしました
	InitMove = true;
	//スクロールする初期化はしていません
	InitScroll = false;
}

//画像のポジションを入れている
void TextureMove::InitTexturePosition(int TexturePosition, int wight, int hight)
{
	//画像一枚の横・縦の長さを入れている
	UWight = 1.0f / wight;
	VHight = 1.0f / hight;
	XU = (TexturePosition % wight) * UWight;
	YV = (TexturePosition / hight) * VHight;
	//動かす初期化はしていません。
	InitMove = false;
	InitScroll = false;
}

void TextureMove::InitTextureScrollPosition(float XMoveSpeed, float YMoveSpeed, float XStartPos, float YStartPos,float XWight,float YHight)
{
	//動かす初期化はしていません。
	InitMove = false;
	//スクロールする初期化はしました。
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
		//カウントが指定の数字になった時に(最後)
		if (FpsCount % UpdateNum == UpdateNum - 1)
		{
			//アップデート
			XU += UWight;
			NowNum++;

			//最後の画像を超えたら
			if (XU >= 1.0f)
			{
				XU = 0.0f;
				YV += VHight;

				if (YV >= 1.0f)
				{
					YV = 0.0f;
				}
			}
			

			//もし最後の位置まで行ったら
			if (NowNum > EndNum)
			{
				//始まりの位置
				XU = (StartNum % Unum) * UWight;
				YV = (StartNum / Unum) * VHight;

				//最初の位置と最後の位置の差を入れその後に最初の一枚を入れる
				NowNum = StartNum;
			}

		}//if

		FpsCount++;
		//return 
	}
	else
	{
		printf("ループの初期化がされていません。");
	}
}


void TextureMove::UpdatePositionBack(void)
{
	if (InitMove)
	{
		//数え始める時に(最初)
		if (FpsCount % UpdateNum == 0)
		{
			//アップデート
			//横の数何枚目かを入れている
			XU = (NowNum % Unum) * UWight;
			//縦の数何枚目かを入れている
			YV = (NowNum / Unum) * VHight;

			NowNum += NumAdd;

			//最後か最初の位置に戻ったら戻す
			if (NowNum == EndNum || NowNum == StartNum)
			{
				NumAdd *= -1;
			}

		}//if

		FpsCount++;
	}
	else
	{
		printf("バックの初期化がされていません。");
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
		printf("スクロールの初期化がされていません。");
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