#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

enum class MenuState {
    START_GAME,
        NEW_GAME,
            EASY,
            NORMAL,
            HARD,
            BACK_TO_MENU_FROM_NEW_GAME,
        CONTINUE,
        BACK_TO_MENU_FROM_START_GAME,

    OPTIONS,
        MUSIC_VOL,
        SFX_VOL,
        FULSCREEN,
        BACK_TO_MENU_FROM_OPTIONS,

    CREDITS,
    QUIT
};

#endif // MENU_STATE_HPP
