#pragma once
const int FIELD_LENGTH = 21;

// Blocks
const char CHAR_WALL = '#';
const int CHAR_GRASS = 129;
const int CHAR_SPAWN_MEL = 65;
const int CHAR_SPAWN_RAN = 66;
const int CHAR_SPAWN_TAN = 97;
const int CHAR_WEAP_SWORD = 50;
const int CHAR_FIREBALL = 207;
const int CHAR_HEAL = 466;
const int CHAR_DOOR = 294;
const int CHAR_BOMB = 195;
const int CHAR_ARROW = 50;

const int WEIGHT_WALL = 150;
const int WEIGHT_GRASS = 80;
const int WEIGHT_SPAWN_MEL = 1;
const int WEIGHT_SPAWN_RAN = 1;
const int WEIGHT_SPAWN_TAN = 1;
const int WEIGHT_WEAP_SWORD = 3;
const int WEIGHT_WEAP_FIER = 3;
const int WEIGHT_HEAL = 5;
const int WEIGHT_DOOR = 0;
const int WEIGHT_BOMB = 5;
const int WEIGHT_BOMB_SPAWN = 40;

// Entities
const int CHAR_PLAYER = 170;
const int CHAR_ENEMY_MEL = 56;
const int CHAR_ENEMY_RAN = 88;
const int CHAR_ENEMY_TAN = 120;
const int CHAR_EXPLOSION_DAMAGE = 207;

const int HP_PLAYER = 7;
const int HP_ENEMY_MEL = 1;
const int HP_ENEMY_RAN = 1;
const int HP_ENEMY_TAN = 3;

const int DAMAGE_PLAYER = 1;
const int DAMAGE_AROOW_PLAYER = 1;
const int DAMAGE_FIREBALL_PLAYER = 2;
const int DAMAGE_SWORD_PLAYER = 2;

const int DAMAGE_ENEMY_MEL = 1;
const int DAMAGE_ENEMY_RAN = 1;
const int DAMAGE_ENEMY_TAN = 1;

const int KD_ENEMY_RAN = 1;
const int KD_ENEMY_TAN = 1;

const int RADIUS_ENEMY = 7;


// Added entities
const int HEALING = 3;

const int RADIUS_BOMB = 2;
const int RADIUS_FIREBALL = 2;

const int KD_EMMITER = 2;
const int RADIUS_EMITTER = 2;

const int SCORE_PER_KILL = 100;


// UI
const int CHAR_HEART = 530;
const int CHAR_HEART_EMPTY = 532;
const int CHAR_STRONG_POTION = 499;
const int CHAR_FIREBALL_POTION = 501;
//const int CHAR_FIREBALL_POTION = 503;

//Preferences
const bool PEACEFUL = false;
const bool SPAWN_LIMIT = 15;
