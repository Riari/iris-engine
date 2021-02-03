#pragma once

namespace Iris
{
    class Window;

    class Controller
    {
    public:
        explicit Controller(int id);

        [[nodiscard]] int GetID() const;

        virtual void Update(Window&) = 0;

    private:
        int m_id;
    };
}