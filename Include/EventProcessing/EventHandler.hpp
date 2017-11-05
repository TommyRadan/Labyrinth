#pragma once

#include <functional>
#include <vector>

namespace EventProcessing
{
    enum class KeyCode
    {
        W = 119,
        A = 97,
        S = 115,
        D = 100,
        SPACE = 32,
        SHIFT = 1073742049,
        CTRL = 1073741881,
        ENTER = 13,
        ESCAPE = 27
    };

    class EventHandler
    {
        EventHandler() = default;

    public:
        static EventHandler* GetInstance();

        void HandleEvents();

        void RegisterOnFrameCallback(std::function<void(uint32_t)> callback);
        void RegisterOnKeyDownCallback(std::function<void(KeyCode)> callback);
        void RegisterOnKeyUpCallback(std::function<void(KeyCode)> callback);
        void RegisterKeyPressedCallback(std::function<void(KeyCode, uint32_t)> callback);

        void DispatchOnFrameCallback(uint32_t deltaTime);
        void DispatchOnKeyDownCallback(KeyCode keyCode);
        void DispatchOnKeyUpCallback(KeyCode keyCode);
        void DispatchKeyPressedCallBack(KeyCode keyCode, uint32_t deltaTime);

        bool IsKeyPressed(KeyCode keyCode);

    private:
        void HandleFrame();

        std::vector<std::function<void(uint32_t)>> m_OnFrameCallbacks;
        std::vector<std::function<void(KeyCode)>> m_OnKeyDownCallbacks;
        std::vector<std::function<void(KeyCode)>> m_OnKeyUpCallbacks;
        std::vector<std::function<void(KeyCode, uint32_t)>> m_KeyPressedCallbacks;
        std::vector<KeyCode> m_PressedKeys;
    };
}
