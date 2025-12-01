#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Grid.h"
#include "GridRenderer.h"


/**
 * @brief Merepresentasikan status dari applikasi yang sedang dijalankan
 * 
 * Digunakan untuk berpindah-pindah tampilan window
 * ketika pengguna memilih menu pilihan
 */
enum class AppState {
  MainMenu,
  BFS,
  DFS
};

/**
 * @brief Struktur utama (Main Wrapper) yang menjalankan aplikasi.
 * * Class ini berfungsi sebagai wadah untuk semua komponen penting:
 * - Resource: Font, Suara, dan Window.
 * - Logika: Grid data (myGrid) dan sistem rendering (myRenderer).
 * - State: Status aplikasi saat ini (Menu, BFS, atau DFS).
 * * Cara kerjanya: Cukup buat instance struct ini di `main()`, lalu panggil fungsi `run()`.
 */
class App {
private:
  sf::RenderWindow window;
  sf::Font font;
  sf::Text DFS;
  sf::Text BFS;
  sf::SoundBuffer buffer_menu;
  sf::SoundBuffer buffer_menu_click;
  sf::Sound menu_sound;
  sf::Sound menu_click;
  AppState current_app;
  CellModifier brush_mod;

  Grid myGrid;
  GridRenderer myRenderer;
public:
    /**
    * @brief Konstruktor untuk applikasi yang menginisialisasikan semua member struct App
    * @param width lebar window
    * @param height tinggi window
    */
  App(unsigned int width, unsigned int height)
    : window(sf::VideoMode({width, height}), "GG"), 
      DFS(font, "DFS"), BFS(font, "BFS"), menu_sound(buffer_menu), menu_click(buffer_menu_click),
      myGrid(1, 5, width, height), myRenderer(myGrid.GetGridSize()) {

        if(!font.openFromFile("ARIAL.TTF")) {
            std::cerr << "File not found\n";
        }

        if(!buffer_menu.loadFromFile("MenuCollision.mp3")) {
          std::cerr << "File not found\n";
        }

        if(!buffer_menu_click.loadFromFile("MenuClick.mp3")) {
          std::cerr << "File not found\n";
        }

        window.setFramerateLimit(30);

        menu_sound.setBuffer(buffer_menu);
        menu_click.setBuffer(buffer_menu_click);

        BFS.setPosition(sf::Vector2f({width / (2.f+1.f) * 1.f, height / 2.f}));
        DFS.setPosition(sf::Vector2f({width / (2.f+1.f) * 2.f, height / 2.f}));

        BFS.setFillColor(sf::Color(216, 222, 233));
        DFS.setFillColor(sf::Color(216, 222, 233));

        current_app= AppState::MainMenu;
        brush_mod = CellModifier::WallBrush;
  }

  /**
   * @brief Menentukan transisi state aplikasi berdasarkan interaksi klik mouse.
   * * Fungsi ini melakukan "Hit Test" pada elemen UI (DFS/BFS). Jika kursor berada 
   * di dalam area bounding box teks saat diklik, fungsi akan mengembalikan state baru.
   * * @param mouse_pos Koordinat kursor mouse relatif terhadap window (Screen Space).
   * @return AppState Target state selanjutnya (DFS/BFS). Mengembalikan AppState::MainMenu 
   * jika klik dilakukan di area kosong (tidak ada menu yang dipilih).
   */
  AppState ClickedMenu(sf::Vector2i mouse_pos) {
    sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
    if(DFS.getGlobalBounds().contains(mouse_pos_f)) { //mengecek apakah posisi mouse berada di string DFS
      menu_click.play();
      return AppState::DFS;
    }
    if(BFS.getGlobalBounds().contains(mouse_pos_f)) { //mengecek apakah posisi mouse berada di string BFS
      menu_click.play();
      return AppState::BFS;
    }
    return AppState::MainMenu;
  }

  /**
   * @brief Menangani logika visual saat kursor berada di atas menu.
   * * Fungsi ini mendeteksi apakah kursor mouse berada dalam area bounding box teks menu.
   * Jika terdeteksi (collision), fungsi akan memberikan umpan balik visual (perubahan warna & skala)
   * dan audio (sfx) kepada pengguna.
   * * @param mouse_pos Koordinat posisi mouse saat ini (dalam satuan piksel window).
   * @note Konversi ke sf::Vector2f diperlukan karena fungsi `contains` membutuhkan koordinat floating point.
   */
  void CheckMenuCollision(sf::Vector2i mouse_pos) {
    sf::Vector2f mouse_pos_f(static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
    if(DFS.getGlobalBounds().contains(mouse_pos_f)) {
      if(DFS.getFillColor() == sf::Color(216, 222, 233)) {
        menu_sound.play();
        DFS.setScale(sf::Vector2f({1.15f, 1.15f}));
      } 
      DFS.setFillColor(sf::Color(136, 192, 208));
      BFS.setFillColor(sf::Color(216, 222, 233));
      BFS.setScale(sf::Vector2f({1.f, 1.f}));
      return;
    }
    if(BFS.getGlobalBounds().contains(mouse_pos_f)) {
      if(BFS.getFillColor() == sf::Color(216, 222, 233)) {
          menu_sound.play();
          BFS.setScale(sf::Vector2f({1.15f, 1.15f}));
      } 
      BFS.setFillColor(sf::Color(136, 192, 208));
      DFS.setFillColor(sf::Color(216, 222, 233));
      DFS.setScale(sf::Vector2f({1.f, 1.f}));
      return;
    }
    return;
  }

  /**
   * @brief Siklus utama aplikasi (Main Game Loop).
   * * Fungsi ini menangani siklus hidup aplikasi yang mencakup:
   * 1. **Event Polling**: Menangani input diskrit (keypress, resize, close).
   * 2. **Real-time Input**: Menangani input continuous (mouse drag untuk menggambar).
   * 3. **Logic Update**: Mengatur transisi state (Menu <-> Algoritma) dan tool modifier.
   * 4. **Rendering**: Membersihkan layar, menggambar objek berdasarkan state aktif, dan menampilkannya (Double Buffering).
   * * @note Loop ini akan terus berjalan selama window terbuka.
   * @details Key mapping: [W] Wall, [S] Start Node, [E] End Node, [Right Click] Erase.
   */
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
          // } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::R)) {
          //   myRenderer.RandomWall(myGrid);
          // }
        } else if (event.is<sf::Event::MouseMoved>()) {
          sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); //mengambil posisi mouse
          if(current_app == AppState::MainMenu) CheckMenuCollision(mouse_pos);
        }
      }

      //gambar tembok/set start/set end 
      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { //event kalau mouse diklik
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); //mengambil posisi mouse
        if(current_app == AppState::MainMenu) {
          current_app = ClickedMenu(mouse_pos); 
        } else if(current_app == AppState::DFS || current_app == AppState::BFS) {
          myRenderer.BrushTool(window, brush_mod, mouse_pos, myGrid);
        }
      } else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window); //mengambil posisi mouse
        myRenderer.BrushTool(window, CellModifier::Erase, mouse_pos, myGrid);
      }
      
      window.clear(sf::Color(15, 23, 42));//background window
      
      switch (current_app) {
        case AppState::MainMenu: //ketika app state adalah main menu, tampilkan main menu
        window.draw(DFS);
        window.draw(BFS);
        break;
      case AppState::BFS: //ketika app state adalah BFS, tampilkan BFS
          myRenderer.DrawGrid(window, myGrid);
        break;
      case AppState::DFS: //ketika app state adalah DFS, tampilkan DFS
        break;
      default:
        break;
      }
      // std::cout << "DFS\n";
      window.display(); //mengupdate tampilan window.
    }
  }
};