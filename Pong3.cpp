#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Pong", Style::Fullscreen);
    int P1score = 0;
    int P1lives = 3;
    int P2score = 0;
    int P2lives = 3;
    // Create a bat at the bottom center of the screen
    Bat bat(1910, 1080/2);
    Bat bat2(10 , 1080/2);

    // Create a ball
    Ball ball(1920 / 2, 0);

    // Create a Text object called HUD
    Text hud;
    Text hud2;
    Text Start;
    Text Pause;
    Text gameOver;
    // A cool retro-style font
    Font font;
    font.loadFromFile("fonts/DS-DIGIT.ttf");
    // Set the font to our retro-style
    hud.setFont(font);
    hud2.setFont(font);
    Start.setFont(font);
    Pause.setFont(font);
    gameOver.setFont(font);
    // Make it nice and big
    hud.setCharacterSize(50);
    hud2.setCharacterSize(50);
    Start.setCharacterSize(50);
    Pause.setCharacterSize(50);
    gameOver.setCharacterSize(50);
    // Choose a rr
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);
    hud2.setFillColor(Color::White);
    hud2.setPosition(1400, 20);
    Start.setFillColor(Color::White);
    Start.setPosition(460, 340);
    Pause.setFillColor(Color::White);
    Pause.setPosition(660, 540);
    gameOver.setFillColor(Color::White);
    gameOver.setPosition(960, 540);
    // Here is our clock for timing everything
    Clock clock;
    //The game is running
    bool paused = true;

    while (window.isOpen())
    {
        /*
        Handle the player input
        ****************************
        ****************************
        ****************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                // Quit the game when the window is closed
                window.close();
        }

        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Handle the pressing and releasing of the arrow keys
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            bat.moveUp();
        }
        else
        {
            bat.stopUp();
        }

        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            bat.moveDown();
        }
        else
        {
            bat.stopDown();
        }

        // Handle the pressing and releasing of the arrow keys
        if (Keyboard::isKeyPressed(Keyboard::LShift))
        {
            bat2.moveUp();
        }
        else
        {
            bat2.stopUp();
        }

        if (Keyboard::isKeyPressed(Keyboard::LControl))
        {
            bat2.moveDown();
        }
        else
        {
            bat2.stopDown();
        }

        //Pause
        if (Keyboard::isKeyPressed(Keyboard::R)) {
            bool paused = false;
        }

        /*
        Update the bat, the ball and the HUD
        *****************************
        *****************************
        *****************************
        */
        if(paused) {
           
        // Update the delta time
        Time dt = clock.restart();

        bat.update(dt);
        bat2.update(dt);
        ball.update(dt);

        // Update the HUD text
        std::stringstream P1ss;
        std::stringstream P2ss;
        std::stringstream St;
        std::stringstream Pa;
        std::stringstream gO;
        P1ss << "P1 Score: " << P1score << "  Lives: " << P1lives;
        P2ss << "P2 Score: " << P2score << " Lives: " << P2lives;
        St << "Welcome to Pong" << "\n" << "Press Enter to Play" << "\n";
        Pa << "Pause" << "\n" << "Press R to Resume" << "\n";
        gO << "Game Over" << "\n";
        hud.setString(P1ss.str());
        hud2.setString(P2ss.str());
        Start.setString(St.str());
        Pause.setString(Pa.str());
        gameOver.setString(gO.str());

        // Handle ball hitting the bottom
        if (ball.getPosition().top > window.getSize().y)
        {
            // reverse the ball direction
            ball.reboundTopOrBottom();
            /* Remove a life
            lives--;*/
            // Check for zero lives
            if (P1lives < 1) {
                paused = true;
                // reset the score
                P1score = 0;
                // reset the lives
                //P1lives = 3;
            }
            if (P2lives < 1) {
                paused = true;
                // reset the score
                P2score = 0;
                // reset the lives
                //P2lives = 3;
            }
        }

        // Handle ball hitting top
        if (ball.getPosition().top < 0)
        {
            ball.reboundTopOrBottom();
            /* Add a point to the players score
            score++;*/
        }

        // Handle ball hitting sides
        if (ball.getPosition().left < 0)
        {
            ball.reboundSides();
            //Remove a life
            P1lives--;
        }
        // Handle ball hitting sides
        if (ball.getPosition().left > 1921 ||
            ball.getPosition().left + ball.getPosition().width> window.
            getSize().x)
        {
            ball.reboundSides();
            //Remove a life
            P2lives--;
        }

        // Has the ball hit the bat?
        if (ball.getPosition().intersects(bat.getPosition()))
        {
            // Hit detected so reverse the ball and score a point
            ball.reboundBat();
            // Add a point to the players score
            P2score++;
        }

        // Has the ball hit the bat?
        if (ball.getPosition().intersects(bat2.getPosition()))
        {
            // Hit detected so reverse the ball and score a point
            ball.reboundBat();
            // Add a point to the players score
            P1score++;
        }
                }

        /*
        Draw the bat, the ball and the HUD
        *****************************
        *****************************
        *****************************
        */

        window.clear();
        window.draw(Start);
        window.draw(hud);
        window.draw(hud2);
        if(Keyboard::isKeyPressed(Keyboard::S)) {
            bool paused = true;
            window.draw(Pause);
        }
        window.draw(bat.getShape());
        window.draw(bat2.getShape());
        window.draw(ball.getShape());
        if(P1lives || P2lives < 1) {
            window.draw(gameOver);
            !paused;
        }
        window.display();
    }
    return 0;
}