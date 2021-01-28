#include "Player.h"

Player::Player(std::string _textureID, std::string texturePath, Vec2 pos, int remMoves)
{
	textureID = _textureID;
	Renderer::GetInstance()->LoadTexture(_textureID, texturePath);

	Vec2 size = Renderer::GetInstance()->GetTextureSize(_textureID);

	size.x /= 3;
	size.y /= 4;

	position = rect = Rect(0, 0, size);

	position.x = pos.x * SPRITE_RESOLUTION;
	position.y = pos.y * SPRITE_RESOLUTION;

	mapPos = Vec2(std::trunc((position.x + (position.w / 2)) / SPRITE_RESOLUTION), std::trunc((position.y + (position.h / 2)) / SPRITE_RESOLUTION));

	cellsMovedCounter = 0;
	speed = 5.f;
	animationTime = 0.2f;
	remainingMoves = remMoves;
	isAtGoal = false;
}

void Player::Update(Inputs* inputs, Map* map, float dt)
{
	animationTime -= dt;
	switch (dir)
	{
	case Direction::UP:
		dir = Direction::UP_STOP;
		break;
	case Direction::DOWN:
		dir = Direction::DOWN_STOP;
		break;
	case Direction::LEFT:
		dir = Direction::LEFT_STOP;
		break;
	case Direction::RIGHT:
		dir = Direction::RIGHT_STOP;
		break;
	}

	bool tmp = false;
	for (size_t i = 0; i < 4; i++)
	{
		tmp = tmp || direction[i];
	}

	if (!tmp)
	{
		if (*inputs->GetKey(InputKeys::UP))
		{
			direction[(int)InputKeys::UP] = true;
			dir = Direction::UP;
		}
		else if (*inputs->GetKey(InputKeys::DOWN))
		{
			direction[(int)InputKeys::DOWN] = true;
			dir = Direction::DOWN;
		}
		else if (*inputs->GetKey(InputKeys::LEFT))
		{
			direction[(int)InputKeys::LEFT] = true;
			dir = Direction::LEFT;
		}
		else if (*inputs->GetKey(InputKeys::RIGHT))
		{
			direction[(int)InputKeys::RIGHT] = true;
			dir = Direction::RIGHT;
		}
	}

	//Colisions
	if (direction[(int)InputKeys::UP])
	{
		if (cellsMovedCounter == 0 && *map->GetCellFromPos(Vec2(mapPos.x, mapPos.y - 1)) == CellType::WALL)
		{
			direction[(int)InputKeys::UP] = false;
		}
		else
		{
			if (!map->CalculateWallCollisions(mapPos, position, dir))
			{
				position.y -= speed;
				cellsMovedCounter++;
			}
			else
			{
				if (cellsMovedCounter != 0)
					remainingMoves--;
				direction[(int)InputKeys::UP] = false;
				cellsMovedCounter = 0;

				if (textureID == T_PLAYER_1)
				{
					if (*map->GetCellFromPos(mapPos) == CellType::GOAL_P1)
						isAtGoal = true;
				}
				else if (textureID == T_PLAYER_2)
				{
					if (*map->GetCellFromPos(mapPos) == CellType::GOAL_P2)
						isAtGoal = true;
				}
			}
		}
		
		mapPos = Vec2(std::trunc((position.x + (position.w / 2)) / SPRITE_RESOLUTION), std::trunc((position.y + (position.h / 2)) / SPRITE_RESOLUTION));
	}
	else if (direction[(int)InputKeys::DOWN])
	{
		if (cellsMovedCounter == 0 && *map->GetCellFromPos(Vec2(mapPos.x, mapPos.y + 1)) == CellType::WALL)
		{
			direction[(int)InputKeys::DOWN] = false;
		}
		else
		{
			if (!map->CalculateWallCollisions(mapPos, position, dir))
			{
				position.y += speed;
				cellsMovedCounter++;
			}
			else
			{
				if (cellsMovedCounter != 0)
					remainingMoves--;
				direction[(int)InputKeys::DOWN] = false;
				cellsMovedCounter = 0;

				if (textureID == T_PLAYER_1)
				{
					if (*map->GetCellFromPos(mapPos) == CellType::GOAL_P1)
						isAtGoal = true;
				}
				else if (textureID == T_PLAYER_2)
				{
					if (*map->GetCellFromPos(mapPos) == CellType::GOAL_P2)
						isAtGoal = true;
				}
			}
		}
		mapPos = Vec2(std::trunc((position.x + (position.w / 2)) / SPRITE_RESOLUTION), std::trunc((position.y + (position.h / 2)) / SPRITE_RESOLUTION));
	}
	else if (direction[(int)InputKeys::LEFT])
	{
		if (cellsMovedCounter == 0 && *map->GetCellFromPos(Vec2(mapPos.x - 1, mapPos.y)) == CellType::WALL)
		{
			direction[(int)InputKeys::LEFT] = false;
		}
		else
		{
			if (!map->CalculateWallCollisions(mapPos, position, dir))
			{
				position.x -= speed;
				cellsMovedCounter++;
			}
			else
			{
				if (cellsMovedCounter != 0)
					remainingMoves--;
				direction[(int)InputKeys::LEFT] = false;
				cellsMovedCounter = 0;

				if (textureID == T_PLAYER_1)
				{
					if (*map->GetCellFromPos(mapPos) == CellType::GOAL_P1)
						isAtGoal = true;
				}
				else if (textureID == T_PLAYER_2)
				{
					if (*map->GetCellFromPos(mapPos) == CellType::GOAL_P2)
						isAtGoal = true;
				}
			}
		}
		mapPos = Vec2(std::trunc((position.x + (position.w / 2)) / SPRITE_RESOLUTION), std::trunc((position.y + (position.h / 2)) / SPRITE_RESOLUTION));
	}
	else if (direction[(int)InputKeys::RIGHT])
	{
		if (cellsMovedCounter == 0 && *map->GetCellFromPos(Vec2(mapPos.x + 1, mapPos.y)) == CellType::WALL)
		{
			direction[(int)InputKeys::RIGHT] = false;
		}
		else
		{
			if (!map->CalculateWallCollisions(mapPos, position, dir))
			{
				position.x += speed;
				cellsMovedCounter++;
			}
			else
			{
				if (cellsMovedCounter != 0)
					remainingMoves--;
				direction[(int)InputKeys::RIGHT] = false;
				cellsMovedCounter = 0;

				if (textureID == T_PLAYER_1)
				{
					if (*map->GetCellFromPos(mapPos) == CellType::GOAL_P1)
						isAtGoal = true;
				}
				else if (textureID == T_PLAYER_2)
				{
					if (*map->GetCellFromPos(mapPos) == CellType::GOAL_P2)
						isAtGoal = true;
				}
			}
		}
		mapPos = Vec2(std::trunc((position.x + (position.w / 2)) / SPRITE_RESOLUTION), std::trunc((position.y + (position.h / 2)) / SPRITE_RESOLUTION));
	}

	

	
	if (animationTime <= 0)
	{
		switch (dir)
		{
		case Direction::UP:
			rect.x += rect.w;
			rect.y = 0;
			break;
		case Direction::DOWN:
			rect.x += rect.w;
			rect.y = rect.h * 2;
			break;
		case Direction::LEFT:
			rect.x += rect.w;
			rect.y = rect.h;
			break;
		case Direction::RIGHT:
			rect.x += rect.w;
			rect.y = rect.h * 3;
			break;
		case Direction::UP_STOP:
			rect.x = rect.w;
			rect.y = 0;
			break;
		case Direction::DOWN_STOP:
			rect.x = rect.w;
			rect.y = rect.h * 2;
			break;
		case Direction::LEFT_STOP:
			rect.x = 0;
			rect.y = rect.h;
			break;
		case Direction::RIGHT_STOP:
			rect.x = 0;
			rect.y = rect.h * 3;
			break;
		}
		if (rect.x >= rect.w * 3)
			rect.x = 0;

		animationTime = 0.2f;
	}
}

void Player::Draw()
{
	Rect pos = Rect(position.x + (SPRITE_RESOLUTION - position.w) / 2, position.y + 80 + (SPRITE_RESOLUTION - position.h) / 2, position.w, position.h);
	if (textureID == T_PLAYER_1)
	{
		Renderer::GetInstance()->LoadRect(T_PLAYER_1, pos);
		Renderer::GetInstance()->LoadRect(T_PLAYER_1_RECT, rect);

		Renderer::GetInstance()->PushSprite(T_PLAYER_1, T_PLAYER_1_RECT, T_PLAYER_1);
	}
	else if (textureID == T_PLAYER_2)
	{
		Renderer::GetInstance()->LoadRect(T_PLAYER_2, pos);
		Renderer::GetInstance()->LoadRect(T_PLAYER_2_RECT, rect);

		Renderer::GetInstance()->PushSprite(T_PLAYER_2, T_PLAYER_2_RECT, T_PLAYER_2);
	}
}
