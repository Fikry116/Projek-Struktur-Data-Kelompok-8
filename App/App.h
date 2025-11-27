//buat run sistem biar di main rapih
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
enum class AppState {MainMenu, Queue, Stack};


struct App {
    sf::RenderWindow window;
    sf::Font font;
    sf::Text stack;
    sf::Text queue;
    sf::SoundBuffer buffer;
    sf::Sound main_menu_sound;
    AppState current_app;

    //Grid 


    App(unsigned int width, unsigned int height)
      : window(sf::VideoMode({width, height}), "GG"), 
        stack(font, "Stack"), queue(font, "Queue"), main_menu_sound(buffer){
          if(!font.openFromFile("ARIAL.TTF")) {
              std::cerr << "File not found\n";
          }

          if(!buffer.loadFromFile("MenuSoundClick.mp3")) {
            std::cerr << "File not found\n";
          }

          main_menu_sound.setBuffer(buffer);

          queue.setPosition(sf::Vector2f({width / (2.f+1.f) * 1.f, height / 2.f}));
          stack.setPosition(sf::Vector2f({width / (2.f+1.f) * 2.f, height / 2.f}));

          queue.setFillColor(sf::Color::White);
          stack.setFillColor(sf::Color::White);

          current_app= AppState::MainMenu;

    }
    /**
     * @brief Prosedur ini mengecek apakah
     */
    AppState ClickedMenu(sf::Vector2i mouse_pos) {
        stack.setFillColor(sf::Color::White);
        queue.setFillColor(sf::Color::White);

        sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
        main_menu_sound.play();
        if(stack.getGlobalBounds().contains(mouse_pos_f)) {
            stack.setFillColor(sf::Color::Red);
            return AppState::Queue;
        }
        if(queue.getGlobalBounds().contains(mouse_pos_f)) {
            queue.setFillColor(sf::Color::Red);
            return AppState::Queue;
        }
        return AppState::MainMenu;
    }

    void run() {
        while(window.isOpen()) {
            while(auto eventOpt = window.pollEvent()) { //looping ketika terjadi event pada window.
                auto &event = *eventOpt;
                if (auto *resize = event.getIf<sf::Event::Resized>()) { //update ukuran window kalau di resize
                    sf::View view(sf::FloatRect({0.f, 0.f}, 
                    {static_cast<float>(resize->size.x), static_cast<float>(resize->size.y)}));
                        window.setView(view); //mengatur ukuran baru window.
                    
                    //update posisi teks queue dan stack
                    queue.setPosition({resize->size.x / (2.f+1.f)* 1.f, resize->size.y/(2.f)});  
                    stack.setPosition({resize->size.x / (2.f+1.f)* 2.f, resize->size.y/(2.f)});  
                } else if (event.getIf<sf::Event::Closed>()) { //event window ditutup
                    window.close();
                } else if (event.is<sf::Event::MouseButtonPressed>()) { //event kalau mouse diklik
                    if(current_app == AppState::MainMenu) {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); //mengambil posisi mouse
                        current_app = ClickedMenu(mouse_pos); 
                    }
                } else if (event.is<sf::Event::KeyPressed>()) {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape)) {
                        current_app = AppState::MainMenu;
                    }
                }
            }
            
            window.clear(sf::Color(24, 59, 78));

            switch (current_app) {
            case AppState::MainMenu: //ketika app state adalah main menu, tampilkan main menu
                window.draw(stack);
                window.draw(queue);
                break;
            case AppState::Queue: //ketika app state adalah Queue, tampilkan BFS
                break;
            case AppState::Stack: //ketika app state adalah Stack, tampilkan DFS
                break;
            default:
                break;
            }
            window.display(); //mengupdate tampilan window.
        }
    }

    
};