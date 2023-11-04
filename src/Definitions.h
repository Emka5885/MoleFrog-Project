#pragma once

enum direction { left, right };

constexpr const int WIDTH = 1080;
constexpr const int HEIGHT = 720;

constexpr const int TILE_SIZE = 60;

constexpr const int GRAVITY = 15;

constexpr const int MAX_HEALTH = 3;
constexpr const int PLAYER_SPEED = 4;

constexpr const int GHOST_SPEED = 5;
constexpr const int SWEET_SPEED = 6;

constexpr const int ENTITY_SIZE = 80;

constexpr const char* FONT = "font";
constexpr const char* FONT_PATH = "res/MilkyNice.ttf";

constexpr const char* TILESETS_IMAGE = "tilesets";
constexpr const char* TILESETS_IMAGE_PATH = "res/moleFrogTilesets.png";
constexpr const char* MOLE_IMAGE = "mole";
constexpr const char* MOLE_IMAGE_PATH = "res/mole.png";
constexpr const char* HEART_IMAGE = "hearts";
constexpr const char* HEART_IMAGE_PATH = "res/hearts.png";