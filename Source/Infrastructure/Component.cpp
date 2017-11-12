#include <Infrastructure/Component.hpp>

Component::Component() :
    m_IsInitialized { false }
{}

const bool Component::IsInitialized() const
{
    return m_IsInitialized;
}
