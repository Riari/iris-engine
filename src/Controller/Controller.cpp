#include "Controller/Controller.hpp"

using namespace Iris;

Controller::Controller(int id) : m_id(id) {}

int Controller::GetID() const
{
    return m_id;
}
