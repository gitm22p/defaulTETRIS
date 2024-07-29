#pragma once

#include "colors.h"

class Menu
{
public:
    Menu();
    ~Menu();
    Music menuMusic;
    bool gameMode;
    void Draw();
    void MenuKBInput();

private:
    const float buttonWidthInactive{300};
    const float buttonHeightInactive{40};
    const float buttonWidthActive{320};
    const float buttonHeightActive{80};
    void DrawAllButtons();
    void DrawExitMenu(bool activeMode);
    void DrawCreditsMenu(bool activeMode);
    void DrawExitButton(bool activeMode);
    void DrawCreditsButton(bool activeMode);
    void DrawStartButton(bool activeMode);
    void DrawLogo();
    Font font;
    Sound selectSound;
    Sound enterSound;
    Sound backSound;
    bool buttonMode;
    int selectButton;
};


