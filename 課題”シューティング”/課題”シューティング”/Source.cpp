#include <string>
#include "XLibrary11.hpp"
using namespace XLibrary11;

enum Mode
{
	Title,
	Game,
};

// ランダムな座標を取得する
Float3 GetRandomPosition()
{
	return Float3(
		App::GetWindowSize().x / 2 + rand() / (float)RAND_MAX * 100,
		rand() / (float)RAND_MAX * App::GetWindowSize().y - App::GetWindowSize().y / 2,
		0.0
	);
}

// 当たり判定
bool IsHit(
	Float3 position1,
	Float3 position2,
	float range
)
{
	if (position1.x - range < position2.x &&
		position1.x + range > position2.x &&
		position1.y - range < position2.y &&
		position1.y + range > position2.y)
	{
		// 当たった
		return true;
	}
	// 当たってない
	return false;
}

int MAIN()
{
	Mode mode = Title; // 最初の画面にする

	Camera camera;
	camera.color = Float4(0.0, 0.0, 0.0, 1.0);

	float playerSpeed = 5.0;//自機の速さ

	Sprite player(L"player.png");//自機の画像
	player.scale = 2.0;

	const int enemyNum = 3.0; //敵の数
	float enemySpeed = 5.0; //敵の速さ

	Sprite enemy(L"enemy2.png"); //敵の画像
	enemy.scale = 2.0;

	Float3 enemyPosition[enemyNum]; //敵の座標

	const int enemy2Num = 1.0; //敵の数
	float enemy2Speed = 10.0; //敵の速さ

	Sprite enemy2(L"enemy.png"); //敵の画像
	enemy2.scale = 2.0;

	Float3 enemy2Position[enemy2Num]; //敵の座標

	const int bulletNum = 15;// 弾の数
	const float bulletSpeed = 10.0;// 弾の速さ
	int bulletIndex = 0;// 次に発射する弾の番号
	// 次に発射するまでのカウント
	int bulletInterval = 0;

	Sprite bullet(L"bullet.png");// 弾の画像
	bullet.scale = 2.0;

	Float3 bulletPosition[bulletNum];// 弾の座標
	float bulletRadian[bulletNum];// 弾の角度

	const int misairuNum = 15;// ミサイルの数
	const float misairuSpeed = 10.0;// ミサイルの速さ
	const float gravitySpeed = 0.5;// ミサイルの落ちるスピード
	int misairuIndex = 0;// 次に発射するミサイルの番号
	// 次に発射するまでのカウント
	int misairuInterval = 0;

	Sprite misairu(L"misairu.png");// ミサイルの画像
	misairu.scale = 2.0;

	Float3 misairuPosition[misairuNum];// ミサイルの座標
	float misairuRadian[misairuNum];// ミサイルの角度
	float misairugravity[misairuNum];// ミサイルの重力

	const int bullet2Num = 45.0;// 敵の弾の数
	float bullet2Speed = 10.0;//敵の弾の速さ
	int bullet2Index = 0;// 敵の次に発射する弾の番号
	// 敵の次に発射するまでのカウント
	int bullet2Interval = 10.0;

	Sprite bullet2(L"bullet2.png");// 敵の弾の画像
	bullet2.scale = 2.0;

	Float3 bullet2Position[bullet2Num];// 敵の弾の座標
	float bullet2Radian[bullet2Num];// 敵の弾の角度

	const int bullet3Num = 100.0;// 敵の弾の数
	float bullet3Speed = 5.0;//敵の弾の速さ
	int bullet3Index = 0;// 敵の次に発射する弾の番号
	// 敵の次に発射するまでのカウント
	int bullet3Interval = 10.0;

	Sprite bullet3(L"bullet3.png");// 敵の弾の画像
	bullet3.scale = 2.0;

	Float3 bullet3Position[bullet3Num];// 敵の弾の座標
	float bullet3Radian[bullet3Num];// 敵の弾の角度*/

	Text titleText(L"シューティング", 32.0);
	titleText.scale = 2.0;
	titleText.color = Float4(0.0, 1.0, 1.0, 1.0);

	int score = 0;// スコア

	Text scoreText(L"0", 10.0);
	scoreText.scale = 10.0;
	scoreText.color = Float4(0.0, 1.0, 1.0, 1.0);

	Text lifeText(L"★", 10);
	lifeText.scale = 5.0;
	lifeText.color = Float4(0.0, 1.0, 1.0, 1.0);

	int zanki = 3;// 残機の数

	Text zankiText(L"3", 11.5);
	zankiText.scale = 5.0;
	zankiText.color = Float4(0.0, 1.0, 1.0, 1.0);

	Sound BGMSound(L"BGM.wav");

	while (App::Refresh())
	{

		camera.Update();

		switch (mode)
		{
		case Title:

			if (App::GetKeyDown(VK_RETURN))
			{
				player.position = 0.0;
				enemySpeed = 5.0;
				enemy2Speed = 5.0;
				score = 0;
				scoreText.Create(L"0", 10.0);
				zanki = 3;
				zankiText.Create(L"3", 11.5);
				BGMSound.Play();

				// 敵座標の初期化
				for (int i = 0; i < enemyNum; i++)
				{
					enemyPosition[i] = GetRandomPosition();
				}

				// 弾の座標の初期化
				for (int i = 0; i < bulletNum; i++)
				{
					//はるか彼方に飛ばす
					bulletPosition[i].x = 9999.0;
					bulletRadian[i] = 0.0;
				}

				// ミサイルの座標の初期化
				for (int i = 0; i < misairuNum; i++)
				{
					//はるか彼方に飛ばす
					misairuPosition[i].x = 9999.0;
					misairuRadian[i] = 0.0;
				}

				// 敵の弾の座標の初期化
				for (int i = 0; i < bullet2Num; i++)
				{
					//はるか彼方に飛ばす
					bullet2Position[i].x = 9999.0;
					bullet2Radian[i] = 0.0;
				}

				// 敵の弾の座標の初期化
				for (int i = 0; i < bullet3Num; i++)
				{
					//はるか彼方に飛ばす
					bullet3Position[i].x = 9999.0;
					bullet3Radian[i] = 0.0;
				}
				mode = Game;
			}

			camera.position = 0.0;

			titleText.Draw();
			lifeText.Draw();
			zankiText.Draw();

			scoreText.position = Float3(
				0.0, 200.0, 0.0
			);
			scoreText.Draw();

			lifeText.position = Float3(
				-290.0, 200.0, 0.0
			);
			lifeText.Draw();

			zankiText.position = Float3(
				-245.0, 200.0, 0.0
			);
			zankiText.Draw();

			break;

		case Game:

			// 自機の移動の処理
			if (App::GetKey('D'))
				player.position.x += playerSpeed;

			if (App::GetKey('A'))
				player.position.x -= playerSpeed;

			if (App::GetKey('W'))
				player.position.y += playerSpeed;

			if (App::GetKey('S'))
				player.position.y -= playerSpeed;

			if (player.position.x > App::GetWindowSize().x / 2 + 5)
				player.position.x = App::GetWindowSize().x / 2 + 5;

			if (player.position.x < -App::GetWindowSize().x / 2 - 5)
				player.position.x = -App::GetWindowSize().x / 2 - 5;

			if (player.position.y > App::GetWindowSize().y / 2 + 5)
				player.position.y = App::GetWindowSize().y / 2 + 5;

			if (player.position.y < -App::GetWindowSize().y / 2 - 5)
				player.position.y = -App::GetWindowSize().y / 2 - 5;

			player.Draw();// 自機を描画

			//弾を発射する処理
			bulletInterval++;
			if (App::GetKey('J'))
			{
				if (bulletInterval > 10)
				{
					bulletInterval = 0;
					// 弾を敵機に合わせる
					bulletPosition[bulletIndex] =
						player.position;
					bulletRadian[bulletIndex] =
						0.0;

					bulletIndex++;
					if (bulletIndex >= bulletNum)
						bulletIndex = 0;
				}
			}

			//ミサイルを発射する処理
			misairuInterval++;
			if (App::GetKey('K'))
			{
				if (misairuInterval > 10)
				{
					misairuInterval = 0;
					// ミサイルを敵機に合わせる
					misairuPosition[misairuIndex] =
						player.position;
					misairuRadian[misairuIndex] =
						-0.2;
					misairugravity[misairuIndex] =
						0.0;

					misairuIndex++;
					if (misairuIndex >= misairuNum)
						misairuIndex = 0;
				}
			}

			for (int i = 0; i < enemyNum; i++)
			{
				// 敵を動かす処理
				if (enemyPosition[i].x < -App::GetWindowSize().x)
				{
					enemyPosition[i] = GetRandomPosition();
				}
				enemyPosition[i] += Float3(
					-enemySpeed,
					0.0,
					0.0
				);
				enemy.position = enemyPosition[i];

				float hitRange =
					enemy.GetSize().x / 2.0 *
					enemy.scale.x;
				for (int j = 0; j < bulletNum; j++)
				{
					if (IsHit(
						enemyPosition[i],
						bulletPosition[j],
						hitRange
					))
					{
						enemyPosition[i] =
							camera.position +
							GetRandomPosition();
						score += 1;
						if (score % 30 == 0)
						{
							enemySpeed += 1.5;
							bullet2Speed += 1.5;
						}
						scoreText.Create(
							std::to_wstring(score),
							10.0
						);
					}

					
				}

				for (int u = 0; u < misairuNum; u++)
				{
					if (IsHit(
						enemyPosition[i],
						misairuPosition[u],
						hitRange
					))
					{
						enemyPosition[i] =
							camera.position +
							GetRandomPosition();
						score += 1;
						if (score % 30 == 0)
						{
							enemySpeed += 1.5;
							bullet2Speed += 1.5;
						}
						scoreText.Create(
							std::to_wstring(score),
							10.0
						);
					}
				}

				//弾を発射する処理
				bullet2Interval++;
				if (bullet2Interval > 10)
				{
					bullet2Interval = 0;
					// 弾を敵機に合わせる
					bullet2Position[bullet2Index] =
						enemy.position;
					bullet2Radian[bullet2Index] =
						0.0;

					bullet2Index++;
					if (bullet2Index >= bullet2Num)
						bullet2Index = 0;
				}

				enemy.Draw();
			}
			for (int i = 0; i < enemy2Num; i++)
			{
				// 敵2を動かす処理
				if (enemy2Position[i].x < 255)
				{
					enemy2Position[i].x = 255;
					if (App::GetKey('S'))
						enemy2Position[i].y += enemy2Speed;
					if (App::GetKey('W'))
						enemy2Position[i].y -= enemy2Speed;
					if (App::GetKey('A'))
						enemy2Position[i].y += enemy2Speed;
					if (App::GetKey('D'))
						enemy2Position[i].y -= enemy2Speed;

					if (enemy2Position[i].y > App::GetWindowSize().y / 2 + 5)
						enemy2Position[i].y = App::GetWindowSize().y / 2 + 5;
					if (enemy2Position[i].y < -App::GetWindowSize().y / 2 - 5)
						enemy2Position[i].y = -App::GetWindowSize().y / 2 - 5;
				}
				enemy2Position[i] += Float3(
					-enemy2Speed,
					0.0,
					0.0
				);
				enemy2.position = enemy2Position[i];
				enemy2.Draw();// 敵を描画
			}

			bullet3Interval++;
			if (App::GetKey('J'))
			{
				if (bullet3Interval > 10)
				{
					bullet3Interval = 0;
					// 弾を敵機に合わせる
					bullet3Position[bullet3Index] =
						enemy2.position;
					bullet3Radian[bullet3Index] =
						0.0;

					bullet3Index++;
					if (bullet3Index >= bullet3Num)
						bullet3Index = 0;
				}
			}

			bullet3Interval++;
			if (App::GetKey('K'))
			{
				if (bullet3Interval > 10)
				{
					bullet3Interval = 0;
					// 弾を敵機に合わせる
					bullet3Position[bullet3Index] =
						enemy2.position;
					bullet3Radian[bullet3Index] =
						0.0;

					bullet3Index++;
					if (bullet3Index >= bullet3Num)
						bullet3Index = 0;
				}
			}

			//自機との当たり判定
			for (int i = 0; i < bullet2Num; i++)
			{
				float hitRange =
					bullet2.GetSize().x / 2.0 *
					bullet2.scale.x;
				if (IsHit(
					bullet2Position[i],
					player.position,
					hitRange
				))
				{
					zanki -= 1;
					player.position = 0.0;
					if (zanki == 0)
					{
						mode = Title;
					}
					zankiText.Create(
						std::to_wstring(zanki),
						10.0
					);
				}
			}

			for (int i = 0; i < enemy2Num; i++)
			{
				float hitRange =
					enemy2.GetSize().x / 2.0 *
					enemy2.scale.x;
				if (IsHit(
					enemy2Position[i],
					player.position,
					hitRange
				))
				{
					zanki -= 1;
					player.position = 0.0;
					if (zanki == 0)
					{
						mode = Title;
					}
					zankiText.Create(
						std::to_wstring(zanki),
						10.0
					);
				}
			}

			for (int i = 0; i < bullet3Num; i++)
			{
				float hitRange =
					bullet3.GetSize().x / 2.0 *
					bullet3.scale.x;
				if (IsHit(
					bullet3Position[i],
					player.position,
					hitRange
				))
				{
					zanki -= 1;
					player.position = 0.0;
					if (zanki == 0)
					{
						mode = Title;
					}
					zankiText.Create(
						std::to_wstring(zanki),
						10.0
					);
				}
			}

			for (int i = 0; i < bulletNum; i++)
			{
				bulletPosition[i] += Float3(
					cosf(bulletRadian[i]),
					sinf(bulletRadian[i]),
					0.0
				) * bulletSpeed;
				bullet.position = bulletPosition[i];
				bullet.Draw();// 弾の描画
			}

			for (int i = 0; i < misairuNum; i++)
			{
				misairuPosition[i] += Float3(
					cosf(misairuRadian[i]),
					sinf(misairuRadian[i]),
					0.0
				) * misairuSpeed;
				// 重力の処理
				misairugravity[i] -= gravitySpeed;
				misairuPosition[i].y += misairugravity[i];
				misairu.position = misairuPosition[i];

				misairu.Draw();// ミサイルの描画
			}

			for (int i = 0; i < bullet2Num; i++)
			{
				bullet2Position[i] -= Float3(
					cosf(bullet2Radian[i]),
					sinf(bullet2Radian[i]),
					0.0
				) * bullet2Speed;
				bullet2.position = bullet2Position[i];

				bullet2.Draw();// 弾の描画
			}

			for (int i = 0; i < bullet3Num; i++)
			{
				bullet3Position[i] -= Float3(
					cosf(bullet3Radian[i]),
					sinf(bullet3Radian[i]),
					0.0
				) * bullet3Speed;
				bullet3.position = bullet3Position[i];

				bullet3.Draw();// 弾の描画
			}

			scoreText.position = camera.position +
				Float3(0.0, 200.0, 0.0);
			scoreText.Draw();

			lifeText.position = camera.position +
				Float3(-290.0, 200.0, 0.0);
			lifeText.Draw();

			zankiText.position = camera.position +
				Float3(-245.0, 200.0, 0.0);
			zankiText.Draw();
		}
	}
	return 0;
}