#pragma once
#include <string>
#include <vector>
#include <curses.h>
#include <algorithm>

#include "Object.h"
#include "Block.h"
#include "config.h"


using namespace std;
class Render {
public:
  Render() { initscr();
    }

    void upper_interface(int hp, int score, int steps, int swing, int scrolls) {
      for (int i = 0; i < hp; i++) {
        printw("O");
      }
      printw("      %d", score);
      printw("      %d", steps);
      printw("      %d/%d", swing, scrolls);
      printw("\n");
    }

    void lower_interface() { 
      if (PlayerLog().Logs.size()) {
        string tmpData = PlayerLog().Logs.back();
        printw("%s", tmpData.c_str());
      } else {
        printw("%s", "-Traveller lost");
      } 
    }

    void draw_map(vector<vector<Block>> terrain,
             vector<shared_ptr<Object>> objects, pair<int, int> pos) {
      vector<string> outfield(FIELD_LENGTH);
      for (auto& line : terrain) {
        string str;
        for (auto& sym : line) {
          str += sym.sym;
        }
        outfield.push_back(str);
        
      }

      for (auto& entity : objects) {
        if (entity->sym) {
          int deltaX = FIELD_LENGTH / 2 + entity->x - pos.first;
          int deltaY = FIELD_LENGTH / 2 + entity->y - pos.second;

          if (deltaX >= 0 && deltaX < outfield.size() && deltaY >= 0 &&
              deltaY < outfield.at(deltaX).size()) {
            outfield.at(deltaX).at(deltaY) = entity->sym;
          }
        } 
      }

      int legendLine = 0;
      for (auto& line : outfield) {
        string outputLine = string(line.begin(), line.end());
        if (legendLine < 15) {
          outputLine += "||" + mainLegend[legendLine].first +
                        "::" + mainLegend[legendLine].second;
        }
        legendLine++;
        printw("%d%s\n", legendLine, outputLine.c_str());
      }
    }

    void draw(int hp, int steps, vector<vector<Block>> terrain,
              vector<shared_ptr<Object>> objects, pair<int, int> pos) {
      erase();
      upper_interface(hp, Player().score, steps, Player().swingsOfSword,
                      Player().fireballs);
      draw_map(terrain, objects, pos);
      lower_interface();
    }

    void draw(string title, int score, int steps, vector<int> leads) { 
      erase();
      printw(title.c_str());
      printw("\n");
      sort(leads.begin(), leads.end(), greater<int>());
      for (auto& lead : leads) {
        printw("%d\n", lead);
      }
    };

 private:
  pair<string, char> mainLegend[15] = {{"Player", CHAR_PLAYER},
                                         {"Militiaman", CHAR_ENEMY_MEL},
                                         {"Ranger", CHAR_ENEMY_RAN},
                                         {"Knight", CHAR_ENEMY_TAN},
                                         {"Wall", CHAR_WALL},
                                         {"Grass", CHAR_GRASS},
                                         {"Militia tent", CHAR_SPAWN_MEL},
                                         {"The Pathfinders' Tent", CHAR_SPAWN_RAN},
                                         {"Knight's Fortress", CHAR_SPAWN_TAN},
                                         {"Sword", CHAR_WEAP_SWORD},
                                         {"Fire's scroll", CHAR_WEAP_FIER},
                                         {"Treatment Potion", CHAR_HEAL},
                                         {"Door", CHAR_DOOR},
                                         {"Bomb", CHAR_BOMB},
                                         {"Arrow", CHAR_ARROW}};
};
