#include "Player.h"

Player::Player(Image &image, float X, float Y, int W, int H, std::string Name) :Entity(image, X, Y, W, H, Name)
{
	state = stay;
	if (name == "Player1") 
	{
		//������� ������� ���� ������������� ���
		//������ ������ ������. IntRect ��� ���������� �����
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}
}

void Player::control()
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		state = left;
		speed = 0.1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		state = right;
		speed = 0.1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		state = up;
		speed = 0.1;
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		state = down;
		speed = 0.1;
	}
}

void Player::checkCollisionWithMap(GameMap &gameMap, float Dx, float Dy) //����� �������� ������������ � ���������� �����
{
	for (int i = y / 32; i < (y + h) / 32; i++) //���������� �� ��������� �����
		for (int j = x / 32; j < (x + w) / 32; j++)
		{
			if (gameMap.TileMap[i][j] == '0') //���� ������� ������ �����
			{
				if (Dy > 0) { y = i * 32 - h;  dy = 0; } //�� Y 
				if (Dy < 0) { y = i * 32 + 32; dy = 0; } //������������ � �������� ������ 
				if (Dx > 0) { x = j * 32 - w; dx = 0; } //� ������ ����� �����
				if (Dx < 0) { x = j * 32 + 32; dx = 0; } //� ����� ����� �����
			}
			if (gameMap.TileMap[i][j] == 'f') {
				fishFood += 1;  //���� ���
				gameMap.TileMap[i][j] = ' '; //������ ��� �� ������
			}
		}
}


void Player::update(GameMap &gameMap, float time) //����� "���������/����������" ������� ������.
{
	if (life) { //���������, ��� �� �����
		control(); //������� ���������� ����������
		switch (state) //�������� ��������� �������� � ����������� �� ���������
		{
			case right: { //��������� ���� ������
				dx = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
				break;
			}
			case left: { //��������� ���� �����
				dx = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
				break;
			}
			case up: { //���� �����
				dy = -speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
				break;
			}
			case down: { //���� ����
				dy = speed;
				CurrentFrame += 0.005*time;
				if (CurrentFrame > 3) CurrentFrame -= 3;
				sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
				break;
			}
			case stay: { //�����
				dy = speed;
				dx = speed;
				break;
			}
		}

		x += dx*time; //�������� �� "X"
		checkCollisionWithMap(gameMap, dx, 0); //������������ ������������ �� X
		y += dy*time; //�������� �� "Y"
		checkCollisionWithMap(gameMap, 0, dy); //������������ ������������ �� Y

		speed = 0; //�������� ��������, ����� �������� �����������

		sprite.setPosition(x, y); //������ � ������� (x, y).

		if (fishFood <= 0) { life = false; } //���� ��� ������ 0, ���� ����� 0, �� ������� 
	}
};