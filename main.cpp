#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdlib.h>
#include <time.h>
const char kWindowTitle[] = "LC1A_09_コヤマタクミ";

typedef struct Vector2 {
	float x;
	float y;
};

typedef struct Particle {
	Vector2 position;
	int isActive;
	unsigned int carentAlpha;
	float size;
	int gh;
};

typedef struct player {
	Vector2 pos;
	float speed;
	float size;
	int gh;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	player player{
		{700,400},
		5,
		30,
		Novice::LoadTexture("./player.png")
	};

	const int max = 90;

	const int eMax = 10;

	Particle effect[max];

	for (int i = 0; i < eMax; i++)
	{
		effect[i].isActive = false;
		effect[i].position.x = player.pos.x;
		effect[i].position.y = player.pos.y;
		effect[i].carentAlpha = 0x22;
		effect[i].size = 40;
		effect[i].gh = Novice::LoadTexture("./player.png");
	};

	int flag = false;

	Particle trajectory[max];

	for (int i = 0; i < max; i++)
	{
		trajectory[i].isActive = false;
		trajectory[i].position.x = player.pos.x;
		trajectory[i].position.y = player.pos.y;
		trajectory[i].carentAlpha = 0x22;
		trajectory[i].size = 30;
	};

	int frameCount = 0;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//移動している時
		if (flag)
		{
			//パーティクル生成
			for (int i = 0; i < max; i++)
			{
				//パーティクルがアクティブじゃない
				if (!trajectory[i].isActive)
				{
					trajectory[i].isActive = true;
					trajectory[i].position.x = player.pos.x - player.size / 2;
					trajectory[i].position.y = player.pos.y - player.size / 2;
					trajectory[i].size = 30;
					trajectory[i].carentAlpha = 0x22;
					break;
				}
				//アクティブ
				else
				{
					trajectory[i].carentAlpha -= 0x02;
					if (trajectory[i].carentAlpha <= 0x00) {
						trajectory[i].isActive = false;
					}
				}
			}
		}
		//移動してないとき
		else
		{
			for (int i = 0; i < max; i++)
			{
				//i番目のパーティクルがアクティブなら
				if (trajectory[i].isActive)
				{
					trajectory[i].carentAlpha -= 0x02;
					if (trajectory[i].carentAlpha <= 0x00)
					{
						trajectory[i].isActive = false;
					}
				}
			}
		}

		if (keys[DIK_SPACE]) {

			frameCount++;

			//パーティクル生成
			for (int i = 0; i < eMax; i++)
			{
				//パーティクルがアクティブじゃない
				if (!effect[i].isActive)
				{
					if (frameCount % 8 == 0)
					{
						effect[i].position.x = 0;
						effect[i].position.y = 1;
					}
					else if (frameCount % 8 == 1)
					{
						effect[i].position.x = -1;
						effect[i].position.y = 1;
					}
					else if (frameCount % 8 == 2)
					{
						effect[i].position.x = -1;
						effect[i].position.y = 0;
					}
					else if (frameCount % 8 == 3)
					{
						effect[i].position.x = -1;
						effect[i].position.y = -1;
					}
					else if (frameCount % 8 == 4)
					{
						effect[i].position.x = 0;
						effect[i].position.y = -1;
					}
					else if (frameCount % 8 == 5)
					{
						effect[i].position.x = 1;
						effect[i].position.y = -1;
					}
					else if (frameCount % 8 == 6)
					{
						effect[i].position.x = 1;
						effect[i].position.y = 0;
					}
					else if (frameCount % 8 == 7)
					{
						effect[i].position.x = 1;
						effect[i].position.y = 1;
					}
					effect[i].isActive = true;

					effect[i].size = 40;
					effect[i].carentAlpha = 0x22;
					break;
				}
				//アクティブ
				else
				{
					effect[i].size -= 2;
					if (effect[i].size <= 0) {
						effect[i].isActive = false;
					}
				}
			}
		}

		else
		{
			for (int i = 0; i < eMax; i++)
			{
				frameCount = 0;
				if (effect[i].isActive)
				{
					effect[i].carentAlpha -= 0x02;
					if (effect[i].carentAlpha <= 0x00)
					{
						effect[i].isActive = false;
					}
				}
			}
		}


		if (keys[DIK_UP] || keys[DIK_W]) {
			player.pos.y -= player.speed;
			flag = true;
		}

		else if (keys[DIK_LEFT] || keys[DIK_A]) {

			player.pos.x -= player.speed;
			flag = true;

		}

		else if (keys[DIK_DOWN] || keys[DIK_S]) {

			player.pos.y += player.speed;
			flag = true;

		}

		else if (keys[DIK_LEFT] || keys[DIK_D]) {

			player.pos.x += player.speed;
			flag = true;
		}

		else
		{
			flag = false;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawQuad(player.pos.x - player.size / 2, player.pos.y - player.size / 2,
			player.pos.x + player.size / 2, player.pos.y - player.size / 2,
			player.pos.x - player.size / 2, player.pos.y + player.size / 2,
			player.pos.x + player.size / 2, player.pos.y + player.size / 2,
			0, 0, 128, 128,
			player.gh, WHITE);

		for (int i = 0; i < max; i++)
		{
			if (trajectory[i].isActive)
			{
				Novice::DrawBox(trajectory[i].position.x, trajectory[i].position.y, trajectory[i].size, trajectory[i].size, 0.0f, 0xFFFFFF00 + trajectory[i].carentAlpha, kFillModeSolid);
			}
		}

		for (int i = 0; i < eMax; i++)
		{
			if (effect[i].isActive)
			{
				Novice::DrawBox(player.pos.x - player.size / 2 + effect[i].position.x * effect[i].size, player.pos.y - player.size / 2 + effect[i].position.y * effect[i].size, trajectory[i].size, trajectory[i].size, 0.0f, 0xFFFFFF00 + effect[i].carentAlpha, kFillModeSolid);
			}
		}

		Novice::ScreenPrintf(10, 10, "%f", player.pos.x + effect[0].position.x + effect[0].size);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
