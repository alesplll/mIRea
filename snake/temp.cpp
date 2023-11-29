#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <random>

using namespace std;
using namespace sf;

int main()
{
    /// Initialize the game
    init_game();

    /// Create SFML window
    RenderWindow window(VideoMode(window_width, window_height), "Snake", Style::Close);

    /// Main game loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            /// Handle window closure event
            if (event.type == Event::Closed)
                window.close();

            /// Handle key presses
            if (event.type == Event::KeyPressed)
            {
                if (current_menu == MENU_MAIN)
                {
                    /// Это когда мы в меню
                    switch (event.key.code)
                    {
                    case Keyboard::Up:

                        break;
                    case Keyboard::Down:

                        break;
                    case Keyboard::Enter:

                        break;
                    case Keyboard::Escape:

                        break;
                    }
                }
                else
                {
                    game_over_timeout = 0;
                }
            }
            else
            {
                /// а это уже играем
                switch (event.key.code)
                {
                case Keyboard::Up:

                    break;
                case Keyboard::Right:

                    break;
                case Keyboard::Down:

                    break;
                case Keyboard::Left:

                    break;
                case Keyboard::Escape:

                    break;
                }
            }
        }
    }
}
