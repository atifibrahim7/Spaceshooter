#pragma once 
#include "menu.h"

Menu ::Menu()
{
    menu_texture.loadFromFile("img/Menu.jpg");
    instruction_tex.loadFromFile("img/PNG/Menu/instuction.png");
    instruction.setTexture(instruction_tex);
    menu.setTexture(menu_texture);
    menu.setScale(0.5, 0.5);
    instruction.setScale(0.6, 1);
    instruction.setPosition(0, 50);

    // Constructor's body
}

void Menu::display_menu(bool& flag, Sprite* s)
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
                Vector2i mousePos = Mouse::getPosition(window);

                if (mousePos.x >= 350 && mousePos.x <= 550 && mousePos.y >= 320 && mousePos.y <= 400)
                {
                    // Start the game
                    flag = 1;
                    window.close();

                    // Game g;
                    // g.start_game();
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
                if (mousePos.x >= 380 && mousePos.x <= 560 && mousePos.y >= 610 && mousePos.y <= 640)
                {
                    //~Game();
                    flag = 0;
                    window.close();
                }
                else if (mousePos.x >= 300 && mousePos.x <= 515 && mousePos.y >= 540 && mousePos.y <= 590)
                {
                    displayHighScores(window, event, s);
                }
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

void Menu::displayHighScores(RenderWindow& window, Event& event, Sprite* s)
{
    std::ifstream inputFile("scores.txt");
    if (inputFile.is_open())
    {
        std::string line;
        std::vector<std::string> highScores;

        // Read the first three lines from the file
        for (int i = 0; i < 6 && std::getline(inputFile, line); i++)
        {
            highScores.push_back(line);
        }

        inputFile.close();

        // Create an SFML window to display the high scores
     //   RenderWindow window(VideoMode(400, 300), "High Scores");

        // Create a SFML text object to display the high scores
        // Create a SFML text object to display the high scores
        Font font;
        if (!font.loadFromFile("img/SS.otf"))
        {
            std::cout << "Error: Unable to load font." << std::endl;
            return;
        }

        Text text;
        text.setFont(font);
        text.setCharacterSize(50);
        text.setFillColor(Color::Yellow);

        // Set the position and content of the high scores text
        std::string highScoresText = "      High Scores:\n";
        text.setFillColor(Color::White);
        for (const auto& score : highScores)
        {
            highScoresText += score + "\n";
        }
        text.setString(highScoresText);
        text.setPosition(120.f, 120.f);
        for (int i = 0; i < 3; i++)
        {
            s[i].setScale(0.05, 0.05);
            s[i].setPosition(50, 190 + i * 50);

        }
        // Main loop for rendering the window
        while (window.isOpen())
        {
            // Handle events
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                }
                else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Key::BackSpace)
                {
                    return;
                }
            }

            window.clear(Color::Black);
            for (int i = 0; i < 3; i++)
                window.draw(s[i]);
            window.draw(text);
            window.display();
        }
    }
    else
    {
        std::cout << "Error: Unable to open the scores file." << std::endl;
    }
}
