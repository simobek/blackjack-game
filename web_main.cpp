#define CROW_MAIN
#include "blackjack.h"
#include "crow_all.h"
#include <memory>
#include <mutex>

using namespace std;

// Global game instance
std::unique_ptr<blackjack> game;
std::mutex gameMutex;

crow::response stateToResponse(const GameState &state) {
  crow::json::wvalue json;
  std::vector<crow::json::wvalue> pHand;
  for (int card : state.playerHand)
    pHand.push_back(card);

  std::vector<crow::json::wvalue> dHand;
  for (int card : state.dealerHand)
    dHand.push_back(card);

  json["playerHand"] = crow::json::wvalue::list(std::move(pHand));
  json["dealerHand"] = crow::json::wvalue::list(std::move(dHand));
  json["playerScore"] = state.playerScore;
  json["dealerScore"] = state.dealerScore;
  json["gameOver"] = state.gameOver;
  json["message"] = state.message;
  json["recommendation"] = state.recommendation;

  return crow::response(json.dump());
}

int main() {
  crow::SimpleApp app;

  // Serve static files
  CROW_ROUTE(app, "/")([](const crow::request &, crow::response &res) {
    res.set_static_file_info("index.html");
    res.end();
  });

  CROW_ROUTE(app, "/style.css")([](const crow::request &, crow::response &res) {
    res.set_static_file_info("style.css");
    res.end();
  });

  CROW_ROUTE(app, "/script.js")([](const crow::request &, crow::response &res) {
    res.set_static_file_info("script.js");
    res.end();
  });

  // API Routes
  CROW_ROUTE(app, "/api/start")
      .methods(crow::HTTPMethod::Post)([](const crow::request &req) {
        auto x = crow::json::load(req.body);
        if (!x)
          return crow::response(400);

        int decks = 2;         // Default
        bool infinite = false; // Default

        if (x.has("decks"))
          decks = x["decks"].i();
        if (x.has("infinite"))
          infinite = x["infinite"].b();

        std::lock_guard<std::mutex> lock(gameMutex);
        game = std::make_unique<blackjack>(decks, infinite);
        return stateToResponse(game->startGameState(decks, infinite));
      });

  CROW_ROUTE(app, "/api/hit").methods(crow::HTTPMethod::Post)([]() {
    std::lock_guard<std::mutex> lock(gameMutex);
    if (!game)
      return crow::response(400, "Game not started");

    return stateToResponse(game->hitState());
  });

  CROW_ROUTE(app, "/api/stand").methods(crow::HTTPMethod::Post)([]() {
    std::lock_guard<std::mutex> lock(gameMutex);
    if (!game)
      return crow::response(400, "Game not started");

    return stateToResponse(game->standState());
  });

  CROW_ROUTE(app, "/api/state").methods(crow::HTTPMethod::Get)([]() {
    std::lock_guard<std::mutex> lock(gameMutex);
    if (!game)
      return crow::response(400, "Game not started");

    return stateToResponse(game->getGameState());
  });

  app.port(18080).multithreaded().run();
}
