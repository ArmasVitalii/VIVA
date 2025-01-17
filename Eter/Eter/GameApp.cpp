#include "GameApp.h"

GameApp::GameApp() : window(nullptr), renderer(nullptr), running(true), 
currentState(SPLASH), splashAlpha(0), splashTimer(0), fadeDuration(4500), fadeIn(true)
{
}

bool GameApp::init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) 
    {
        std::cerr << "SDL could not initialize! SDL Error: "
            << SDL_GetError() << std::endl;
        return false;
    }

    if (!IMG_Init(IMG_INIT_PNG)) 
    {
        std::cerr << "SDL_image could not initialize! SDL_image Error: "
            << IMG_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Eter Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (!window) 
    {
        std::cerr << "Window could not be created! SDL Error: "
            << SDL_GetError() << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL Error: "
            << SDL_GetError() << std::endl;
        return false;
    }

    // Load textures 
    {
        SDL_Surface* surf = IMG_Load("Intro.png");
        if (!surf)
        {
            std::cerr << "Failed to load splash image: " << IMG_GetError() << std::endl;
            return false;
        }
        splashTexture = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }
    {
        SDL_Surface* surf = IMG_Load("Menu.png");
        if (!surf) 
        {
            std::cerr << "Failed to load main_menu_bg image: " << IMG_GetError() << std::endl;
            return false;
        }
        mainMenuBg = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }
    {
        SDL_Surface* surf = IMG_Load("Menu.png");
        if (!surf)
        {
            std::cerr << "Failed to load settings_bg image: " << IMG_GetError() << std::endl;
            return false;
        }
        settingsBg = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }
    {
        SDL_Surface* surf = IMG_Load("Menu.png");
        if (!surf) 
        {
            std::cerr << "Failed to load game_board_bg image: " << IMG_GetError() << std::endl;
            return false;
        }
        gameBoardBg = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
    }

    // Set initial alpha for splash screen
    SDL_SetTextureBlendMode(splashTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(splashTexture, splashAlpha);

    initButtons();
    initCards();
    return true;
}

void GameApp::run() //Main loop runner
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

void GameApp::clean() //Clean up
{
    SDL_DestroyTexture(splashTexture);
    SDL_DestroyTexture(mainMenuBg);
    SDL_DestroyTexture(settingsBg);
    SDL_DestroyTexture(gameBoardBg);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void GameApp::initButtons() //Buttons Initialization (positions can be adjusted)
{
    // Bottom-middle alignment for 3 buttons
    int buttonWidth = 400;
    int buttonHeight = 100;
    int gap = 10;

    // Compute x-coord so that the button is centered horizontally
    int xPos = (SCREEN_WIDTH - buttonWidth) / 2;
    int yPos = SCREEN_HEIGHT - 350; // some offset from bottom

    playButton.rect = { xPos, yPos, buttonWidth, buttonHeight };
    playButton.text = "Play";
    playButton.hovered = false;

    settingsButton.rect = { xPos, yPos + (buttonHeight + gap), buttonWidth, buttonHeight };
    settingsButton.text = "Settings";
    settingsButton.hovered = false;

    quitButton.rect = { xPos, yPos + 2 * (buttonHeight + gap), buttonWidth, buttonHeight };
    quitButton.text = "Quit";
    quitButton.hovered = false;

    // For Settings Menu
    settingsButton1.rect = { 200, 200, buttonWidth, buttonHeight };
    settingsButton1.text = "Option A";
    settingsButton1.hovered = false;

    settingsButton2.rect = { 200, 310, buttonWidth, buttonHeight };
    settingsButton2.text = "Option B";
    settingsButton2.hovered = false;

    settingsButton3.rect = { 200, 420, buttonWidth, buttonHeight };
    settingsButton3.text = "Option C";
    settingsButton3.hovered = false;

    settingsBackButton.rect = { 200, 530, buttonWidth, buttonHeight };
    settingsBackButton.text = "Back";
    settingsBackButton.hovered = false;
}

void GameApp::initCards()
{
    // Let’s place 5 cards at the bottom
    int cardWidth = 60;
    int cardHeight = 90;
    int startX = 300;
    int gap = 20;
    for (int i = 0; i < 5; ++i)
    {
        Cardx card;
        card.rect = { startX + i * (cardWidth + gap), SCREEN_HEIGHT - 120, cardWidth, cardHeight };
        card.beingDragged = false;
        card.offsetX = 0;
        card.offsetY = 0;
        cards.push_back(card);
    }

    // Board position
    boardPos = { (SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT - 400) / 2 };
}

bool GameApp::isMouseOverButton(int mouseX, int mouseY, const Button& btn)
{
    return (mouseX >= btn.rect.x && mouseX <= btn.rect.x + btn.rect.w &&
        mouseY >= btn.rect.y && mouseY <= btn.rect.y + btn.rect.h);
}

Uint32 GameApp::getTick()
{
    return SDL_GetTicks();
}

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

            // Handle button clicks by state
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
            else if (currentState == SETTINGS)
            {
                if (isMouseOverButton(mx, my, settingsBackButton)) {
                    currentState = MAIN_MENU;
                }
                // Additional settings button logic can go here...
            }
            else if (currentState == PLAY) 
            {
                // Check if we clicked on any card
                for (auto& card : cards)
                {
                    if (mx >= card.rect.x && mx <= card.rect.x + card.rect.w &&
                        my >= card.rect.y && my <= card.rect.y + card.rect.h) {
                        card.beingDragged = true;
                        card.offsetX = mx - card.rect.x;
                        card.offsetY = my - card.rect.y;
                    }
                }
                if (isMouseOverButton(mx, my, settingsBackButton)) {
                    currentState = MAIN_MENU;
                }
            }
        }
        else if (e.type == SDL_MOUSEBUTTONUP) 
        {
            // Release any dragged card
            for (auto& card : cards)
            {
                card.beingDragged = false;
            }
        }
        else if (e.type == SDL_MOUSEMOTION && currentState == PLAY) 
        {
            // Move any card that’s being dragged
            int mx = e.motion.x;
            int my = e.motion.y;
            for (auto& card : cards)
            {
                if (card.beingDragged)
                {
                    card.rect.x = mx - card.offsetX;
                    card.rect.y = my - card.offsetY;
                }
            }
        }
        else if (e.type == SDL_MOUSEBUTTONUP && currentState == PLAY) {
            // For whichever player's turn it is
            Player_UI& activePlayer = (currentPlayerIndex == 0) ? player1 : player2;

            for (int i = 0; i < (int)activePlayer.hand.size(); ++i) {
                Cardx& card = activePlayer.hand[i];
                if (card.beingDragged) {
                    card.beingDragged = false;
                    // Attempt to place on board
                    placeCardOnBoard(card, currentPlayerIndex, i);
                    // If placed successfully, you might remove it from the player's hand, 
                    // or mark it as “used,” etc., depending on your rules.
                }
            }
        }

    }
}

void GameApp::update(Uint32 deltaTime) // UPDATE LOGIC (PER STATE)
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
        // We handle QUIT in event or do immediate break
        running = false;
        break;
    }
}

void GameApp::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    switch (currentState) {
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
        // Possibly render a goodbye screen or nothing
        break;
    }

    SDL_RenderPresent(renderer);
}

void GameApp::updateSplash(Uint32 deltaTime)
{
    splashTimer += deltaTime;
    // Half the fadeDuration is fade in, second half is fade out
    if (fadeIn) 
    {
        // fade in
        float ratio = (float)splashTimer / (fadeDuration / 2);
        splashAlpha = (int)(255.0f * ratio);
        if (splashAlpha >= 255)
        {
            splashAlpha = 255;
            fadeIn = false;
            // reset timer so we can fade out
            splashTimer = 0;
        }
    }
    else 
    {
        // fade out
        float ratio = (float)splashTimer / (fadeDuration / 2);
        splashAlpha = 255 - (int)(255.0f * ratio);
        if (splashAlpha <= 0) 
        {
            splashAlpha = 0;
            // Go to main menu
            currentState = MAIN_MENU;
        }
    }
    SDL_SetTextureAlphaMod(splashTexture, splashAlpha);
}

void GameApp::renderSplash()
{
    // Fill background black
    SDL_Rect dst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, splashTexture, nullptr, &dst);
}

void GameApp::renderMainMenu()
{
    // Draw main menu background
    SDL_Rect dst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, mainMenuBg, nullptr, &dst);

    // Render placeholders for buttons.  
    // In a real app, you might draw actual button textures or text.
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    auto drawBtn = [&](const Button& b) {
        SDL_SetRenderDrawColor(renderer,
            b.hovered ? 200 : 255,
            b.hovered ? 200 : 255,
            b.hovered ? 0 : 255,
            255);
        SDL_RenderFillRect(renderer, &b.rect);
        };

    drawBtn(playButton);
    drawBtn(settingsButton);
    drawBtn(quitButton);
}

void GameApp::updateMainMenu()
{
    // Could do button hover detection, animations, etc.
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    playButton.hovered = isMouseOverButton(mx, my, playButton);
    settingsButton.hovered = isMouseOverButton(mx, my, settingsButton);
    quitButton.hovered = isMouseOverButton(mx, my, quitButton);
}

void GameApp::renderSettingsMenu()
{
    SDL_Rect dst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, settingsBg, nullptr, &dst);

    // Same button rendering approach
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    auto drawBtn = [&](const Button& b) {
        SDL_SetRenderDrawColor(renderer,
            b.hovered ? 200 : 255,
            b.hovered ? 200 : 255,
            b.hovered ? 0 : 255,
            255);
        SDL_RenderFillRect(renderer, &b.rect);
        };

    drawBtn(settingsButton1);
    drawBtn(settingsButton2);
    drawBtn(settingsButton3);
    drawBtn(settingsBackButton);
}

void GameApp::updateSettingsMenu()
{
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    settingsButton1.hovered = isMouseOverButton(mx, my, settingsButton1);
    settingsButton2.hovered = isMouseOverButton(mx, my, settingsButton2);
    settingsButton3.hovered = isMouseOverButton(mx, my, settingsButton3);
    settingsBackButton.hovered = isMouseOverButton(mx, my, settingsBackButton);
}

void GameApp::renderGameBoard()
{
    // Draw game board background
    SDL_Rect boardDst = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, gameBoardBg, nullptr, &boardDst);


    // (Optional) draw grid lines
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    for (int r = 0; r <= BOARD_ROWS; ++r) {
        int y = gameBoard.boardY + r * gameBoard.cellHeight;
        SDL_RenderDrawLine(renderer, gameBoard.boardX, y,
            gameBoard.boardX + BOARD_COLS * gameBoard.cellWidth, y);
    }
    for (int c = 0; c <= BOARD_COLS; ++c) {
        int x = gameBoard.boardX + c * gameBoard.cellWidth;
        SDL_RenderDrawLine(renderer, x, gameBoard.boardY,
            x, gameBoard.boardY + BOARD_ROWS * gameBoard.cellHeight);
    }

    Player_UI& activePlayer = (currentPlayerIndex == 0) ? player1 : player2;
    for (auto& card : activePlayer.hand) {
        // faceUp = true => draw card face
        // faceUp = false => draw card back or skip
        if (card.faceUp) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
        }
        else {
            // e.g., grey if hidden
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        }
        SDL_RenderFillRect(renderer, &card.rect);
    }


    // 4) Optionally, show the inactive player’s hand face-down somewhere
    Player_UI& inactivePlayer = (currentPlayerIndex == 0) ? player2 : player1;
    for (auto& card : inactivePlayer.hand) {
        if (card.faceUp) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        }
        // If you truly want them hidden, you might skip rendering or place them off-screen
        SDL_RenderFillRect(renderer, &card.rect);
    }

    //// Render the 5 cards
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //for (auto& card : cards) {
    //    SDL_RenderFillRect(renderer, &card.rect);
    //}
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    auto drawBtn = [&](const Button& b) {
        SDL_SetRenderDrawColor(renderer,
           b.hovered ? 200 : 255,
            b.hovered ? 200 : 255,
           b.hovered ? 0 : 255,
            255);
        SDL_RenderFillRect(renderer, &b.rect);
       };

    drawBtn(settingsBackButton);

    


}

void GameApp::updateGameBoard(Uint32 deltaTime)
{
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    settingsBackButton.hovered = isMouseOverButton(mx, my, settingsBackButton);

    // Here is where you'd update game board logic, animations, etc.
    // For now, just manage card movement in event code
    (void)deltaTime; // unused in this basic sample
}

void GameApp::initBoard() {
    for (int r = 0; r < BOARD_ROWS; ++r) {
        for (int c = 0; c < BOARD_COLS; ++c) {
            gameBoard.cells[r][c].cardOwner = -1;
            gameBoard.cells[r][c].cardIndex = -1;
        }
    }

    // Decide how big each cell should be
    gameBoard.cellWidth = 80;
    gameBoard.cellHeight = 120;

    // Position the 5×5 grid in the middle of the screen
    int totalBoardWidth = BOARD_COLS * gameBoard.cellWidth;
    int totalBoardHeight = BOARD_ROWS * gameBoard.cellHeight;
    gameBoard.boardX = (SCREEN_WIDTH - totalBoardWidth) / 2;
    gameBoard.boardY = (SCREEN_HEIGHT - totalBoardHeight) / 2;
}

void GameApp::startGame() {
    player1.hand.clear();
    player2.hand.clear();

    int numCards = (selectedGameMode == GameMode::SEVEN_CARDS) ? 7 : 10;

    // Just an example: create dummy cards for each player
    for (int i = 0; i < numCards; ++i) {
        Cardx cardP1;
        cardP1.rect = { 100 + i * 70, SCREEN_HEIGHT - 200, 60, 90 };
        cardP1.beingDragged = false;
        cardP1.offsetX = 0;
        cardP1.offsetY = 0;
        cardP1.faceUp = true;  // if it’s the current player’s turn
        player1.hand.push_back(cardP1);

        Cardx cardP2;
        cardP2.rect = { 100 + i * 70, 100, 60, 90 }; // or wherever you want to place them
        cardP2.beingDragged = false;
        cardP2.offsetX = 0;
        cardP2.offsetY = 0;
        cardP2.faceUp = false; // hidden if it’s not their turn
        player2.hand.push_back(cardP2);
    }

    currentPlayerIndex = 0;  // start with player1, for example
    initBoard();            // reset the 5x5 board to empty
    // Potentially set game state
    currentState = PLAY;
}

void GameApp::switchTurns() {
    // Switch from 0 to 1, or 1 to 0
    currentPlayerIndex = (currentPlayerIndex == 0) ? 1 : 0;

    // Hide the now-inactive player's cards, show the active player's cards
    for (auto& c : player1.hand) {
        c.faceUp = (currentPlayerIndex == 0);
    }
    for (auto& c : player2.hand) {
        c.faceUp = (currentPlayerIndex == 1);
    }
}

void GameApp::placeCardOnBoard(Cardx& card, int ownerID, int cardIndex) {
    // Loop through each cell
    for (int r = 0; r < BOARD_ROWS; ++r) {
        for (int c = 0; c < BOARD_COLS; ++c) {
            // If that cell is empty
            if (gameBoard.cells[r][c].cardOwner == -1) {
                // Compute the bounding box of this cell
                int cellX = gameBoard.boardX + c * gameBoard.cellWidth;
                int cellY = gameBoard.boardY + r * gameBoard.cellHeight;
                SDL_Rect cellRect = { cellX, cellY, gameBoard.cellWidth, gameBoard.cellHeight };

                // Check if the card's center is inside the cell rect, or some overlap check
                int cardCenterX = card.rect.x + card.rect.w / 2;
                int cardCenterY = card.rect.y + card.rect.h / 2;

                if (cardCenterX >= cellRect.x && cardCenterX <= cellRect.x + cellRect.w &&
                    cardCenterY >= cellRect.y && cardCenterY <= cellRect.y + cellRect.h)
                {
                    // Snap the card to the center of this cell
                    card.rect.x = cellX + (gameBoard.cellWidth - card.rect.w) / 2;
                    card.rect.y = cellY + (gameBoard.cellHeight - card.rect.h) / 2;

                    // Mark the cell as occupied
                    gameBoard.cells[r][c].cardOwner = ownerID;
                    gameBoard.cells[r][c].cardIndex = cardIndex;

                    switchTurns();

                    return;
                }
            }
        }
    }
}