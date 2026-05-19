# Blackjack Game

A C++ blackjack game with two ways to play:

- a console version for quick terminal games
- a Crow-powered web version with a simple HTML/CSS/JavaScript interface

The game supports finite multi-deck play, infinite-deck simulation, dealer play, hidden dealer cards, hand scoring with aces, and basic-strategy recommendations.

## Features

- Console and browser gameplay
- Finite deck mode with automatic reshuffle
- Infinite deck mode
- Blackjack scoring with soft ace handling
- Dealer logic that hits below 17
- Strategy helper for hard totals, soft totals, and pairs
- Web API endpoints for starting, hitting, standing, and reading state
- Included Windows build script for the web server

## Project Structure

```text
.
├── main.cpp              # Console entry point
├── web_main.cpp          # Crow web server and API routes
├── blackjack.h           # Main game logic
├── deck.h                # Deck/shoe handling
├── hand.h                # Hand scoring and helpers
├── card.h                # Card value model
├── player.h              # Player wrapper around a hand
├── strategy.h            # Basic strategy tables
├── index.html            # Web UI markup
├── style.css             # Web UI styling
├── script.js             # Web UI behavior
├── build_web.bat         # Windows build script for web version
├── crow_all.h            # Crow single-header dependency
└── include/              # Standalone ASIO headers
```

## Requirements

- Windows
- `g++` with C++17 support, such as MSYS2 MinGW
- A modern web browser for the web version

The repository includes Crow and standalone ASIO headers, so no package manager is required for the current Windows build.

## Build the Web Version

From PowerShell or Command Prompt:

```powershell
cd "path\to\Blackjack-game"
.\build_web.bat
```

This creates:

```text
web_blackjack.exe
```

The build command used by the script is:

```powershell
g++ web_main.cpp -o web_blackjack.exe -Iinclude -DASIO_STANDALONE -lws2_32 -lmswsock -O2 -std=c++17
```

## Run the Web Version

```powershell
.\web_blackjack.exe
```

Then open:

```text
http://127.0.0.1:18080
```

## Run the Console Version

Build:

```powershell
g++ main.cpp -o blackjack.exe -std=c++17
```

Run:

```powershell
.\blackjack.exe
```

You can choose finite deck mode or infinite deck mode when the program starts.

## Web API

The web server exposes a small JSON API.

### Start a Game

```http
POST /api/start
Content-Type: application/json
```

Example body:

```json
{
  "decks": 2,
  "infinite": false
}
```

Example PowerShell request:

```powershell
Invoke-RestMethod -Uri http://127.0.0.1:18080/api/start `
  -Method Post `
  -ContentType "application/json" `
  -Body '{"decks":2,"infinite":false}'
```

Example response:

```json
{
  "playerHand": [5, 4],
  "dealerHand": [9, 0],
  "playerScore": 9,
  "dealerScore": 0,
  "gameOver": false,
  "message": "Game started",
  "recommendation": "HIT"
}
```

`0` in `dealerHand` means the dealer hole card is hidden.

### Hit

```http
POST /api/hit
```

Draws one card for the player and returns the updated game state.

### Stand

```http
POST /api/stand
```

Finishes the dealer turn and returns the final result.

### Current State

```http
GET /api/state
```

Returns the current game state.

## Gameplay Notes

- Card values are numeric.
- Face cards are represented as `10`.
- Aces are represented as `11`, then counted as `1` automatically when needed.
- The dealer's second card is hidden until the player busts or stands.
- Recommendations come from the strategy tables in `strategy.h`.

## Development Notes

Quick syntax checks:

```powershell
g++ -fsyntax-only main.cpp -std=c++17
g++ -fsyntax-only web_main.cpp -Iinclude -DASIO_STANDALONE -std=c++17
```

The web server listens on port `18080` by default. You can change this in `web_main.cpp`.
