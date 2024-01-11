#include <iostream>
#include "Canvas.h"
#include <sys/resource.h>
int main() {

    const rlim_t kStackSize = 64L * 1024L * 1024L;   // min stack size = 64 Mb
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }

    Canvas canvas(400, 40);
    sf::RenderWindow window(sf::VideoMode(canvas.getDiameter(), canvas.getDiameter()), "Drawing",  sf::Style::Close);
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);
    sf::Event event;
    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }
        window.clear();
        canvas.draw(window);
//        canvas.drawBestLine();
        window.display();
    }

    return 0;
}
