#include "GameApp.h"

// --------------------------------------------------------------------
// CONSTRUCTOR
// --------------------------------------------------------------------
GameApp::GameApp()
    : window(nullptr),
    renderer(nullptr),
    running(true),
    currentState(SPLASH),
    splashAlpha(0),
    splashTimer(0),
    fadeDuration(4500),
    fadeIn(true),
    currentPlayerIndex(0),
    selectedGameMode(GameMode::SEVEN_CARDS)
{
}

// --------------------------------------------------------------------
// INITIALIZATION
// --------------------------------------------------------------------
bool GameApp::init()
{
    if (TTF_Init() < 0) {
        std::cerr << "SDL_ttf could not initialize! Error: " << TTF_GetError() << std::endl;
        return false;
    }
    m_font = TTF_OpenFont("../assets/Arial.ttf", 24); // Increased size for better visibility
    if (!m_font) {
        std::cerr << "Failed to load font! Error: " << TTF_GetError() << std::endl;
        return false;
    }

    // 1) SDL init
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        std::cerr << "SDL could not initialize! Error: "
            << SDL_GetError() << std::endl;
        return false;
    }

    // 2) SDL_image init (PNG)
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cerr << "SDL_image could not initialize! Error: "
            << IMG_GetError() << std::endl;
        return false;
    }

    // 3) Create window
    window = SDL_CreateWindow("Eter Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Window could not be created! Error: "
            << SDL_GetError() << std::endl;
        return false;
    }

    // 4) Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! Error: "
            << SDL_GetError() << std::endl;
        return false;
    }

    // 5) Load splash
    {
        SDL_Surface* surf = IMG_Load("Intro.png");
        if (!surf)
        {
            std::cerr << "Failed to load splash image: "
                << IMG_GetError() << std::endl;
            return false;
        }
        splashTexture = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }

    // 6) Load backgrounds
    {
        SDL_Surface* surf = IMG_Load("Menu.png");
        if (!surf)
        {
            std::cerr << "Failed to load main_menu_bg: "
                << IMG_GetError() << std::endl;
            return false;
        }
        mainMenuBg = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }
    {
        SDL_Surface* surf = IMG_Load("Menu.png");
        if (!surf)
        {
            std::cerr << "Failed to load settings_bg: "
                << IMG_GetError() << std::endl;
            return false;
        }
        settingsBg = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }
    {
        SDL_Surface* surf = IMG_Load("Menu.png");
        if (!surf)
        {
            std::cerr << "Failed to load game_board_bg: "
                << IMG_GetError() << std::endl;
            return false;
        }
        gameBoardBg = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }

    // 7) Prepare splash fade
    SDL_SetTextureBlendMode(splashTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(splashTexture, splashAlpha);

    // 8) Init buttons & board
    initButtons();
    initBoard(); // Board cells, position, etc.

    initCardTextures();
    initPlayerHands();

    return true;
}

void GameApp::initCardTextures()
{
    std::vector<std::string> cardPaths = {
        "../assets/blue_card_1.png", "../assets/blue_card_1.png", 
        "../assets/blue_card_2.png", "../assets/blue_card_2.png", 
        "../assets/blue_card_3.png", "../assets/blue_card_3.png", 
        "../assets/blue_card_4.png"                             
    };

    for (const auto& path : cardPaths) {
        SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
        if (!texture) {
            std::cerr << "Failed to load texture: " << path << " - " << IMG_GetError() << std::endl;
        }
        else {
            blueCardTextures.push_back(texture);
        }
    }

    cardPaths = {
        "../assets/red_card_1.png", "../assets/red_card_1.png",   
        "../assets/red_card_2.png", "../assets/red_card_2.png",  
        "../assets/red_card_3.png", "../assets/red_card_3.png",  
        "../assets/red_card_4.png"                                 
    };

    for (const auto& path : cardPaths) {
        SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
        if (!texture) {
            std::cerr << "Failed to load texture: " << path << " - " << IMG_GetError() << std::endl;
        }
        else {
            redCardTextures.push_back(texture);
        }
    }
}

void GameApp::initPlayerHands()
{

    // Initialize Player 1 cards 
    for (int i = 0; i < 7; ++i) {
        Cardx card;
        card.value = (i < 2) ? 1 : (i < 4) ? 2 : (i < 6) ? 3 : 4;
        card.rect = { 100 + i * 120, 800, 100, 150 };
        card.faceUp = true;
        card.texture = blueCardTextures[card.value - 1];
        player1.hand.push_back(card);
    }

    // Initialize Player 2 cards
    for (int i = 0; i < 7; ++i) {
        Cardx card;
        card.value = (i < 2) ? 1 : (i < 4) ? 2 : (i < 6) ? 3 : 4;
        card.rect = { 100 + i * 120, 100, 100, 150 };
        card.faceUp = false;
        card.texture = redCardTextures[card.value - 1];
        player2.hand.push_back(card);
    }
}

void GameApp::cleanCardTextures()
{
    for (auto texture : blueCardTextures)
    {
        if (texture) SDL_DestroyTexture(texture);
    }
    blueCardTextures.clear();

    for (auto texture : redCardTextures)
    {
        if (texture) SDL_DestroyTexture(texture);
    }
    redCardTextures.clear();

}

// --------------------------------------------------------------------
// MAIN LOOP
// --------------------------------------------------------------------
void GameApp::run()
{
    Uint32 lastTick = getTick();

    while (running)
    {
        Uint32 currentTick = getTick();
        Uint32 deltaTime = currentTick - lastTick;
        lastTick = currentTick;

        handleEvents();
        update(deltaTime);
        render();

        // Frame capping
        Uint32 frameTime = getTick() - currentTick;
        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
}

// --------------------------------------------------------------------
// CLEAN-UP
// --------------------------------------------------------------------
void GameApp::clean()
{
    if (m_font) {
        TTF_CloseFont(m_font);
    }
    TTF_Quit();
    if (splashTexture)   SDL_DestroyTexture(splashTexture);
    if (mainMenuBg)      SDL_DestroyTexture(mainMenuBg);
    if (settingsBg)      SDL_DestroyTexture(settingsBg);
    if (gameBoardBg)     SDL_DestroyTexture(gameBoardBg);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}

// --------------------------------------------------------------------
// GET TICKS (HELPER)
// --------------------------------------------------------------------
Uint32 GameApp::getTick()
{
    return SDL_GetTicks();
}

// --------------------------------------------------------------------
// BUTTONS INIT
// --------------------------------------------------------------------
void GameApp::initButtons()
{
    int buttonWidth = 400;
    int buttonHeight = 100;
    int gap = 10;

    SDL_Texture* texture = NULL;
    

    // Main menu buttons (bottom-middle)
    int xPos = (SCREEN_WIDTH - buttonWidth) / 2;
    int yPos = SCREEN_HEIGHT - 350; // offset from bottom

    playButton.rect = { xPos, yPos, buttonWidth, buttonHeight };
    playButton.text = "Play";
    playButton.hovered = false;
    SDL_Surface* textSurface = TTF_RenderText_Shaded(m_font, playButton.text.c_str(), SDL_Color(255.f, 255.f, 255.f, 255.f), SDL_Color(0.f, 0.f, 0.f, 0.f));
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, texture, NULL, &playButton.rect);
    SDL_FreeSurface(textSurface);

    settingsButton.rect = { xPos, yPos + (buttonHeight + gap),
                             buttonWidth, buttonHeight };
    settingsButton.text = "Settings";
    settingsButton.hovered = false;

    quitButton.rect = { xPos, yPos + 2 * (buttonHeight + gap),
                             buttonWidth, buttonHeight };
    quitButton.text = "Quit";
    quitButton.hovered = false;

    // Settings menu buttons
    settingsButton1.rect = { 200, 200, buttonWidth, buttonHeight };
    settingsButton1.text = "Option A";   // e.g. 7 Cards
    settingsButton1.hovered = false;

    settingsButton2.rect = { 200, 310, buttonWidth, buttonHeight };
    settingsButton2.text = "Option B";   // e.g. 10 Cards
    settingsButton2.hovered = false;

    settingsButton3.rect = { 200, 420, buttonWidth, buttonHeight };
    settingsButton3.text = "Training";
    settingsButton3.hovered = false;

    settingsBackButton.rect = { 200, 530, buttonWidth, buttonHeight };
    settingsBackButton.text = "Back";
    settingsBackButton.hovered = false;
}

// --------------------------------------------------------------------
// BOARD INIT
// --------------------------------------------------------------------
void GameApp::initBoard()
{
    // Initialize all cells to empty
    for (int r = 0; r < BOARD_ROWS; ++r) {
        for (int c = 0; c < BOARD_COLS; ++c) {
            gameBoard.cells[r][c].cardOwner = -1;
            gameBoard.cells[r][c].cardIndex = -1;
        }
    }

    gameBoard.cellWidth = 80;
    gameBoard.cellHeight = 120;

    int totalBoardWidth = BOARD_COLS * gameBoard.cellWidth;
    int totalBoardHeight = BOARD_ROWS * gameBoard.cellHeight;

    // Center the 5×5 board in the screen
    gameBoard.boardX = (SCREEN_WIDTH - totalBoardWidth) / 2;
    gameBoard.boardY = (SCREEN_HEIGHT - totalBoardHeight) / 2;
}

// --------------------------------------------------------------------
// HANDLE EVENTS
// --------------------------------------------------------------------
void GameApp::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) {
            running = false;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            int mx = e.button.x;
            int my = e.button.y;

            // -------------------------
            // MAIN MENU
            // -------------------------
            if (currentState == MAIN_MENU)
            {
                if (isMouseOverButton(mx, my, playButton)) {
                    currentState = PLAY;
                    startGame();
                }
                else if (isMouseOverButton(mx, my, settingsButton)) {
                    currentState = SETTINGS;
                }
                else if (isMouseOverButton(mx, my, quitButton)) {
                    currentState = QUIT;
                    running = false;
                }
            }
            // -------------------------
            // SETTINGS
            // -------------------------
            else if (currentState == SETTINGS)
            {
                if (isMouseOverButton(mx, my, settingsBackButton)) {
                    currentState = MAIN_MENU;
                }
                // e.g., if Option A means 7 cards, Option B means 10 cards
                else if (isMouseOverButton(mx, my, settingsButton1)) {
                    selectedGameMode = GameMode::SEVEN_CARDS;
                }
                else if (isMouseOverButton(mx, my, settingsButton2)) {
                    selectedGameMode = GameMode::TEN_CARDS;
                }
                else if (isMouseOverButton(mx, my, settingsButton3)) {
                    // This sets the game to TRAINING mode
                    selectedGameMode = GameMode::TRAINING;
                }
                // etc.
            }
            // -------------------------
            // PLAY
            // -------------------------
            else if (currentState == PLAY)
            {
                // Drag detection on the *active player's* hand
                Player_UI& activePlayer = (currentPlayerIndex == 0) ? player1 : player2;

                for (auto& card : activePlayer.hand)
                {
                    if (mx >= card.rect.x && mx <= card.rect.x + card.rect.w &&
                        my >= card.rect.y && my <= card.rect.y + card.rect.h)
                    {
                        card.beingDragged = true;
                        card.offsetX = mx - card.rect.x;
                        card.offsetY = my - card.rect.y;
                    }
                }
                // Check if back button clicked
                if (isMouseOverButton(mx, my, settingsBackButton)) {
                    currentState = MAIN_MENU;
                }
            }
        }
        else if (e.type == SDL_MOUSEBUTTONUP)
        {
            int mx = e.button.x;
            int my = e.button.y;

            if (currentState == PLAY)
            {
                // Release dragged cards from active player
                Player_UI& activePlayer = (currentPlayerIndex == 0) ? player1 : player2;

                for (int i = 0; i < (int)activePlayer.hand.size(); ++i) {
                    Cardx& card = activePlayer.hand[i];
                    if (card.beingDragged) {
                        card.beingDragged = false;

                        // Attempt to place on board
                        placeCardOnBoard(card, currentPlayerIndex, i);
                    }
                }
            }
        }
        else if (e.type == SDL_MOUSEMOTION)
        {
            if (currentState == PLAY)
            {
                int mx = e.motion.x;
                int my = e.motion.y;

                // Move any dragged card in active player's hand
                Player_UI& activePlayer = (currentPlayerIndex == 0) ? player1 : player2;
                for (auto& card : activePlayer.hand)
                {
                    if (card.beingDragged)
                    {
                        card.rect.x = mx - card.offsetX;
                        card.rect.y = my - card.offsetY;
                    }
                }
            }
        }
    }
}

// --------------------------------------------------------------------
// UPDATE (PER STATE)
// --------------------------------------------------------------------
void GameApp::update(Uint32 deltaTime)
{
    switch (currentState)
    {
    case SPLASH:
        updateSplash(deltaTime);
        break;
    case MAIN_MENU:
        updateMainMenu();
        break;
    case SETTINGS:
        updateSettingsMenu();
        break;
    case PLAY:
        updateGameBoard(deltaTime);
        break;
    case QUIT:
        running = false;
        break;
    }
}

// --------------------------------------------------------------------
// RENDER (PER STATE)
// --------------------------------------------------------------------
void GameApp::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    switch (currentState)
    {
    case SPLASH:
        renderSplash();
        break;
    case MAIN_MENU:
        renderMainMenu();
        break;
    case SETTINGS:
        renderSettingsMenu();
        break;
    case PLAY:
        renderGameBoard();
        break;
    case QUIT:
        // optional goodbye screen
        break;
    }

    SDL_RenderPresent(renderer);
}

void GameApp::renderText(SDL_Renderer* renderer, const std::string& text, TTF_Font* font, SDL_Color color, SDL_Rect* buttonRect)
{
    // Create a surface with the text rendered on it
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!textSurface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }

    // Create a texture from the surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);  // Free the surface after creating the texture

    if (!textTexture) {
        std::cerr << "Failed to create texture from text: " << SDL_GetError() << std::endl;
        return;
    }

    // Get the dimensions of the text texture
    int textWidth = 0, textHeight = 0;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    // Position the text centered within the button's rectangle
    SDL_Rect textRect = {
        buttonRect->x + (buttonRect->w - textWidth) / 2,
        buttonRect->y + (buttonRect->h - textHeight) / 2,
        textWidth,
        textHeight
    };

    // Render the text texture
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);  // Clean up the texture after rendering
}

// --------------------------------------------------------------------
// SPLASH UPDATES
// --------------------------------------------------------------------
void GameApp::updateSplash(Uint32 deltaTime)
{
    splashTimer += deltaTime;
    float halfDuration = (float)fadeDuration / 2.0f;

    if (fadeIn)
    {
        // fade in
        float ratio = (float)splashTimer / halfDuration;
        splashAlpha = (int)(255.0f * ratio);
        if (splashAlpha >= 255)
        {
            splashAlpha = 255;
            fadeIn = false;
            splashTimer = 0; // reset to start fade out
        }
    }
    else
    {
        // fade out
        float ratio = (float)splashTimer / halfDuration;
        splashAlpha = 255 - (int)(255.0f * ratio);
        if (splashAlpha <= 0)
        {
            splashAlpha = 0;
            currentState = MAIN_MENU; // go to menu
        }
    }
    SDL_SetTextureAlphaMod(splashTexture, splashAlpha);
}

// --------------------------------------------------------------------
// SPLASH RENDER
// --------------------------------------------------------------------
void GameApp::renderSplash()
{
    SDL_Rect dst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, splashTexture, nullptr, &dst);
}

// --------------------------------------------------------------------
// MAIN MENU LOGIC
// --------------------------------------------------------------------
void GameApp::updateMainMenu()
{
    int mx, my;
    SDL_GetMouseState(&mx, &my);

    playButton.hovered = isMouseOverButton(mx, my, playButton);
    settingsButton.hovered = isMouseOverButton(mx, my, settingsButton);
    quitButton.hovered = isMouseOverButton(mx, my, quitButton);
}

void GameApp::renderMainMenu()
{
    SDL_Rect dst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, mainMenuBg, nullptr, &dst);

    SDL_Color buttonColor = { 70, 70, 70, 255 };  // Dark gray for button background
    SDL_Color hoverColor = { 100, 100, 100, 255 }; // Lighter gray for hover
    SDL_Color textColor = { 255, 255, 255, 255 };  // White text

    auto drawButton = [&]( Button& btn) {
        // Draw button background
        SDL_SetRenderDrawColor(renderer,
            btn.hovered ? hoverColor.r : buttonColor.r,
            btn.hovered ? hoverColor.g : buttonColor.g,
            btn.hovered ? hoverColor.b : buttonColor.b,
            255);
        SDL_RenderFillRect(renderer, &btn.rect);

        // Draw button border
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &btn.rect);

        // Render button text
        renderText(renderer, btn.text, m_font, textColor, &btn.rect);
        };

    drawButton(playButton);
    drawButton(settingsButton);
    drawButton(quitButton);
}

// --------------------------------------------------------------------
// SETTINGS LOGIC
// --------------------------------------------------------------------
void GameApp::updateSettingsMenu()
{
    int mx, my;
    SDL_GetMouseState(&mx, &my);

    settingsButton1.hovered = isMouseOverButton(mx, my, settingsButton1);
    settingsButton2.hovered = isMouseOverButton(mx, my, settingsButton2);
    settingsButton3.hovered = isMouseOverButton(mx, my, settingsButton3);
    settingsBackButton.hovered = isMouseOverButton(mx, my, settingsBackButton);
}

void GameApp::renderSettingsMenu()
{
    SDL_Rect dst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, settingsBg, nullptr, &dst);

    // Draw buttons
    SDL_Color buttonColor = { 70, 70, 70, 255 };
    SDL_Color hoverColor = { 100, 100, 100, 255 };
    SDL_Color textColor = { 255, 255, 255, 255 };

    auto drawButton = [&]( Button& btn) {
        // Draw button background
        SDL_SetRenderDrawColor(renderer,
            btn.hovered ? hoverColor.r : buttonColor.r,
            btn.hovered ? hoverColor.g : buttonColor.g,
            btn.hovered ? hoverColor.b : buttonColor.b,
            255);
        SDL_RenderFillRect(renderer, &btn.rect);

        // Draw button border
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &btn.rect);

        // Render button text
        renderText(renderer, btn.text, m_font, textColor, &btn.rect);
        };

    drawButton(settingsButton1);
    drawButton(settingsButton2);
    drawButton(settingsButton3);
    drawButton(settingsBackButton);
}

// --------------------------------------------------------------------
// GAME BOARD LOGIC
// --------------------------------------------------------------------
void GameApp::updateGameBoard(Uint32 deltaTime)
{
    (void)deltaTime;
    // Possibly do animations, timers, etc.

    // Also check the "Back" button hover
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    settingsBackButton.hovered = isMouseOverButton(mx, my, settingsBackButton);
}

void GameApp::renderGameBoard()
{
    SDL_Rect dst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, gameBoardBg, nullptr, &dst);

    // (Optional) draw the 5×5 grid lines
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int r = 0; r <= BOARD_ROWS; ++r) {
        int y = gameBoard.boardY + r * gameBoard.cellHeight;
        SDL_RenderDrawLine(renderer, gameBoard.boardX, y,
            gameBoard.boardX + BOARD_COLS * gameBoard.cellWidth,
            y);
    }
    for (int c = 0; c <= BOARD_COLS; ++c) {
        int x = gameBoard.boardX + c * gameBoard.cellWidth;
        SDL_RenderDrawLine(renderer, x, gameBoard.boardY,
            x, gameBoard.boardY + BOARD_ROWS * gameBoard.cellHeight);
    }

    // Render active player's cards
    Player_UI& activePlayer = (currentPlayerIndex == 0) ? player1 : player2;
    for (auto& card : activePlayer.hand)
    {
        if (card.faceUp ) {
            // white for face-up
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        }
        else {
            // grey if hidden
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        }
        SDL_RenderFillRect(renderer, &card.rect);
    }

    // Render inactive player's cards (face-down?)
    Player_UI& inactivePlayer = (currentPlayerIndex == 0) ? player2 : player1;
    for (auto& card : inactivePlayer.hand)
    {
        if (card.faceUp ) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderCopy(renderer, card.texture, nullptr, &card.rect);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        }
        SDL_RenderFillRect(renderer, &card.rect);
    }

    // Render Back button
    auto drawButton = [&]( Button& btn) {
        SDL_Color buttonColor = { 70, 70, 70, 255 };
        SDL_Color hoverColor = { 100, 100, 100, 255 };
        SDL_Color textColor = { 255, 255, 255, 255 };

        SDL_SetRenderDrawColor(renderer,
            btn.hovered ? hoverColor.r : buttonColor.r,
            btn.hovered ? hoverColor.g : buttonColor.g,
            btn.hovered ? hoverColor.b : buttonColor.b,
            255);
        SDL_RenderFillRect(renderer, &btn.rect);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &btn.rect);

        renderText(renderer, btn.text, m_font, textColor, &btn.rect);
     };
    drawButton(settingsBackButton);
}

// --------------------------------------------------------------------
// START GAME (Give each player cards, etc.)
// --------------------------------------------------------------------
void GameApp::startGame()
{
    // Clear old hands
    player1.hand.clear();
    player2.hand.clear();
    if (selectedGameMode == GameMode::TRAINING) {
        // 1) Hard-code the 7 training card values
        std::vector<int> trainingValues = { 1,1,2,2,3,3,4 };

        // 2) For each player, create 7 cards with these values
        for (int i = 0; i < 7; ++i) {
            Cardx cardP1;
            cardP1.value = trainingValues[i];
            cardP1.rect = { 100 + i * 70, SCREEN_HEIGHT - 200, 60, 90 };
            cardP1.beingDragged = false;
            cardP1.faceUp = true;  // player1 is active at start
            cardP1.texture = blueCardTextures[cardP1.value - 1];
            player1.hand.push_back(cardP1);

            Cardx cardP2;
            cardP2.value = trainingValues[i];
            cardP2.rect = { 100 + i * 70, 100, 60, 90 };
            cardP2.beingDragged = false;
            cardP2.faceUp = false; // hidden if not active
            cardP2.texture = redCardTextures[cardP2.value - 1];
            player2.hand.push_back(cardP2);
        }

        // 3) Force a 3×3 board (If your code uses board init constants, just ensure ROWS=3, COLS=3)
        // Example: If you normally do something like "initBoard(ROWS, COLS)", pass 3,3 or
        // just have your initBoard() function be specifically for 3×3 in training.
        initBoard(); // you might set it up so it’s always 3×3 for training mode

    }
    else {
        // Decide how many cards per player
        int numCards = (selectedGameMode == GameMode::SEVEN_CARDS) ? 7 : 10;

        // Create dummy cards for each player
        for (int i = 0; i < numCards; ++i)
        {
            // Player 1's card
            Cardx cardP1;
            cardP1.rect = { 100 + i * 70, SCREEN_HEIGHT - 200, 60, 90 };
            cardP1.beingDragged = false;
            cardP1.offsetX = 0;
            cardP1.offsetY = 0;
            cardP1.faceUp = true; // player1 is active initially
            player1.hand.push_back(cardP1);

            // Player 2's card
            Cardx cardP2;
            cardP2.rect = { 100 + i * 70, 100, 60, 90 };
            cardP2.beingDragged = false;
            cardP2.offsetX = 0;
            cardP2.offsetY = 0;
            cardP2.faceUp = false; // hidden if not their turn
            player2.hand.push_back(cardP2);
        }
    }
    // Active player = player1
    currentPlayerIndex = 0;

    // Reset the board to empty
    initBoard();

    // Go to play state
    currentState = PLAY;
}

// --------------------------------------------------------------------
// SWITCH TURNS (Flip faceUp states, etc.)
// --------------------------------------------------------------------
void GameApp::switchTurns()
{
    // Toggle 0 <-> 1
    currentPlayerIndex = (currentPlayerIndex == 0) ? 1 : 0;

    // Face-up for active player's cards, face-down for inactive
    for (auto& c : player1.hand) {
        c.faceUp = (currentPlayerIndex == 0);
    }
    for (auto& c : player2.hand) {
        c.faceUp = (currentPlayerIndex == 1);
    }
}

// --------------------------------------------------------------------
// PLACE CARD ON BOARD
// --------------------------------------------------------------------
void GameApp::placeCardOnBoard(Cardx& card, int ownerID, int cardIndex)
{
    // Check all cells to see if we can place it
    for (int r = 0; r < BOARD_ROWS; ++r) {
        for (int c = 0; c < BOARD_COLS; ++c) {
            if (gameBoard.cells[r][c].cardOwner == -1) {
                // bounding box of this cell
                int cellX = gameBoard.boardX + c * gameBoard.cellWidth;
                int cellY = gameBoard.boardY + r * gameBoard.cellHeight;
                SDL_Rect cellRect = { cellX, cellY, gameBoard.cellWidth, gameBoard.cellHeight };

                // Check if card center is in cell
                int cardCenterX = card.rect.x + card.rect.w / 2;
                int cardCenterY = card.rect.y + card.rect.h / 2;

                if (cardCenterX >= cellRect.x && cardCenterX <= cellRect.x + cellRect.w &&
                    cardCenterY >= cellRect.y && cardCenterY <= cellRect.y + cellRect.h)
                {
                    // Snap the card to the center
                    card.rect.x = cellX + (gameBoard.cellWidth - card.rect.w) / 2;
                    card.rect.y = cellY + (gameBoard.cellHeight - card.rect.h) / 2;

                    // Mark board cell as occupied
                    gameBoard.cells[r][c].cardOwner = ownerID;
                    gameBoard.cells[r][c].cardIndex = cardIndex;

                    // Switch turns if your rule is "one card per turn"
                    switchTurns();
                    return;
                }
            }
        }
    }
}

// --------------------------------------------------------------------
// UTILITY: CHECK MOUSE OVER BUTTON
// --------------------------------------------------------------------
bool GameApp::isMouseOverButton(int mouseX, int mouseY, const Button& btn)
{
    return (mouseX >= btn.rect.x && mouseX <= btn.rect.x + btn.rect.w &&
        mouseY >= btn.rect.y && mouseY <= btn.rect.y + btn.rect.h);
}
