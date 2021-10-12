#include "GameObject.h"

const Vector2D& GameObject::GetPosition() const
{
    return m_position;
}

void GameObject::SetPosition(const Vector2D& position)
{
    m_position = position;
}
