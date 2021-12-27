#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <random>
#include "controller.h"
#include "view.h"
#include "solver.h"

#include <cstdint>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>


using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

void Controller::execute()
{

    Uint32 titleTimestamp = SDL_GetTicks();
    Uint32 frameStart;
    Uint32 frameEnd;
    Uint32 frameDuration;
    int frameCount = 0;
    bool quit = false;
    bool gameOver = false;
    bool userPlayed = false;
    SDL_bool mouse_active = SDL_FALSE;
    SDL_bool mouse_hover = SDL_FALSE;

    makeFirstMove(solver, fieldTypeP2);
    view.drawGridState(solver.getGameField(), fieldTypeP2);
    view.drawGridLines();
    view.update();
	

    while (!quit)
    {

        frameStart = SDL_GetTicks();

        view.waitForInput(quit, userPlayed);

        if (userPlayed && !gameOver)
        {
            int selectedIndex = view.getSelectedIndex();

            if (solver.isEmptyField(selectedIndex))
            {

                if (solver.isWinningField(selectedIndex, fieldTypeP1))
                {

                    solver.setFieldValue(selectedIndex, fieldTypeP1);
                    gameOver = true;
                }
                else
                {
                    solver.setFieldValue(selectedIndex, fieldTypeP1);

                    int response = solver.solve(fieldTypeP2, 0);

                    if (solver.getWinningIndex() >= 0)
                    {
                        if (solver.isWinningField(solver.getWinningIndex(), fieldTypeP2))
                        {
                            gameOver = true;
                        }
                        solver.setFieldValue(solver.getWinningIndex(), fieldTypeP2);
                    }
                }
            }
            if (gameOver)
            {
                view.drawSolution(solver.getWinningIndices());
            }
            view.drawGridState(solver.getGameField(), fieldTypeP2);
            view.drawGridLines();

            view.update();

            userPlayed = false;
        }

        frameEnd = SDL_GetTicks();
        frameCount++;
        frameDuration = frameEnd - frameStart;

        // After every second, update the window title.
        if (frameEnd - titleTimestamp >= 1000)
        {

            frameCount = 0;
            titleTimestamp = frameEnd;
        }

        // If the time for this frame is too small (i.e. frameDuration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        std::size_t kFramesPerSecond{60};
        std::size_t targetFrameDuration{1000 / kFramesPerSecond};

        if (frameDuration < targetFrameDuration)
        {
            SDL_Delay(targetFrameDuration - frameDuration);
        }
    }
}


{
void Controller::CreateDoc()
{
   "name" : "MongoDB",
   "type" : "database",
   "winner" : "",
   "versions": [ "v3.2", "v3.0", "v2.6" ],
   "info" : {
               "x" : 203,
               "y" : 102
            }
}

}
void Controller::sendData(string s)
{
Controller::connectDb(mongosh "mongodb+srv://cluster0.bxwn6.mongodb.net/myFirstDatabase" --username yura224112);
Controller::CreateDoc();

auto builder = bsoncxx::builder::stream::document{};
bsoncxx::document::value doc_value = builder
  << "name" << "MongoDB"
  << "type" << "database"
  << "winner" << s
  << "versions" << bsoncxx::builder::stream::open_array
    << "v3.2" << "v3.0" << "v2.6"
  << close_array
  << "info" << bsoncxx::builder::stream::open_document
    << "x" << 203
    << "y" << 102
  << bsoncxx::builder::stream::close_document
  << bsoncxx::builder::stream::finalize;
}

/* PRIVATE */

/*
 * Using uniform distribution, the first move is just a random field.
 * https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
 */
void Controller::makeFirstMove(Solver &solver, const FieldType type)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, (frameSize * frameSize) - 1);
    int startingPosition = dis(gen);
    solver.setFieldValue(startingPosition, type);
}
void Controller::connectDb(uri)
{
mongocxx::instance instance{}; 
mongocxx::uri uri("mongodb://localhost:27017");
mongocxx::client client(uri);
}
