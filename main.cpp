#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode({640, 640}), "Textra Errestrial", Style::Titlebar | Style::Close);
    window.setFramerateLimit(144);
    
    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event -> is<Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}