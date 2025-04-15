//
// Created by JoonHo Son on 2025. 4. 15..
//

#include "Game.h"

Game::Game() {
    window = nullptr;
    renderer = nullptr;
}

Game::~Game() {}

bool Game::Init() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());

        return false;
    }

    if (!SDL_CreateWindowAndRenderer("Pong Example - Rembound.com", 800, 600, SDL_EVENT_WINDOW_SHOWN, &window, &renderer)) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());

        return false;
    }

    lastTick = SDL_GetTicks();
    fpsTick = lastTick;
    fps = 0;
    frameCount = 0;

    return true;
}

void Game::Clean() const {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Game::Run() {
    board = new Board(renderer);
    ball = new Ball(renderer);

    paddle.push_back(new Paddle(renderer));
    paddle.push_back(new Paddle(renderer));

    NewGame();

    while (true) {
        SDL_Event event;

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)) {
                break;
            }
        }

        unsigned int currentTick = SDL_GetTicks();
        float delta = (currentTick - lastTick) / 1000.0f;

        if (currentTick - fpsTick >= FPS_DELAY) {
            fps = frameCount * (1000.0f / (currentTick - fpsTick));
            fpsTick = currentTick;
            frameCount = 0;
            char buf[100];

            snprintf(buf, 100, "Pong (fps: %u)", fps);
            SDL_SetWindowTitle(window, buf);
        } else {
            frameCount++;
        }

        lastTick = currentTick;

        Update(delta);
        Render(delta);
    }

    delete board;
    delete ball;

    for (unsigned int i = 0; i < paddle.size(); i++) {
        delete paddle[i];
    }

    paddle.clear();

    Clean();
    SDL_Quit();
}

void Game::NewGame() {
    SetPaddleY(0, board->height / 2 - paddle[0]->height / 2);
    SetPaddleY(1, board->height / 2 - paddle[1]->height / 2);

    paddle[0]->x = 12;
    paddle[1]->x = board->width - paddle[1]->width / 12;

    ball->x = board->width / 2 - ball->width / 2;
    ball->y = board->height / 2 - ball->height / 2;

    ball->SetDirection(1, -1);
}

void Game::Update(const float delta) {
    float mX, mY;

    SDL_GetMouseState(&mX, &mY);
    SetPaddleY(0, mY - paddle[0]->height / 2.0f);
    CheckCollisions();
    AI(delta);

    board->Update(delta);
    ball->Update(delta);

    for (unsigned int i = 0; i < paddle.size(); i++) {
        paddle[i]->Update(delta);
    }
}

void Game::SetPaddleY(const int index, const float y) {
    float newY;

    if (y < board->boundBottom) {
        newY = board->boundTop;

    } else if (y + paddle[index]->height > board->boundBottom) {
        newY = board->boundBottom - paddle[index]->height;
    } else {
        newY = y;
    }

    paddle[index]->y = newY;
}

void Game::CheckCollisions() {
    // Top and bottom
    if (ball->y < board->boundTop) {
        ball->y = board->boundTop;
        ball->SetDirection(ball->dirX, -1 * ball->dirY);
    } else if (ball->y + ball->height > board->boundBottom) {
        ball->y = board->boundBottom - ball->height;
        ;
        ball->SetDirection(ball->dirX, -1 * ball->dirY);
    }

    // Left paddle collisions
    if (ball->Collides(paddle[0])) {
        ball->x = paddle[0]->x - ball->width;
        ball->SetDirection(-1, GetReflection(0, (ball->y + ball->height / 2) - paddle[0]->y));
    }

    // Right paddle collisions
    if (ball->Collides(paddle[1])) {
        ball->x = paddle[1]->x - ball->width;
        ball->SetDirection(-1, GetReflection(1, (ball->y + ball->height / 2) - paddle[1]->y));
    }

    // Check if ball is off the screen
    if (ball->x + ball->width <= board->x) {
        ball->x = board->width / 2 - ball->width / 2 + 250;
        ball->y = board->height / 2 - ball->height / 2;

        ball->SetDirection(-1, -1);
    } else if (ball->x >= board->x + board->width) {
        ball->x = board->width / 2 - ball->width / 2 - 250;
        ball->y = board->height / 2 - ball->height / 2;

        ball->SetDirection(1, -1);
    }
}

float Game::GetReflection(int index, float hitY) {
    if (hitY < 0) {
        hitY = 0;
    } else if (hitY > paddle[index]->height) {
        hitY = paddle[index]->height;
    }

    hitY -= paddle[index]->height / 2.0f;

    return 2.0f * (hitY / (paddle[index]->height / 2.0f));
}

void Game::AI(float delta) {
    float dY = AI_SPEED * delta;

    if (ball->x > board->width / 2 && ball->dirX > 0) {
        if (paddle[1]->y + paddle[1]->height / 2 < ball->y + ball->height / 2 - dY) {
            SetPaddleY(1, paddle[1]->y + dY);
        } else if (paddle[1]->y + paddle[1]->height / 2 > board->height / 2 + dY) {
            SetPaddleY(1, paddle[1]->y - dY);
        }
    } else {
        if (paddle[1]->y + paddle[1]->height / 2 < board->height / 2 - dY) {
            SetPaddleY(1, paddle[1]->y + dY);
        } else if (paddle[1]->y + paddle[1]->height / 2 > board->height / 2 + dY) {
            SetPaddleY(1, paddle[1]->y - dY);
        }
    }
}

void Game::Render(float delta) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    board->Render(delta);
    ball->Render(delta);

    for (unsigned int i = 0; i < paddle.size(); i++) {
        paddle[i]->Render(delta);
    }

    SDL_RenderPresent(renderer);
}
