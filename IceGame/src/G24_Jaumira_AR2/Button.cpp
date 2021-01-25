#include "Button.h"

void Button::SetTextData(Vec2 _pos, std::string _fontPath, std::string _text, std::string _fontID, std::string _textID, Color _color)
{
	Vec2 size;
	font = Font(_fontID, _fontPath, 30);
	text = Text(_textID, _text, _color);
	buttonState = _textID;
	size = Renderer::GetInstance()->LoadTextureText(_fontID, text);
	_pos.x -= size.x / 2;
	_pos.y -= size.y / 2;
	rect = Rect(_pos, size);
	Renderer::GetInstance()->LoadRect(_textID, rect);
}

void Button::ChangeState(Vec2 mouse)
{
	// Hovers
	if (Collision(mouse))
	{
		if (text.id == BTTN_LVL_1)
			buttonState = text.id = BTTN_LVL_1_H;
		else if (text.id == BTTN_LVL_2)
			buttonState = text.id = BTTN_LVL_2_H;
		else if (text.id == BTTN_RANKING)
			buttonState = text.id = BTTN_RANKING_H;
		else if (text.id == BTTN_MENU)
			buttonState = text.id = BTTN_MENU_H;
		else if (text.id == BTTN_EXIT)
			buttonState = text.id = BTTN_EXIT_H;
		else if (text.id == BTTN_BACK_R)
			buttonState = text.id = BTTN_BACK_R_H;
	}
	// Normals
	else
	{
		if (text.id == BTTN_LVL_1_H)
			buttonState = text.id = BTTN_LVL_1;
		else if (text.id == BTTN_LVL_2_H)
			buttonState = text.id = BTTN_LVL_2;
		else if (text.id == BTTN_RANKING_H)
			buttonState = text.id = BTTN_RANKING;
		else if (text.id == BTTN_MENU_H)
			buttonState = text.id = BTTN_MENU;
		else if (text.id == BTTN_EXIT_H)
			buttonState = text.id = BTTN_EXIT;
		else if (text.id == BTTN_BACK_R_H)
			buttonState = text.id = BTTN_BACK_R;
	}
}

bool Button::Collision(Vec2 _mouse)
{
	return _mouse.x > rect.x && _mouse.x < rect.x + rect.w && _mouse.y > rect.y && _mouse.y < rect.y + rect.h;
}

void Button::Draw()
{
	Renderer::GetInstance()->PushImage(buttonState, buttonState);
}