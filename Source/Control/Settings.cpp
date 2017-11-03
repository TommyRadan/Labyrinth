#include <Control/Settings.hpp>

Settings::Settings()
{
    m_WindowWidth = 800;
    m_WindowHeight = 600;
    m_WindowType = WinType::WIN_TYPE_WINDOWED;

    m_WindowName = "Labyrinth";
    m_IsDoubleBuffered = true;
    m_FieldOfView = 70.0f;
    m_MouseSensitivity = 0.005f;
    m_IsMouseReversed = true;
}

Settings* const Settings::GetInstance()
{
    static Settings* instance = nullptr;

    if(instance == nullptr)
    {
        instance = new Settings();
    }

    return instance;
}

const unsigned int Settings::GetWindowWidth() const noexcept
{
    return m_WindowWidth;
}

const unsigned int Settings::GetWindowHeight() const noexcept
{
    return m_WindowHeight;
}

const char* Settings::GetWindowName() const noexcept
{
    return m_WindowName.c_str();
}

const WinType Settings::GetWindowType() const noexcept
{
    return m_WindowType;
}

const bool Settings::IsDoubleBuffered() const noexcept
{
    return m_IsDoubleBuffered;
}

const float Settings::GetFieldOfView() const noexcept
{
    return m_FieldOfView;
}

const float Settings::GetMouseSensitivity() const noexcept
{
    return m_MouseSensitivity;
}

const float Settings::GetAspectRatio() const noexcept
{
    return float(m_WindowWidth) / m_WindowHeight;
}

const bool Settings::IsMouseReversed() const noexcept
{
    return m_IsMouseReversed;
}
