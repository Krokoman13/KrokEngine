#include "EventHandeler.hpp"
//#include "../../Core/Math/Vec2.hpp"

EventHandeler::EventHandeler(sf::RenderWindow& renderWindow)
{
	_renderWindow = &renderWindow;
}

void EventHandeler::HandleEvent(sf::Event& event)
{
	if (!Input::focus)
	{
		if (event.type == sf::Event::GainedFocus)
		{
			Input::focus = true;
			Input::mouseInScreen = true;
			return;
		}

		return;
	}

	switch (event.type)
	{
	case sf::Event::Closed:
		_renderWindow->close();
		break;

	case sf::Event::LostFocus:
		Input::focus = false;
		break;

	case sf::Event::MouseLeft:
		Input::mouseInScreen = false;
		break;

	case sf::Event::MouseEntered:
		Input::mouseInScreen = true;
		break;

	case sf::Event::MouseMoved:
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*_renderWindow);
			Input::mousePosition.Set((float)mousePosition.x, (float)mousePosition.y);
			//setHovering(ui->GetHoverables());
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (Input::mouseInScreen)
		{
			Input::mouseButtons[event.mouseButton.button] = true;
			Input::mouseButtonsDown[event.mouseButton.button] = true;
			//HandleClicks(event.mouseButton.button);
		}
		break;

	case sf::Event::MouseButtonReleased:
		if (Input::mouseInScreen)
		{
			Input::mouseButtons[event.mouseButton.button] = false;
			Input::mouseButtonsUp[event.mouseButton.button] = true;
		}
		break;

	case sf::Event::KeyPressed:
		Input::key[event.key.code] = true;
		Input::keyDown[event.key.code] = true;
		break;

	case sf::Event::KeyReleased:
		Input::key[event.key.code] = false;
		Input::keyUp[event.key.code] = true;
		break;

	default:
		return;
	}
}

void EventHandeler::ClearButtons()
{
	for (unsigned int i = 0; i < sf::Keyboard::Key::KeyCount ; i++)
	{
		Input::keyDown[i] = false;
		Input::keyUp[i] = false;
	}

	for (unsigned int i = 0; i < sf::Mouse::Button::ButtonCount; i++)
	{
		Input::mouseButtonsDown[i] = false;
		Input::mouseButtonsUp[i] = false;
	}
}

//void EventHandeler::HandleClicks(sf::Mouse::Button button)
//{
//	for (size_t i = _hoveringOver.size(); i != 0; i--)
//	{
//		Clickable* clickable = dynamic_cast<Clickable*>(_hoveringOver[i-1]);
//
//		if (clickable)
//		{
//			if (clickable->onClickButton == button)
//			{
//				clickable->OnClick();
//				return;
//			}
//		}
//	}
//}

//void EventHandeler::setHovering(const std::vector<Hoverable*>& hoverables)
//{
//	while (_hoveringOver.size() > 0)
//	{
//		Hoverable* oldHoverable = _hoveringOver[_hoveringOver.size() - 1];
//
//		if (oldHoverable != nullptr)
//		{
//			oldHoverable->hovering = false;
//		}
//
//		_hoveringOver.pop_back();
//	}
//
//	for (Hoverable* hoverable : hoverables)
//	{
//		if (hoverable == nullptr) continue;
//
//		if (hoverable->IsInside(Input::mousePosition.x, Input::mousePosition.y))
//		{
//			hoverable->hovering = true;
//			_hoveringOver.push_back(hoverable);
//		}
//	}
//}
