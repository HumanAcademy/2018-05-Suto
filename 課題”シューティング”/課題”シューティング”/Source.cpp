#include <string>
#include "XLibrary11.hpp"
using namespace XLibrary11;

enum Mode
{
	Title,
	Game,
};

// �����_���ȍ��W���擾����
Float3 GetRandomPosition()
{
	return Float3(
		App::GetWindowSize().x / 2 + rand() / (float)RAND_MAX * 100,
		rand() / (float)RAND_MAX * App::GetWindowSize().y - App::GetWindowSize().y / 2,
		0.0
	);
}

// �����蔻��
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
		// ��������
		return true;
	}
	// �������ĂȂ�
	return false;
}

int MAIN()
{
	Mode mode = Title; // �ŏ��̉�ʂɂ���

	Camera camera;
	camera.color = Float4(0.0, 0.0, 0.0, 1.0);

	float playerSpeed = 5.0;//���@�̑���

	Sprite player(L"player.png");//���@�̉摜
	player.scale = 2.0;

	const int enemyNum = 3.0; //�G�̐�
	float enemySpeed = 5.0; //�G�̑���

	Sprite enemy(L"enemy2.png"); //�G�̉摜
	enemy.scale = 2.0;

	Float3 enemyPosition[enemyNum]; //�G�̍��W

	const int enemy2Num = 1.0; //�G�̐�
	float enemy2Speed = 10.0; //�G�̑���

	Sprite enemy2(L"enemy.png"); //�G�̉摜
	enemy2.scale = 2.0;

	Float3 enemy2Position[enemy2Num]; //�G�̍��W

	const int bulletNum = 15;// �e�̐�
	const float bulletSpeed = 10.0;// �e�̑���
	int bulletIndex = 0;// ���ɔ��˂���e�̔ԍ�
	// ���ɔ��˂���܂ł̃J�E���g
	int bulletInterval = 0;

	Sprite bullet(L"bullet.png");// �e�̉摜
	bullet.scale = 2.0;

	Float3 bulletPosition[bulletNum];// �e�̍��W
	float bulletRadian[bulletNum];// �e�̊p�x

	const int misairuNum = 15;// �~�T�C���̐�
	const float misairuSpeed = 10.0;// �~�T�C���̑���
	const float gravitySpeed = 0.5;// �~�T�C���̗�����X�s�[�h
	int misairuIndex = 0;// ���ɔ��˂���~�T�C���̔ԍ�
	// ���ɔ��˂���܂ł̃J�E���g
	int misairuInterval = 0;

	Sprite misairu(L"misairu.png");// �~�T�C���̉摜
	misairu.scale = 2.0;

	Float3 misairuPosition[misairuNum];// �~�T�C���̍��W
	float misairuRadian[misairuNum];// �~�T�C���̊p�x
	float misairugravity[misairuNum];// �~�T�C���̏d��

	const int bullet2Num = 45.0;// �G�̒e�̐�
	float bullet2Speed = 10.0;//�G�̒e�̑���
	int bullet2Index = 0;// �G�̎��ɔ��˂���e�̔ԍ�
	// �G�̎��ɔ��˂���܂ł̃J�E���g
	int bullet2Interval = 10.0;

	Sprite bullet2(L"bullet2.png");// �G�̒e�̉摜
	bullet2.scale = 2.0;

	Float3 bullet2Position[bullet2Num];// �G�̒e�̍��W
	float bullet2Radian[bullet2Num];// �G�̒e�̊p�x

	const int bullet3Num = 100.0;// �G�̒e�̐�
	float bullet3Speed = 5.0;//�G�̒e�̑���
	int bullet3Index = 0;// �G�̎��ɔ��˂���e�̔ԍ�
	// �G�̎��ɔ��˂���܂ł̃J�E���g
	int bullet3Interval = 10.0;

	Sprite bullet3(L"bullet3.png");// �G�̒e�̉摜
	bullet3.scale = 2.0;

	Float3 bullet3Position[bullet3Num];// �G�̒e�̍��W
	float bullet3Radian[bullet3Num];// �G�̒e�̊p�x*/

	Text titleText(L"�V���[�e�B���O", 32.0);
	titleText.scale = 2.0;
	titleText.color = Float4(0.0, 1.0, 1.0, 1.0);

	int score = 0;// �X�R�A

	Text scoreText(L"0", 10.0);
	scoreText.scale = 10.0;
	scoreText.color = Float4(0.0, 1.0, 1.0, 1.0);

	Text lifeText(L"��", 10);
	lifeText.scale = 5.0;
	lifeText.color = Float4(0.0, 1.0, 1.0, 1.0);

	int zanki = 3;// �c�@�̐�

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

				// �G���W�̏�����
				for (int i = 0; i < enemyNum; i++)
				{
					enemyPosition[i] = GetRandomPosition();
				}

				// �e�̍��W�̏�����
				for (int i = 0; i < bulletNum; i++)
				{
					//�͂邩�ޕ��ɔ�΂�
					bulletPosition[i].x = 9999.0;
					bulletRadian[i] = 0.0;
				}

				// �~�T�C���̍��W�̏�����
				for (int i = 0; i < misairuNum; i++)
				{
					//�͂邩�ޕ��ɔ�΂�
					misairuPosition[i].x = 9999.0;
					misairuRadian[i] = 0.0;
				}

				// �G�̒e�̍��W�̏�����
				for (int i = 0; i < bullet2Num; i++)
				{
					//�͂邩�ޕ��ɔ�΂�
					bullet2Position[i].x = 9999.0;
					bullet2Radian[i] = 0.0;
				}

				// �G�̒e�̍��W�̏�����
				for (int i = 0; i < bullet3Num; i++)
				{
					//�͂邩�ޕ��ɔ�΂�
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

			// ���@�̈ړ��̏���
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

			player.Draw();// ���@��`��

			//�e�𔭎˂��鏈��
			bulletInterval++;
			if (App::GetKey('J'))
			{
				if (bulletInterval > 10)
				{
					bulletInterval = 0;
					// �e��G�@�ɍ��킹��
					bulletPosition[bulletIndex] =
						player.position;
					bulletRadian[bulletIndex] =
						0.0;

					bulletIndex++;
					if (bulletIndex >= bulletNum)
						bulletIndex = 0;
				}
			}

			//�~�T�C���𔭎˂��鏈��
			misairuInterval++;
			if (App::GetKey('K'))
			{
				if (misairuInterval > 10)
				{
					misairuInterval = 0;
					// �~�T�C����G�@�ɍ��킹��
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
				// �G�𓮂�������
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

				//�e�𔭎˂��鏈��
				bullet2Interval++;
				if (bullet2Interval > 10)
				{
					bullet2Interval = 0;
					// �e��G�@�ɍ��킹��
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
				// �G2�𓮂�������
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
				enemy2.Draw();// �G��`��
			}

			bullet3Interval++;
			if (App::GetKey('J'))
			{
				if (bullet3Interval > 10)
				{
					bullet3Interval = 0;
					// �e��G�@�ɍ��킹��
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
					// �e��G�@�ɍ��킹��
					bullet3Position[bullet3Index] =
						enemy2.position;
					bullet3Radian[bullet3Index] =
						0.0;

					bullet3Index++;
					if (bullet3Index >= bullet3Num)
						bullet3Index = 0;
				}
			}

			//���@�Ƃ̓����蔻��
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
				bullet.Draw();// �e�̕`��
			}

			for (int i = 0; i < misairuNum; i++)
			{
				misairuPosition[i] += Float3(
					cosf(misairuRadian[i]),
					sinf(misairuRadian[i]),
					0.0
				) * misairuSpeed;
				// �d�͂̏���
				misairugravity[i] -= gravitySpeed;
				misairuPosition[i].y += misairugravity[i];
				misairu.position = misairuPosition[i];

				misairu.Draw();// �~�T�C���̕`��
			}

			for (int i = 0; i < bullet2Num; i++)
			{
				bullet2Position[i] -= Float3(
					cosf(bullet2Radian[i]),
					sinf(bullet2Radian[i]),
					0.0
				) * bullet2Speed;
				bullet2.position = bullet2Position[i];

				bullet2.Draw();// �e�̕`��
			}

			for (int i = 0; i < bullet3Num; i++)
			{
				bullet3Position[i] -= Float3(
					cosf(bullet3Radian[i]),
					sinf(bullet3Radian[i]),
					0.0
				) * bullet3Speed;
				bullet3.position = bullet3Position[i];

				bullet3.Draw();// �e�̕`��
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