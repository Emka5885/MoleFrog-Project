#pragma once

enum direction { left, right };

constexpr const int WIDTH = 1080;
constexpr const int HEIGHT = 720;

constexpr const int TILE_SIZE = 60;

constexpr const int GRAVITY = 15;

constexpr const int MAX_HEALTH = 3;
constexpr const int PLAYER_SPEED = 4;

constexpr const int ENTITY_SPEED = 2;

constexpr const int GHOST_SIZE = 80;
constexpr const int CANDY_SIZE = 50;

constexpr const int SPAWN_RATE = 45;

constexpr const char* OUTLINE_FONT = "outline_font";
constexpr const char* SHADOW_FONT = "shadow_font";
constexpr const char* FONT = "font";
constexpr const char* FONT_PATH = "res/SharpAxe.ttf";

constexpr const char* ICON_IMAGE_PATH = "res/ghost.png";
constexpr const char* TILESETS_IMAGE = "tilesets";
constexpr const char* TILESETS_IMAGE_PATH = "res/moleFrogTilesets.png";
constexpr const char* MOLE_IMAGE = "mole";
constexpr const char* MOLE_IMAGE_PATH = "res/mole.png";
constexpr const char* HEART_IMAGE = "hearts";
constexpr const char* HEART_IMAGE_PATH = "res/hearts.png";
constexpr const char* CANDY_IMAGE = "candy";
constexpr const char* CANDY_IMAGE_PATH = "res/candy.png";
constexpr const char* GHOST_IMAGE = "ghost";
constexpr const char* GHOST_IMAGE_PATH = "res/ghost.png";

extern int score;
extern int numberOfHearts;