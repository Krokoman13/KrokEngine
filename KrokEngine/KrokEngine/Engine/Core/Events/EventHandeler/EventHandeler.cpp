#include "EventHandeler.hpp"
//#include "../../Core/Math/Vec2.hpp"

EventHandeler::EventHandeler()
{

}

void EventHandeler::HandleEvent(Event& event)
{
	if (!Input::focus)
	{
		if (event.type == Event::GainedFocus)
		{
			Input::focus = true;
			Input::mouseInScreen = true;
			return;
		}

		return;
	}

	switch (event.type)
	{
	case Event::Closed:
		//_renderWindow->close();
		break;

	case Event::LostFocus:
		Input::focus = false;
		break;

	case Event::MouseLeft:
		Input::mouseInScreen = false;
		break;

	case Event::MouseEntered:
		Input::mouseInScreen = true;
		break;

	case Event::MouseMoved:
		{
			//Vector2i mousePosition = Mouse::getPosition(*_renderWindow);
			//Input::mousePosition.Set((float)mousePosition.x, (float)mousePosition.y);
			//setHovering(ui->GetHoverables());
		}
		break;

	case Event::MouseButtonPressed:
		if (Input::mouseInScreen)
		{
			//Input::mouseButtons[event.mouseButton.button] = true;
			//Input::mouseButtonsDown[event.mouseButton.button] = true;
			//HandleClicks(event.mouseButton.button);
		}
		break;

	case Event::MouseButtonReleased:
		if (Input::mouseInScreen)
		{
			//Input::mouseButtons[event.mouseButton.button] = false;
			//Input::mouseButtonsUp[event.mouseButton.button] = true;
		}
		break;

	case Event::KeyPressed:
		//Input::key[event.key.code] = true;
		//Input::keyDown[event.key.code] = true;
		break;

	case Event::KeyReleased:
		//Input::key[event.key.code] = false;
		//Input::keyUp[event.key.code] = true;
		break;

	default:
		return;
	}
}

void EventHandeler::ClearButtons()
{
	//for (unsigned int i = 0; i < Keyboard::Key::KeyCount ; i++)
	//{
	//	Input::keyDown[i] = false;
	//	Input::keyUp[i] = false;
	//}

	//for (unsigned int i = 0; i < Mouse::Button::ButtonCount; i++)
	//{
	//	Input::mouseButtonsDown[i] = false;
	//	Input::mouseButtonsUp[i] = false;
	//}
}

//void EventHandeler::HandleClicks(Mouse::Button button)
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
