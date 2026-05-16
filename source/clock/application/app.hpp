#ifndef APP_HPP
#define APP_HPP

class App
{
public:
    App();
    App(int width, int height);
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    App(App&&) = delete;
    App& operator=(App&&) = delete;

    void Loop();

private:
    // TODO update phase method
    // TODO draw phase method
    // TODO An app has an event bus
    // TODO An app has a time source
    // TODO An app has a dial
    // TODO An app holds the responsive UI elements control buttons
};

#endif APP_HPP