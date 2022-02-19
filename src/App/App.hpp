#pragma once

#include <list>
#include "Input/InputHandler.hpp"
#include "Input/KeyEvent.hpp"
#include "State/State.hpp"
#include "System/System.hpp"

namespace Iris
{
    class App :
            public InputHandler<KeyEvent>
    {
    public:
        App(App const&) = delete;
        void operator=(App const&) = delete;

        static App& GetInstance();

        void Run(const std::list<std::unique_ptr<State>>&) const;

        void RegisterUpdateSystem(const std::shared_ptr<System>&);
        void RegisterPreRenderSystem(const std::shared_ptr<System>&);
        void RegisterRenderSystem(const std::shared_ptr<System>&);
        void RegisterPostRenderSystem(const std::shared_ptr<System>&);

        void Handle(KeyEvent) override;

    private:
        App() = default;

        bool m_debug = false;
        bool m_shouldExit = false;

        std::list<std::shared_ptr<System>> m_updateSystems;
        std::list<std::shared_ptr<System>> m_preRenderSystems;
        std::list<std::shared_ptr<System>> m_renderSystems;
        std::list<std::shared_ptr<System>> m_postRenderSystems;
    };
}