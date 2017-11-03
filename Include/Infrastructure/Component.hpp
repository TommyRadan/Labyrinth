#pragma once

struct Component
{
    Component();

    virtual void Init() = 0;
    virtual void Quit() = 0;

    const bool IsInitialized() const;

protected:
    bool m_IsInitialized;
};
