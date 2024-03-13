#pragma once
#include <vector>
#include <iostream>
#include <curses.h>
#include <cstdio>
#include <SFML/Graphics.hpp>

#include "Object.h"
#include "Pool.h"
#include "Player.h"
#include "Arrow.h"
#include "NullEntity.h"
#include "DamageEntity.h"
#include "BombEntity.h"
#include "EnemyMel.h"
#include "EnemyRan.h"
#include "EnemyTan.h"
#include "Sword.h"
#include "HealingEntity.h"
#include "Scroll.h"

#include "Block.h"

#include "Terrain.h"
#include "config.h"
#include "TileSource.h"




class Game {
    std::vector<std::unique_ptr<Block>> blocks;
    std::shared_ptr<Terrain> field;

public:
    Game() { 
      main_cycle();
    }

    void loadGame(int seed = rand(), int x = 0, int y = 0,
                                               int score = 0, int scrolls = 0,
                                               int swings = 0, int steps = 0) { 
      Pool().objects.clear();

      blocks.clear();
      PlayerLog().Logs.clear();
      PlayerLog().Logs.push_back("Traveller lost");

      player.reset(new Player(x, y));
      field.reset(new Terrain(seed, x, y));

      Pool().objects.push_back(player);
      lvlSeed = seed;

      while (!field->getCell(player->x, player->y).isWalkable) {
        player->setPosition(player->x + 1, player->y);
      }

      this->steps = steps;
      player->score = score;
      player->fireballs = scrolls;
      //player->fireballs = -1;
      player->swingsOfSword = swings;
    }

    void save_game() {
      FILE* save;
      fopen_s(&save, "save", "w");
      fprintf_s(save, "%d\n%d\n%d\n%d\n%d\n%d\n%d", lvlSeed, player->x, player->y,
                Player().score, Player().fireballs, Player().swingsOfSword,
                steps);
      fclose(save);
    }

    void main_cycle() {
      sf::RenderWindow window(sf::VideoMode(672, 700), "The Lost Traveller");
      window.setFramerateLimit(60);

      sf::Event event;
      string sceneTag = "menu";
      TileMap map;
      TileMap entities;
      TileMap ui;
      map.scale(2.f, 2.f);
      entities.scale(2.f, 2.f);
      ui.scale(2.f, 2.f);
      sf::Font font;
      font.loadFromFile("PixelFont.ttf");

      // Menu 
      sf::Text title;
      vector<sf::Text> leaderTable;
      title.setFont(font);
      title.setString("THE LOST TRAVELER");
      title.setCharacterSize(24);
      title.setFillColor(sf::Color::White);
      title.setStyle(sf::Text::Bold);

      FILE *lead;
      if (!fopen_s(&lead, "lead", "r")) {
        int n;
        fscanf_s(lead, "%d", &n);
        for (int i = 0, tScore; i < n; ++i) {
          fscanf_s(lead, "%d", &tScore);
          leads.push_back(tScore);
        }
        fclose(lead);

        sort(leads.begin(), leads.end(), greater<int>());
        int below = 10;
        for (auto i : leads) {
          leaderTable.push_back(sf::Text());
          leaderTable.back().setFont(font);
          leaderTable.back().setString(to_string(i));

          leaderTable.back().setCharacterSize(22);
          leaderTable.back().setFillColor(sf::Color::White);
          leaderTable.back().setPosition(0, (below += 22));

          window.draw(leaderTable.back());
        }
      }

      // Game
      sf::Text upperUI;
      upperUI.setFont(font);
      upperUI.setString("Score: " + to_string(player->score) + "      " +
                      to_string(player->swingsOfSword) + "/" +
                      to_string(player->fireballs));
      upperUI.setCharacterSize(24);
      upperUI.setFillColor(sf::Color::White);
      upperUI.setStyle(sf::Text::Bold);
      upperUI.setPosition(300, 0);
      sf::Text logText;
      logText.setFont(font);
      logText.setCharacterSize(22);
      logText.setFillColor(sf::Color::White);
      logText.setStyle(sf::Text::Bold);
      logText.setPosition(0, 672);

      while (window.isOpen()) {
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed) window.close();
          if (event.type == sf::Event::KeyPressed) {
            if (sceneTag == "menu") {
              if (event.key.code == sf::Keyboard::Space) {
                  // Начало игры
                sceneTag = "game";
                srand(time(NULL));
                loadGame();
                map.load("Tileset.png", sf::Vector2u(16, 16),
                    &setLevel(field->getTerrain(player->x, player->y)),
                         FIELD_LENGTH, FIELD_LENGTH);

                entities.load(
                    "Tileset.png", sf::Vector2u(16, 16),
                              &setEntities(),
                    FIELD_LENGTH, FIELD_LENGTH);
                ui.load("Tileset.png", sf::Vector2u(16, 16), &setUI(),
                        HP_PLAYER, 1);

              } else if (event.key.code == sf::Keyboard::F6) {
                // Загрузка
                sceneTag = "game";
                FILE* save;
                if (!fopen_s(&save, "save", "r")) {
                  int seed, x, y, score, scrolls, swings, steps;
                  fscanf_s(save, "%d\n%d\n%d\n%d\n%d\n%d\n%d", &seed, &x, &y,
                           &score, &scrolls, &swings, &steps);
                  loadGame(seed, x, y, score, scrolls, swings, steps);
                  fclose(save);
                  map.load("Tileset.png", sf::Vector2u(16, 16),
                           &setLevel(field->getTerrain(player->x, player->y)),
                           FIELD_LENGTH, FIELD_LENGTH);
                  entities.load("Tileset.png", sf::Vector2u(16, 16),
                                &setEntities(), FIELD_LENGTH,
                                FIELD_LENGTH);
                  ui.load("Tileset.png", sf::Vector2u(16, 16), &setUI(),
                          HP_PLAYER, 1);
                } else {
                  srand(time(NULL));
                  loadGame();
                  map.load("Tileset.png", sf::Vector2u(16, 16),
                           &setLevel(field->getTerrain(player->x, player->y)),
                           FIELD_LENGTH, FIELD_LENGTH);
                  entities.load("Tileset.png", sf::Vector2u(16, 16),
                                &setEntities(), FIELD_LENGTH,
                                FIELD_LENGTH);
                  ui.load("Tileset.png", sf::Vector2u(16, 16), &setUI(),
                          HP_PLAYER, 1);
                }
              }
            } else if (sceneTag == "game") {
                // Ход игрока
              player->isShot = false;
              if (event.key.code == sf::Keyboard::W) {
                playerDirection = {0, -1};
              } else if (event.key.code == sf::Keyboard::S) {
                playerDirection = {0, 1};
              } else if (event.key.code == sf::Keyboard::A) {
                playerDirection = {-1, 0};
              } else if (event.key.code == sf::Keyboard::D) {
                playerDirection = {1, 0};
              } else if (event.key.code == sf::Keyboard::Space) {
                player->isShot = true;
              } else if (event.key.code == sf::Keyboard::F5) {
                  save_game();
              }



              // Update
              if (player->isShot) {
                if (field
                        ->getCell(-(player->x - playerDirection.first),
                                  -(player->y - playerDirection.second))
                        .isWalkable) {
                  if (player->fireballs) {
                    --player->fireballs;
                    Pool().objects.push_back(make_shared<BombEntity>(
                        player->x - playerDirection.first,
                        player->y - playerDirection.second, playerDirection,
                        CHAR_FIREBALL, RADIUS_FIREBALL, 10));
                  } else {
                    Pool().objects.push_back(make_shared<Arrow>(
                        player->x - playerDirection.first,
                        player->y - playerDirection.second, playerDirection));
                  }
                }
              } else {
                if (field
                        ->getCell(-(player->x - playerDirection.first),
                                  -(player->y - playerDirection.second))
                        .isWalkable) {
                  shared_ptr<Object> entityCell =
                      getEntityCell({player->x - playerDirection.first,
                                     player->y - playerDirection.second});
                  if (entityCell->tag.empty()) {
                    player->x -= playerDirection.first;
                    player->y -= playerDirection.second;
                  } else {
                    if (player->swingsOfSword) {
                      --player->swingsOfSword;
                      if (entityCell->tag == "BombEntity") {
                        explosion({entityCell->x, entityCell->y},
                                  RADIUS_FIREBALL, DAMAGE_FIREBALL_PLAYER);
                      }
                      entityCell->setHealth(entityCell->hp -
                                            DAMAGE_SWORD_PLAYER);
                    } else {
                      if (entityCell->tag == "BombEntity") {
                        explosion({entityCell->x, entityCell->y},
                                  RADIUS_FIREBALL, DAMAGE_FIREBALL_PLAYER);
                      }
                      entityCell->setHealth(entityCell->hp - player->damage);
                    }
                    if (entityCell->isIrrelevant) {
                      player->score += SCORE_PER_KILL;
                    }
                    player->setHealth(player->hp - entityCell->damage);
                  }
                  
                }
                SetEntityMap();
                map.load("Tileset.png", sf::Vector2u(16, 16),
                         &setLevel(field->getTerrain(player->x, player->y)),
                         FIELD_LENGTH, FIELD_LENGTH);
                entities.load("Tileset.png", sf::Vector2u(16, 16),
                              &setEntities(), FIELD_LENGTH,
                              FIELD_LENGTH);
                ui.load("Tileset.png", sf::Vector2u(16, 16), &setUI(),
                        HP_PLAYER, 1);
              }
              SetEntityMap();
              map.load("Tileset.png", sf::Vector2u(16, 16),
                       &setLevel(field->getTerrain(player->x, player->y)),
                       FIELD_LENGTH, FIELD_LENGTH);
              entities.load("Tileset.png", sf::Vector2u(16, 16), &setEntities(),
                            FIELD_LENGTH, FIELD_LENGTH);
              ui.load("Tileset.png", sf::Vector2u(16, 16), &setUI(), HP_PLAYER,
                      1);


              // Collisions (or not) of Objects
              for (auto entity : Pool().objects) {
                if (entity == nullptr) {
                  entity = make_shared<NullEntity>();
                }
                if (!(entity->dir.first || entity->dir.second) || entity->isIrrelevant) {
                  continue;
                }
                if (field
                        ->getCell(-(entity->x - entity->dir.first),
                                  -(entity->y - entity->dir.second))
                        .isWalkable) {
                  shared_ptr<Object> entityCell =
                      getEntityCell({(entity->x - entity->dir.first),
                                     (entity->y - entity->dir.second)});

                  if (entityCell->tag.empty()) {
                    entity->move();
                  } else {
                    if (entity->tag == "BombEntity") {
                      explosion({entity->x, entity->y}, RADIUS_FIREBALL,
                                DAMAGE_FIREBALL_PLAYER);
                    } else if (entityCell->tag == "BombEntity") {
                      explosion({entityCell->x, entityCell->y}, RADIUS_FIREBALL,
                                DAMAGE_FIREBALL_PLAYER);
                    }
                    printf("%s meet %s\n", entity->tag.c_str(),
                           entityCell->tag.c_str());

                    entityCell->setHealth(entityCell->hp - entity->damage);
                    entity->setHealth(entity->hp - entityCell->damage);
                  }
                } else {
                  if (entity->tag == "BombEntity") {
                    explosion({entity->x, entity->y}, RADIUS_FIREBALL, DAMAGE_FIREBALL_PLAYER);
                  }
                  entity->setHealth(entity->hp);
                }

                // Update after entity
                SetEntityMap();
              }
              Pool().objects.erase(
                  remove_if(Pool().objects.begin(), Pool().objects.end(),
                            [](const shared_ptr<Object>& sptr) {
                              return sptr->isIrrelevant;
                            }),
                  Pool().objects.end());
              upperUI.setString("Score: " + to_string(player->score) +
                                "      " + to_string(player->swingsOfSword) +
                                "/" + to_string(player->fireballs));
              if (!player->hp) {
                sceneTag = "gameover";
                leads.push_back(player->score);
                sort(leads.begin(), leads.end(), greater<int>());
                leaderTable.clear();
                int below = 10;
                for (auto i : leads) {
                  leaderTable.push_back(sf::Text());
                  leaderTable.back().setFont(font);
                  leaderTable.back().setString(to_string(i));

                  leaderTable.back().setCharacterSize(22);
                  leaderTable.back().setFillColor(sf::Color::White);
                  leaderTable.back().setPosition(0, (below += 22));
                }
              } else {
                ++steps;
              }
              // End of Update
            } else if (sceneTag == "gameover") {
              sceneTag = "menu";
              leads.push_back(player->score);
              FILE* lead;
              fopen_s(&lead, "lead", "w");
              fprintf_s(lead, "%d\n", leads.size());

              for (auto i : leads) {
                fprintf_s(lead, "%d\n", i); 
              }
              fclose(lead);
            }
            
            if (event.key.code == sf::Keyboard::Escape) {
              if (sceneTag == "menu") {
                window.close();
              } else {
                sceneTag = "menu";
              }
            }
                
          }
        }

        //необходимые действия по отрисовке
        
        if (sceneTag == "menu") {
          window.clear();
          window.draw(title);
          for (auto& leaderStr : leaderTable) {
            window.draw(leaderStr);   
          }
        } else if (sceneTag == "game") {
          window.clear();
          window.draw(map);
          window.draw(entities);
          window.draw(ui);
          window.draw(upperUI);

          logText.setString(
              PlayerLog().Logs.back());
          
          window.draw(logText);

        } else if (sceneTag == "gameover") {
          window.clear();
          window.draw(map);
          window.draw(entities);
          window.draw(ui);
          window.draw(upperUI);

          sf::Text gameOverText;
          gameOverText.setFont(font);
          gameOverText.setString(
              "GAME OVER\nScore: " + to_string(player->score) +
              "\nSteps: " + to_string(steps));
          gameOverText.setCharacterSize(36);
          gameOverText.setFillColor(sf::Color::White);
          gameOverText.setStyle(sf::Text::Bold);
          gameOverText.setPosition(200, 200);
          window.draw(gameOverText);
        }        
        window.display();
      }
    }

    int& setLevel(vector<vector<Block>> terrain) { 
      level.clear();
      for (auto& line : terrain) {
        for (auto& cell : line) {
          level.push_back(cell.sym);
          if (cell.tag[1] == 'p') {
            setEmitter({(-player->y + (level.size() - 1) / FIELD_LENGTH -
                         FIELD_LENGTH / 2),
                        (-player->x + (level.size() - 1) % FIELD_LENGTH -
                         FIELD_LENGTH / 2)},
                       cell.tag[8] == 'M'   ? "EnemyMel"
                       : cell.tag[8] == 'R' ? "EnemyRan"
                                            : "EnemyTan");
          }
        }
      }
      return level.front();
    }

    int& setEntities() {
      if (entityMap.empty()) {
        SetEntityMap();
      }
      movedLvl.clear();
      for (auto line : entityMap) {
        for (auto entity : line) {
          movedLvl.push_back(entity->tag.empty() ? 0 : entity->sym);
        }
      }
      movedLvl[FIELD_LENGTH * FIELD_LENGTH / 2] = player->sym;
      return movedLvl.front();
    }

    vector<vector<shared_ptr<Object>>> SetEntityMap() { 
      entityCounter = 0;
      entityMap.assign(
          FIELD_LENGTH,
          vector<shared_ptr<Object>>(FIELD_LENGTH, make_shared<NullEntity>()));

      //Pool().objects.erase(
      //    remove_if(Pool().objects.begin(), Pool().objects.end(),
      //              [](const shared_ptr<Object>& sptr) {
      //                return sptr->isIrrelevant;
      //              }),
      //    Pool().objects.end());

      if (!Pool().objects.empty()) {
        for (auto& entity : Pool().objects) {
          if (entity->sym) {
            int deltaX = FIELD_LENGTH / 2 + entity->x - player->x;
            int deltaY = FIELD_LENGTH / 2 + entity->y - player->y;

            if (max(deltaX, deltaY) > FIELD_LENGTH * 2 ||
                min(deltaX, deltaY) < -FIELD_LENGTH) {
              entity->isIrrelevant = true;
            }

            if (deltaX >= 0 && deltaX < FIELD_LENGTH && deltaY >= 0 &&
                deltaY < FIELD_LENGTH) {
              entityMap[FIELD_LENGTH - 1 - deltaY][FIELD_LENGTH - 1 - deltaX] =
                  entity;
              ++entityCounter;
            }
          }
        }
      }
      return entityMap;
    }

    shared_ptr<Object> getEntityCell(pair<int, int> pos) { 
      if (entityMap.empty()) {
        SetEntityMap();
      }
      int deltaX = FIELD_LENGTH / 2 + pos.first - player->x;
      int deltaY = FIELD_LENGTH / 2 + pos.second - player->y;

      if (deltaX >= 0 && deltaX < FIELD_LENGTH && deltaY >= 0 &&
          deltaY < FIELD_LENGTH) {

        return entityMap[FIELD_LENGTH - 1 - deltaY][FIELD_LENGTH - 1 - deltaX];
      }
      return make_shared<NullEntity>();
    }

    int& setUI() { 
      uiLvl.clear();
      for (int i = 0; i < player->hp; ++i) {
        uiLvl.push_back(CHAR_HEART);
      }
      for (int i = player->hp; i < HP_PLAYER; ++i) {
        uiLvl.push_back(CHAR_HEART_EMPTY);
      }
      return uiLvl.front();
    }

    void explosion(pair<int, int> center, int rad, int damage) { 
      for (int i = center.first - rad; i <= center.first + rad; ++i) {
        for (int ii = center.second - rad; ii <= center.second + rad; ++ii) {
          shared_ptr<Object> unluckyEntity = getEntityCell({i, ii});
          Pool().objects.push_back(make_shared<DamageEntity>(i, ii));
          if (!unluckyEntity->tag.empty()) {
            unluckyEntity->setHealth(unluckyEntity->hp - damage);
          }
        }
      }
    }

    void setEmitter(pair<int, int> center, string tag = "EnemyMel",
                    int radius = RADIUS_EMITTER) {
      if (PEACEFUL || entityCounter > SPAWN_LIMIT) {
        return;
      }
      
      for (int i = center.first - radius; i <= center.first + radius; ++i) {
        for (int ii = center.second - radius; ii <= center.second + radius;
             ++ii) {
          if (field->getCell(ii, i).isWalkable) {
            if (!(rand() % 9)) {
              ++entityCounter;
              if (tag == "EnemyMel") {
                Pool().objects.push_back(
                    make_shared<EnemyMel>(-ii, -i, player));
                return;
              } else if (tag == "EnemyRan") {
                Pool().objects.push_back(
                    make_shared<EnemyRan>(-ii, -i, player));
                return;
              } else if (tag == "EnemyTan") {
                Pool().objects.push_back(
                    make_shared<EnemyTan>(-ii, -i, player));
                return;
              }
            } else if (!(rand() % WEIGHT_BOMB_SPAWN)) {
              Pool().objects.push_back(make_shared<BombEntity>(-ii, -i));
              return;
            }
          }
        }
      }
        
    }


 private: 
  pair<int, int> playerDirection = {0, 0};
  shared_ptr<Player> player;
  int steps;
  int lvlSeed;
  int entityCounter = 0;

  vector<int> leads;
  vector<int> level;
  vector<int> movedLvl;
  vector<int> uiLvl;

  vector<vector<shared_ptr<Object>>> entityMap;
};
