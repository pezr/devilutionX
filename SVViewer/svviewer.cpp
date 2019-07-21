#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// #include <ncurses.h>

#include "diablo.h"
#include "../3rdParty/Storm/Source/storm.h"
#include "../DiabloUI/diabloui.h"


#define TRUE true
#define FALSE false
#define COL_GREY 0x4

const char* fontPath = "Anonymous Pro.ttf";

void SVV_PlrStringXY(int x, int y, int width, const std::string& str, char color);
std::string i2s(int a);

int const TTEXTS = 42;
SDL_Texture* textures[TTEXTS];
SDL_Rect rects[TTEXTS];
int ctext = 0;
SDL_Color colors[5] = {
    { 255, 255, 255 } // COL_WHITE
    , { 49, 126, 205 } // COL_BLUE
    , { 186, 49, 53 } // COL_RED
    , { 205, 127, 50 } // COL_GOLD
    , { 180, 180, 180 } // COL_GREY
};

int fontSize = 18;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;


/************** Diablo ***************/

using namespace dvl;

void TxtDrawChr()
{
    char col = COL_WHITE;
    char chrstr[64];
    int pc, mindam, maxdam, x, y, w;

    std::string str = "";

    x = 3, y = 1, w = 14; str = plr[myplr]._pName; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    x = 22; y = 1; w = 14; str = ClassStrTbl[plr[myplr]._pClass]; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);


    x = 5; y = 3; w = 5; str = "Level"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    x += 6; y = 3; w = 6; str = i2s(plr[myplr]._pLevel); col = COL_GREY;
    SVV_PlrStringXY(x, y, w, str, col);


    x = 22; y = 3; w = 10; str = "Experience"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    x += 11; y = 3; w = 9; str = i2s(plr[myplr]._pExperience); col = COL_GREY;
    SVV_PlrStringXY(x, y, w, str, col);

    x = 22; y = 5; w = 10; str = "Next level"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    if (plr[myplr]._pLevel == MAXCHARLEVEL - 1) {
        str = "None";
        col = COL_GOLD;
    } else {
        str = i2s(ExpLvlsTbl[plr[myplr]._pLevel]);
        col = COL_GREY;
    }
    x += 11; y = 5; w = 9;
    SVV_PlrStringXY(x, y, w, str, col);

    x = 22; y = 8; w = 10; str = "Gold"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    x += 11; y = 8; w = 8; str = i2s(plr[myplr]._pGold); col = COL_GREY;
    SVV_PlrStringXY(x, y, w, str, col);



    x = 10; y = 7; w = 4; str = "Base"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    x = 17; y = 7; w = 3; str = "Now"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);

    x = 1; y = 9; w = 9; str = "Strength"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    col = COL_GREY;
    if (MaxStats[plr[myplr]._pClass][ATTRIB_STR] == plr[myplr]._pBaseStr)
        col = COL_GOLD;
    x += 10; y = 9; w = 3; str = i2s(plr[myplr]._pBaseStr);
    SVV_PlrStringXY(x, y, w, str, col);

    col = COL_GREY;
    if (plr[myplr]._pStrength > plr[myplr]._pBaseStr)
        col = COL_BLUE;
    if (plr[myplr]._pStrength < plr[myplr]._pBaseStr)
        col = COL_RED;
    x += 6; y = 9; w = 3; str = i2s(plr[myplr]._pStrength);
    SVV_PlrStringXY(x, y, w, str, col);


    x = 1; y = 11; w = 9; str = "Magic"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    col = COL_GREY;
    if (MaxStats[plr[myplr]._pClass][ATTRIB_MAG] == plr[myplr]._pBaseMag)
        col = COL_GOLD;
    x += 10; y = 11; w = 3; str = i2s(plr[myplr]._pBaseMag);
    SVV_PlrStringXY(x, y, w, str, col);

    col = COL_GREY;
    if (plr[myplr]._pMagic > plr[myplr]._pBaseMag)
        col = COL_BLUE;
    if (plr[myplr]._pMagic < plr[myplr]._pBaseMag)
        col = COL_RED;
    x += 6; y = 11; w = 3; str = i2s(plr[myplr]._pMagic);
    SVV_PlrStringXY(x, y, w, str, col);


    x = 1; y = 13; w = 9; str = "Dexterity"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    col = COL_GREY;
    if (MaxStats[plr[myplr]._pClass][ATTRIB_DEX] == plr[myplr]._pBaseDex)
        col = COL_GOLD;
    x += 10; y = 13; w = 3; str = i2s(plr[myplr]._pBaseDex);
    SVV_PlrStringXY(x, y, w, str, col);

    col = COL_GREY;
    if (plr[myplr]._pDexterity > plr[myplr]._pBaseDex)
        col = COL_BLUE;
    if (plr[myplr]._pDexterity < plr[myplr]._pBaseDex)
        col = COL_RED;
    x += 6; y = 13; w = 3; str = i2s(plr[myplr]._pDexterity);
    SVV_PlrStringXY(x, y, w, str, col);


    x = 1; y = 15; w = 9; str = "Vitality"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    col = COL_GREY;
    if (MaxStats[plr[myplr]._pClass][ATTRIB_VIT] == plr[myplr]._pBaseVit)
        col = COL_GOLD;
    x += 10; y = 15; w = 3; str = i2s(plr[myplr]._pBaseVit);
    SVV_PlrStringXY(x, y, w, str, col);

    col = COL_GREY;
    if (plr[myplr]._pVitality > plr[myplr]._pBaseVit)
        col = COL_BLUE;
    if (plr[myplr]._pVitality < plr[myplr]._pBaseVit)
        col = COL_RED;
    x += 6; y = 15; w = 3; str = i2s(plr[myplr]._pVitality);
    SVV_PlrStringXY(x, y, w, str, col);


    x = 1; y = 18; w = 9; str = "Life"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    col = plr[myplr]._pMaxHP <= plr[myplr]._pMaxHPBase ? COL_GREY : COL_BLUE;
    x += 10; y = 18; w = 3; str = i2s(plr[myplr]._pMaxHP >> 6);
    SVV_PlrStringXY(x, y, w, str, col);
    if (plr[myplr]._pHitPoints != plr[myplr]._pMaxHP)
        col = COL_RED;
    x += 6; y = 18; w = 3; str = i2s(plr[myplr]._pHitPoints >> 6);
    SVV_PlrStringXY(x, y, w, str, col);

    x = 1; y = 20; w = 9; str = "Mana"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    col = plr[myplr]._pMaxMana <= plr[myplr]._pMaxManaBase ? COL_GREY : COL_BLUE;
    x += 10; y = 20; w = 3; str = i2s(plr[myplr]._pMaxMana >> 6);
    SVV_PlrStringXY(x, y, w, str, col);
    if (plr[myplr]._pMana != plr[myplr]._pMaxMana)
        col = COL_RED;
    x += 6; y = 20; w = 3; str = i2s(plr[myplr]._pMana >> 6);
    SVV_PlrStringXY(x, y, w, str, col);



    x = 23; y = 10; w = 14; str = "Armor Class"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    col = COL_GREY;
    if (plr[myplr]._pIBonusAC > 0)
        col = COL_BLUE;
    if (plr[myplr]._pIBonusAC < 0)
        col = COL_RED;
    x += 14; y = 10; w = 5;
    str = i2s(plr[myplr]._pIBonusAC + plr[myplr]._pIAC + plr[myplr]._pDexterity / 5);
    SVV_PlrStringXY(x, y, w, str, col);

    x = 23; y = 12; w = 14; str = "To Hit"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    col = COL_GREY;
    if (plr[myplr]._pIBonusToHit > 0)
        col = COL_BLUE;
    if (plr[myplr]._pIBonusToHit < 0)
        col = COL_RED;
    x += 14; y = 12; w = 5;
    str = i2s((plr[myplr]._pDexterity >> 1) + plr[myplr]._pIBonusToHit + 50) + "%";
    SVV_PlrStringXY(x, y, w, str, col);

    x = 23; y = 14; w = 14; str = "Damage"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    col = COL_GREY;
    if (plr[myplr]._pIBonusDam > 0)
        col = COL_BLUE;
    if (plr[myplr]._pIBonusDam < 0)
        col = COL_RED;
    mindam = plr[myplr]._pIMinDam;
    mindam += plr[myplr]._pIBonusDam * mindam / 100;
    mindam += plr[myplr]._pIBonusDamMod;
    if (plr[myplr].InvBody[INVLOC_HAND_LEFT]._itype == ITYPE_BOW) {
        if (plr[myplr]._pClass == PC_ROGUE)
            mindam += plr[myplr]._pDamageMod;
        else
            mindam += plr[myplr]._pDamageMod >> 1;
    } else {
        mindam += plr[myplr]._pDamageMod;
    }
    maxdam = plr[myplr]._pIMaxDam;
    maxdam += plr[myplr]._pIBonusDam * maxdam / 100;
    maxdam += plr[myplr]._pIBonusDamMod;
    if (plr[myplr].InvBody[INVLOC_HAND_LEFT]._itype == ITYPE_BOW) {
        if (plr[myplr]._pClass == PC_ROGUE)
            maxdam += plr[myplr]._pDamageMod;
        else
            maxdam += plr[myplr]._pDamageMod >> 1;
    } else {
        maxdam += plr[myplr]._pDamageMod;
    }
    x += 14; y = 14; w = 5; str = i2s(mindam) + "-" + i2s(maxdam);
    SVV_PlrStringXY(x, y, w, str, col);


    x = 23; y = 16; w = 14; str = "Resist Magic"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    col = plr[myplr]._pMagResist == 0 ? COL_GREY : COL_BLUE;
    if (plr[myplr]._pMagResist < 75) {
        str = i2s(plr[myplr]._pMagResist) + "%";
    } else {
        col = COL_GOLD;
        str = "MAX";
    }
    x += 14; y = 16; w = 5;
    SVV_PlrStringXY(x, y, w, str, col);

    x = 23; y = 18; w = 14; str = "Resist Fire"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    col = plr[myplr]._pFireResist == 0 ? COL_GREY : COL_BLUE;
    if (plr[myplr]._pFireResist < 75) {
        str = i2s(plr[myplr]._pFireResist) + "%";
    } else {
        col = COL_GOLD;
        str = "MAX";
    }
    x += 14; y = 18; w = 5;
    SVV_PlrStringXY(x, y, w, str, col);

    x = 23; y = 20; w = 14; str = "Resist Lgtning"; col = COL_WHITE;
    SVV_PlrStringXY(x, y, w, str, col);
    col = plr[myplr]._pLghtResist == 0 ? COL_GREY : COL_BLUE;
    if (plr[myplr]._pLghtResist < 75) {
        str = i2s(plr[myplr]._pLghtResist) + "%";
    } else {
        col = COL_GOLD;
        str = "MAX";
    }
    x += 14; y = 20; w = 5;
    SVV_PlrStringXY(x, y, w, str, col);

}

void svviewer()
{
    DWORD i, save_num;
    BOOL showFixedMsg;

    showFixedMsg = TRUE;
    for (i = 0; i < MAX_CHARACTERS; i++) {
        PkPlayerStruct pkplr;
        HANDLE archive = pfile_open_save_archive(&showFixedMsg, i);
        if (archive) {
            if (pfile_read_hero(archive, &pkplr)) {
                // _uiheroinfo uihero;
                // strcpy(hero_names[i], pkplr.pName);
                UnPackPlayer(&pkplr, 0, FALSE);
            }
            pfile_SFileCloseArchive(archive);
        }
    }

    TxtDrawChr();
}

std::string i2s(int a)
{
    std::ostringstream temp;
    temp << a;
    return temp.str();
}

/************** SDL ***************/

void SVV_PlrStringXY(int x, int y, int w, const std::string& strv, char color)
{

    if(ctext >= TTEXTS) return;
    std::ostringstream temp;
    temp << std::setw(w) << strv;

    const char* str = temp.str().c_str();

    // attron(COLOR_PAIR(color));
    // mvprintw(y, x, temp.str().c_str());
    // attroff(COLOR_PAIR(color));

    // int lineH = TTF_FontLineSkip(gFont);
    int lineH = TTF_FontHeight(gFont);
    int chW = fontSize - 7;
    int tW = 0;
    int tH = 0;
    TTF_SizeText(gFont, str, &tW, &tH);

    SDL_Texture* textu = textures[ctext];

    SDL_DestroyTexture( textu );
    textu = NULL;

    SDL_Surface* surf = TTF_RenderText_Blended( gFont, str, colors[color] );
    if( surf == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        // Create texture from surface pixels
        textures[ctext] = textu = SDL_CreateTextureFromSurface( gRenderer, surf );
        if( textu == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }

        // Get rid of old surface
        SDL_FreeSurface( surf );
        rects[ctext].x = x * chW;
        rects[ctext].y = y * lineH;
        rects[ctext].w = tW;
        rects[ctext].h = lineH;
    }
    ctext++;
}

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow(
                "Char Editor"
                , SDL_WINDOWPOS_CENTERED
                , SDL_WINDOWPOS_CENTERED
                , SCREEN_WIDTH
                , SCREEN_HEIGHT
                , SDL_WINDOW_SHOWN
                );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer(
                    gWindow
                    , -1
                    , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                    );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                 //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }

                // init colors
                // SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Open the font
    gFont = TTF_OpenFont( fontPath, fontSize );
    if( gFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        // TTF_SetFontOutline(gFont, 1);
    }

    return success;
}

void close()
{

    // destroy textures
    for (int i = 0; i < TTEXTS; i++) {
        SDL_DestroyTexture( textures[i] );
        textures[i] = NULL;
    }


    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
}

static std::string build_cmdline(int argc, char **argv)
{
    std::string str;
    for (int i = 1; i < argc; i++) {
        if (i != 1) {
            str += ' ';
        }
        str += argv[i];
    }
    return str;
}

int main( int argc, char* argv[] )
{
    auto cmdline = build_cmdline(argc, argv);
    // initscr();
    // start_color();
    // init_color(COLOR_CYAN, 900, 900, 900);
    // init_pair(dvl::COL_RED, COLOR_RED, COLOR_BLACK);
    // init_pair(dvl::COL_GOLD, COLOR_YELLOW, COLOR_BLACK);
    // init_pair(dvl::COL_BLUE, COLOR_BLUE, COLOR_BLACK);
    // init_pair(COL_GREY, COLOR_CYAN, COLOR_BLACK);
    // init_pair(dvl::COL_WHITE, COLOR_WHITE, COLOR_BLACK);
    // svviewer();
    // refresh();
    // getch();
    // endwin();

    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0x0, 0x0, 0x0, 0xFF );
                SDL_RenderClear( gRenderer );

                if(ctext < TTEXTS) svviewer();
                //Render textures
                for (int i = 0; i < TTEXTS; i++) {
                    SDL_RenderCopy(gRenderer, textures[i], NULL, &rects[i]);
                }

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
