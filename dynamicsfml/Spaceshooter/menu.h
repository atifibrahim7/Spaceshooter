#include "game.h"

class Menu {
public:
    Sprite menu, instruction;
    Texture menu_texture, instruction_tex;

    // Add menu attributes here
    Menu()
    {
        menu_texture.loadFromFile("img/PNG/Menu/thumbnail.jpg");
        instruction_tex.loadFromFile("img/PNG/Menu/instuction.png");
        instruction.setTexture(instruction_tex);
        menu.setTexture(menu_texture);
        menu.setScale(0.5, 0.75);
        menu.setPosition(0, 50);
        instruction.setScale(0.6, 1);
        instruction.setPosition(0, 50);

        // Constructor's body
    }

    void display_menu()
    {
        // Create a window to display the menu
        RenderWindow window(VideoMode(900, 900), "Menu");

        while (window.isOpen())
        {
            // Handle events
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
                // Check if the left mouse button is pressed
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                {
                    // Check if the mouse position is within the center of the screen
                    Vector2i mousePos = Mouse::getPosition(window);
                    std::cout << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << std::endl;
                    Vector2u windowSize = window.getSize();

                    if (mousePos.x >= 350 && mousePos.x <= 550 && mousePos.y >= 320 && mousePos.y <= 400)
                    {
                        // Start the game
                        window.close();
                        Game g;
                        g.start_game();
                    }
                    if (mousePos.x >= 380 && mousePos.x <= 560 && mousePos.y >= 450 && mousePos.y <= 490)
                    {
                        while (1)
                        {
                            window.draw(instruction);
                            window.display();
                            window.clear();

                            if (Keyboard::isKeyPressed(Keyboard::Key::BackSpace))
                                break;
                        }
                    }
                    if (mousePos.x >= 380 && mousePos.x <= 560 && mousePos.y >= 580 && mousePos.y <= 610)
                        window.close();

                }
            }

            // Draw the menu sprite
            window.clear();
            window.draw(menu);
            window.display();

            // Add functionality of all the menu options here
            // If Instruction option is chosen

            if (Keyboard::isKeyPressed(Keyboard::Key::I))
            {
                while (1)
                {
                    window.draw(instruction);
                    window.display();
                    window.clear();
                    if (Keyboard::isKeyPressed(Keyboard::Key::BackSpace))
                        break;
                }
            }
        }
    }
};
