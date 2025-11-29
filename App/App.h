#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Grid.h"


/**
 * @brief Merepresentasikan status dari applikasi yang sedang dijalankan
 * 
 * Digunakan untuk berpindah-pindah tampilan window
 * ketika pengguna memilih menu pilihan
 */
enum class AppState {MainMenu, BFS, DFS};

struct App {
private:
  sf::RenderWindow window;
  sf::Font font;
  sf::Text DFS;
  sf::Text BFS;
  sf::SoundBuffer buffer;
  sf::Sound menuSound;
  AppState current_app;
  CellModifier brush_mod;

  Grid myGrid;
public:
    /**
    * @brief Konstruktor untuk applikasi yang menginisialisasikan semua member struct App
    * @param width lebar window
    * @param height tinggi window
    */
  App(unsigned int width, unsigned int height)
    : window(sf::VideoMode({width, height}), "GG"), 
      DFS(font, "DFS"), BFS(font, "BFS"), menuSound(buffer), myGrid(1, 5, width, height){
        if(!font.openFromFile("ARIAL.TTF")) {
            std::cerr << "File not found\n";
        }

        if(!buffer.loadFromFile("MenuSoundClick.mp3")) {
          std::cerr << "File not found\n";
        }

        menuSound.setBuffer(buffer);

        BFS.setPosition(sf::Vector2f({width / (2.f+1.f) * 1.f, height / 2.f}));
        DFS.setPosition(sf::Vector2f({width / (2.f+1.f) * 2.f, height / 2.f}));

        BFS.setFillColor(sf::Color(216, 222, 233));
        DFS.setFillColor(sf::Color(216, 222, 233));

        current_app= AppState::MainMenu;
        brush_mod = CellModifier::WallBrush;
  }

  /**
   * @brief Menangani interaksi jika menu ditekan
   * 
   * Fungsi ini mengecek apakah...... ke tampilan berdasarkan menu yang dipilih (DFS/BFS)
   * 
   * @param mouse_pos berisi koordinat mouse x dan y relatif pada window
   * @return Target AppState untuk transisi tampilan (MainMenu, BFS, DFS)
   */
  AppState ClickedMenu(sf::Vector2i mouse_pos) {
    sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
    if(DFS.getGlobalBounds().contains(mouse_pos_f)) { //mengecek apakah posisi mouse berada di string DFS
      return AppState::DFS;
    }
    if(BFS.getGlobalBounds().contains(mouse_pos_f)) { //mengecek apakah posisi mouse berada di string BFS
      return AppState::BFS;
    }
    return AppState::MainMenu;
  }

  /**
   * @brief Menangani interaksi antara menu dengan kursor mouse
   * 
   * Fungsi ini mengecek apakah koordinat kursor mouse berinteraksi dengan menu
   * (DFS/BFS) yaitu saat kursor berada dijangkauan teks.
   * ketika berinteraksi maka warna font berganti menjadi warna
   * dan skala teks berubah pindah ke tampilan berdasarkan menu yang dipilih (DFS/BFS)
   * 
   */
  void CheckMenuCollision(sf::Vector2i mouse_pos) {
    sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
    if(DFS.getGlobalBounds().contains(mouse_pos_f)) {
      if(DFS.getFillColor() == sf::Color(216, 222, 233)) {
        menuSound.play();
        DFS.setScale(sf::Vector2f({1.15f, 1.15f}));
      } 
      DFS.setFillColor(sf::Color(136, 192, 208));
      BFS.setFillColor(sf::Color(216, 222, 233));
      BFS.setScale(sf::Vector2f({1.f, 1.f}));
      return;
    }
    if(BFS.getGlobalBounds().contains(mouse_pos_f)) {
      if(BFS.getFillColor() == sf::Color(216, 222, 233)) {
          menuSound.play();
          BFS.setScale(sf::Vector2f({1.15f, 1.15f}));
      } 
      BFS.setFillColor(sf::Color(136, 192, 208));
      DFS.setFillColor(sf::Color(216, 222, 233));
      DFS.setScale(sf::Vector2f({1.f, 1.f}));
      return;
    }
    return;
  }

  //Main loop 
  void run() {
    while(window.isOpen()) {
      while(auto eventOpt = window.pollEvent()) { //looping ketika terjadi event pada window.
        auto &event = *eventOpt;
        if (auto *resize = event.getIf<sf::Event::Resized>()) { //update ukuran window kalau di resize
          sf::View view(sf::FloatRect({0.f, 0.f}, 
          {static_cast<float>(resize->size.x), static_cast<float>(resize->size.y)}));
              window.setView(view); //mengatur ukuran baru window.
          //update posisi teks BFS dan DFS
          BFS.setPosition({resize->size.x / (2.f+1.f)* 1.f, resize->size.y/(2.f)});  
          DFS.setPosition({resize->size.x / (2.f+1.f)* 2.f, resize->size.y/(2.f)});  
          
        } else if (event.getIf<sf::Event::Closed>()) { //event window ditutup
          window.close();
        } else if (event.is<sf::Event::MouseButtonPressed>()) { //event kalau mouse diklik
          sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); //mengambil posisi mouse
          if(current_app == AppState::MainMenu) {
              current_app = ClickedMenu(mouse_pos); 
          } else if(current_app == AppState::DFS || current_app == AppState::BFS) {
              //fitur untuk brush tool.
              myGrid.BrushTool(window, brush_mod, mouse_pos);
              std::cout << "Pressed DFS\n";
          }
        } else if (event.is<sf::Event::KeyPressed>()) {
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape) && current_app != AppState::MainMenu) {
            current_app = AppState::MainMenu;

            //setting ulang skala dan warna 
            DFS.setFillColor(sf::Color(216, 222, 233));
            DFS.setScale(sf::Vector2f({1.f, 1.f}));
            BFS.setFillColor(sf::Color(216, 222, 233));
            BFS.setScale(sf::Vector2f({1.f, 1.f}));
          } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
              brush_mod = CellModifier::WallBrush;
          } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
              brush_mod = CellModifier::SetStart;
          } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::E)) {
              brush_mod = CellModifier::SetEnd;
          }
        } else if (event.is<sf::Event::MouseMoved>()) {
          sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); //mengambil posisi mouse
          if(current_app == AppState::MainMenu) CheckMenuCollision(mouse_pos);
        }
      }
      
      window.clear(sf::Color(15, 23, 42));

      switch (current_app) {
        case AppState::MainMenu: //ketika app state adalah main menu, tampilkan main menu
          window.draw(DFS);
          window.draw(BFS);
          break;
        case AppState::BFS: //ketika app state adalah BFS, tampilkan BFS
            // if (!Run) {
          myGrid.DrawGrid(window);
                // Run = true;
            // }
            // std::cout << "BFS\n";
            // window.draw(sf::RectangleShape(sf::Vector2f({200, 300})));
          break;
        case AppState::DFS: //ketika app state adalah DFS, tampilkan DFS
            // std::cout << "DFS\n";
            // myGrid.DrawGrid(window);
          break;
        default:
          break;
      }
      // std::cout << "DFS\n";
      window.display(); //mengupdate tampilan window.
    }
  }
};