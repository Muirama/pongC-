#include "input.hpp"

// constructeur
Input::Input()
{
	button.down = button.escape = button.left = button.right = button.up = false;
}

Input::Button Input::GetButton(void) const
{
	return button;
}

void Input::InputHandler(Event event, RenderWindow& window)
{
	if (event.type == Event::Closed)
	{
		window.close();
	}

	if (event.type == Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case Keyboard::Escape:
			button.escape = true;
			break;
		case Keyboard::Up:
			button.up = true;
			break;
		case Keyboard::Down:
			button.down = true;
			break;
		case Keyboard::Left:
			button.left = true;
			break;
		case Keyboard::Right:
			button.right = true;
			break;
		default:
			break;
		}
		
	}

	if (event.type == Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case Keyboard::Escape:
			button.escape = false;
			break;
		case Keyboard::Up:
			button.up = false;
			break;
		case Keyboard::Down:
			button.down = false;
			break;
		case Keyboard::Left:
			button.left = false;
			break;
		case Keyboard::Right:
			button.right = false;
			break;
		default:
			break;
		}

	}
}
