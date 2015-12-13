#include <cstring>

#include "renderer_backend.h"

// Colors
Color Color::RED{0xFF, 0x00, 0x00, 0xFF};
Color Color::ORANGE{0xFF, 0xA5, 0x00, 0xFF};
Color Color::YELLOW{0xFF, 0xFF, 0x00, 0xFF};
Color Color::GREEN{0x00, 0xFF, 0x00, 0xFF};
Color Color::BLUE{0x00, 0x00, 0xFF, 0xFF};
Color Color::PURPLE{0x80, 0x00, 0x80, 0xFF};
Color Color::BLACK{0xFF, 0xFF, 0xFF, 0xFF};
Color Color::WHITE{0x00, 0x00, 0x00, 0xFF};


renderer* renderer::backend = nullptr;
const std::string renderer::MAIN_WINDOW_LABEL = "GoldeNES";

renderer::renderer(int width, int height):
    ticks(0),
    main_window(new sf::RenderWindow(sf::VideoMode(width, height), renderer::MAIN_WINDOW_LABEL)) {

    pixels = new Color[width * height];

    canvas.create(width, height);
    screen.setTexture(canvas);
}

renderer::~renderer() {
    delete pixels;
    delete main_window.release();
}

sf::RenderWindow* renderer::getMainWindow() {
    return main_window.get();
}

Color* renderer::getPixels() {
    return pixels;
}

void renderer::setPixel(int x, int y, const Color& color) {
    pixels[x + (y * main_window->getSize().x)] = color;
}

const Color& renderer::getPixel(int x, int y) {
    return pixels[x + (y * main_window->getSize().x)];
}

const int renderer::screenSize() {
    return main_window->getSize().x * main_window->getSize().y;
}

void renderer::draw() {
    canvas.update((sf::Uint8*) pixels);
    main_window->draw(screen);
}

void renderer::tickMoveWindow() {
    // have we attempted to drag or close this window?
    sf::Event windowEvent;
    while(main_window->pollEvent(windowEvent))
    {
        if(windowEvent.type == sf::Event::Closed)
            main_window->close();
    }
}

void renderer::tick() {
    tickMoveWindow();

    main_window->clear();
    draw();
    main_window->display();

    ++ticks;
}

void renderer::close() {
    main_window->close();
    delete this;
}
