#include "openglcontext.h"

OpenglContext::OpenglContext() : m_maxFps(999999), m_fullscreen(false), m_title(""), m_haveFocus(true)
{
}

OpenglContext::~OpenglContext()
{
}
int OpenglContext::GetFps() const
{
	return 1 / m_app.GetFrameTime();
}

bool OpenglContext::Start(const std::string& title, int width, int height, bool fullscreen)
{
    m_title = title;
    m_fullscreen = fullscreen;
    InitWindow(width, height);

    Init();
    LoadResource();

    while (m_app.IsOpened())
    {
        sf::Event Event;
        while (m_app.GetEvent(Event))
        {
            switch(Event.Type)
            {
            case sf::Event::Closed:
                m_app.Close();
                break;
            case sf::Event::Resized:
                glViewport(0, 0, Event.Size.Width, Event.Size.Height);
				Resized();
                break;
			case sf::Event::KeyPressed:
                KeyPressEvent(Event.Key.Code);
                break;
            case sf::Event::KeyReleased:
                KeyReleaseEvent(Event.Key.Code);
                break;
            case sf::Event::MouseMoved:
                MouseMoveEvent(Event.MouseMove.X, Event.MouseMove.Y);
                break;
            case sf::Event::MouseButtonPressed:
                MousePressEvent(ConvertMouseButton(Event.MouseButton.Button), Event.MouseButton.X, Event.MouseButton.Y);
                break;
            case sf::Event::MouseButtonReleased:
                MouseReleaseEvent(ConvertMouseButton(Event.MouseButton.Button), Event.MouseButton.X, Event.MouseButton.Y);
                break;
            case sf::Event::MouseWheelMoved:
                if(Event.MouseWheel.Delta > 0)
					MouseWheelEvent(MOUSE_BUTTON_WHEEL_UP, Event.MouseWheel.Delta);
                else
                    MouseWheelEvent(MOUSE_BUTTON_WHEEL_DOWN, Event.MouseWheel.Delta);
                break;
			case sf::Event::GainedFocus:
				m_haveFocus = true;
				FocusChanged();
				break;
			case sf::Event::LostFocus:
				m_haveFocus = false;
				FocusChanged();
				break;
            }
        }

        m_app.SetActive();
        Render(m_app.GetFrameTime());
        m_app.Display();
    }

    UnloadResource();
    DeInit();

    return true;
}

int OpenglContext::GetFps()
{
	return 1 / m_app.GetFrameTime();
}

bool OpenglContext::Stop()
{
    m_app.Close();
    return true;
}

void OpenglContext::CenterMouse()
{
    m_app.SetCursorPosition(Width() / 2, Height() / 2);
}

int OpenglContext::Width() const
{
    return m_app.GetWidth();
}

int OpenglContext::Height() const
{
    return m_app.GetHeight();
}

void OpenglContext::SetMaxFps(int maxFps)
{
    m_maxFps = maxFps;
    m_app.SetFramerateLimit(maxFps);
}

int OpenglContext::GetMaxFps() const
{
    return m_maxFps;
}

void OpenglContext::SetFullscreen(bool fullscreen)
{
    if(m_fullscreen == fullscreen)
        return;

    m_fullscreen = !m_fullscreen;

	sf::VideoMode mode = sf::VideoMode::GetDesktopMode();

    DeInit();
	InitWindow(mode.Width, mode.Height);
    Init();

	Resized();
}

bool OpenglContext::IsFullscreen() const
{
    return m_fullscreen;
}

void OpenglContext::MakeRelativeToCenter(int& x, int& y) const
{
    x = x - (Width() / 2);
    y = y - (Height() / 2);
}

void OpenglContext::ShowCursor()
{
    m_app.ShowMouseCursor(true);
}

void OpenglContext::HideCursor()
{
    m_app.ShowMouseCursor(false);
}

void OpenglContext::ShowCrossCursor() const
{
}

void OpenglContext::InitWindow(int width, int height)
{
    m_app.Create(sf::VideoMode(width, height, 32), m_title.c_str(), m_fullscreen ? sf::Style::Fullscreen : (sf::Style::Resize|sf::Style::Close), sf::WindowSettings(32, 8, 0));
}

OpenglContext::MOUSE_BUTTON OpenglContext::ConvertMouseButton(sf::Mouse::Button button) const
{
    switch(button)
    {
    case sf::Mouse::Left:
        return MOUSE_BUTTON_LEFT;
    case sf::Mouse::Middle:
        return MOUSE_BUTTON_MIDDLE;
    case sf::Mouse::Right:
        return MOUSE_BUTTON_RIGHT;
    default:
        return MOUSE_BUTTON_NONE;
    }
}

