#include "Entity.h"

Entity::Entity(Image &image, float X, float Y, int W, int H, std::string Name)
{
	x = X; y = Y; //���������� ��������� �������
	w = W; h = H;
	name = Name;
	moveTimer = 0;
	dx = 0; dy = 0;
	speed = 0;
	CurrentFrame = 0;
	fishFood = 1;
	life = true; //���������������� ���������� ���������� �����, ����� ���
	texture.loadFromImage(image); //������� ���� ����������� � ��������
	sprite.setTexture(texture); //�������� ������ ���������
}

void Entity::switchImage(Image &image) 
{
	texture.loadFromImage(image); //������� ���� ����������� � ��������
	sprite.setTexture(texture); //�������� ������ ���������
}