#include <memory>  // for allocator, shared_ptr, __shared_ptr_access
#include <string>  // for char_traits, operator+, to_string
#include <iostream>

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Slider, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for separator, operator|, Element, size, text, vbox, xflex, bgcolor, hbox, GREATER_THAN, WIDTH, border, HEIGHT, LESS_THAN
#include "ftxui/screen/color.hpp"  // for Color

using namespace ftxui;

class MyScreen {
public:
    MyScreen() {
        std::vector<std::string> tab_values{
                "Game",
                "Friends",
                "Settings",
        };
        int tab_selected = 0;
        auto tab_toggle = Toggle(&tab_values, &tab_selected);

        std::string message;
        Component inputChatMessage = Input(&message, "Aa");
        auto component = Container::Vertical({inputChatMessage}); // need this to interact with the input

//        auto buttons = Container::Horizontal({Button(".", [&] { value--; }, &button_option)});

        auto board = Renderer([] { return text("Board") | center; });
        auto chat = Renderer(component, [&inputChatMessage] {
            return vbox({
                                text("Boris: My favorite book is Mein Kampf"),
                                text("Francesco: I love the book too !"),
                                text("Louis: Eyo wtf"),
                                separator(),
                                hbox(text("> "), inputChatMessage->Render()),
                        });
        });
        auto friends = Renderer([] { return text("Friends") | center; });
        auto settings = Renderer([] { return text("Settings") | center; });

        int right_size = 40;

        auto resize_container = board;
        resize_container = ResizableSplitRight(chat, resize_container, &right_size);

        auto tab_container = Container::Tab(
                {
                        resize_container,
                        friends,
                        settings,
                },
                &tab_selected);


        auto container = Container::Vertical({
                                                     tab_toggle,
                                                     tab_container,
                                             });

        auto renderer = Renderer(container, [&] {
            return vbox({
                                tab_toggle->Render(),
                                separator(),
                                tab_container->Render(),
                        }) |
                   border;
        });

        auto screen = ScreenInteractive::TerminalOutput();
        screen.Loop(renderer);
    }
};


int main(int argc, const char *argv[]) {
    system("clear");
    MyScreen screen;
}

