#ifndef LEVEL_H
#define LEVEL_H
#include <cstddef>
#include "raylib.h"
#include <string>
#include <vector>

class Level {
public:
    Level(const size_t rows, const size_t columns, char* data)
    : rows(rows), columns(columns), data(data) {};
    Level() : rows{0}, columns{0}, data(nullptr) {};

    [[nodiscard]] size_t get_rows() const {
        return rows;
    }
    void set_rows(size_t rows) {
        this->rows = rows;
    }
    [[nodiscard]] size_t get_columns() const {
        return columns;
    }
    void set_columns(size_t columns) {
        this->columns = columns;
    }
    [[nodiscard]] const char* get_data() const {
        return data;
    }
    void set_data(char *data) {
        this->data = data;
    }
    static char& get_level_cell(size_t row, size_t column);

private:
    size_t rows;
    size_t columns;
    char *data = nullptr;
};

class LevelController {
public:
    [[nodiscard]] std::vector<Level> get_levels() const {
        return LEVELS;
    }
    void set_levels(const std::vector<Level> &levels) {
        LEVELS = levels;
    }
    Level &get_current_level() {
        return current_level;
    }
    [[nodiscard]] char * get_current_level_data() const {
        return current_level_data;
    }
    static LevelController &get_instance() {
        static LevelController instance;
        return instance;
    };
    LevelController(const LevelController&) = delete;
    LevelController operator=(const LevelController&) = delete;
    LevelController(LevelController&&) = delete;
    LevelController operator=(LevelController&&) = delete;

    bool is_inside_level(int row, int column);
    bool is_colliding(Vector2 pos, char look_for);
    char& get_collider(Vector2 pos, char look_for);
    static void reset_level_index();
    void load_level(int offset = 0);

    static void unload_level();

    void set_level_cell(size_t row,  size_t column, char chr);
    void set_current_level(const Level &current_level);
    Level parseLevelRLE(const std::string& rleData);
    std::vector<Level> loadLevelsFromFile(const std::string& filename);

private:
    LevelController() = default;
    ~LevelController() = default;
    Level current_level;
    char* current_level_data;
    std::vector<Level> LEVELS;
};

/*
#include "globals.h"

bool is_inside_level(int row, int column) {
    if (row < 0 || row >= current_level.rows) return false;
    if (column < 0 || column >= current_level.columns) return false;
    return true;
}

bool is_colliding(Vector2 pos, char look_for) {
    Rectangle entity_hitbox = {pos.x, pos.y, 1.0f, 1.0f};

    // Scan the adjacent area in the level to look for a match in collision
    for (int row = pos.y - 1; row < pos.y + 1; ++row) {
        for (int column = pos.x - 1; column < pos.x + 1; ++column) {
            // Check if the cell is out-of-bounds
            if (!is_inside_level(row, column)) continue;
            if (get_level_cell(row, column) == look_for) {
                Rectangle block_hitbox = {(float) column, (float) row, 1.0f, 1.0f};
                if (CheckCollisionRecs(entity_hitbox, block_hitbox)) {
                    return true;
                }
            }
        }
    }
    return false;
}

char& get_collider(Vector2 pos, char look_for) {
    // Like is_colliding(), except returns a reference to the colliding object
    Rectangle player_hitbox = {pos.x, pos.y, 1.0f, 1.0f};

    for (int row = pos.y - 1; row < pos.y + 1; ++row) {
        for (int column = pos.x - 1; column < pos.x + 1; ++column) {
            // Check if the cell is out-of-bounds
            if (!is_inside_level(row, column)) continue;
            if (get_level_cell(row, column) == look_for) {
                Rectangle block_hitbox = {(float) column, (float) row, 1.0f, 1.0f};
                if (CheckCollisionRecs(player_hitbox, block_hitbox)) {
                    return get_level_cell(row, column);
                }
            }
        }
    }

    // If failed, get an approximation
    return get_level_cell(pos.x, pos.y);;
}

void reset_level_index() {
    level_index = 0;
}

void load_level(int offset) {
    level_index += offset;

    // Win logic
    if (level_index >= LEVEL_COUNT) {
        game_state = VICTORY_STATE;
        create_victory_menu_background();
        level_index = 0;
        return;
    }

    // Level duplication
    size_t rows = LEVELS[level_index].rows;
    size_t columns = LEVELS[level_index].columns;
    current_level_data = new char[rows*columns];

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            current_level_data[row * columns + column] = LEVELS[level_index].data[row * columns + column];
        }
    }

    current_level = {rows, columns, current_level_data};

    // Instantiate entities
    Player::get_instance().spawn_player();
    EnemiesController::get_instance().spawn_enemies();

    // Calculate positioning and sizes
    derive_graphics_metrics_from_loaded_level();

    // Reset the timer
    timer = MAX_LEVEL_TIME;
}

void unload_level() {
    delete[] current_level_data;
}

// Getters and setters
char& get_level_cell(size_t row, size_t column) {
    return current_level.data[row * current_level.columns + column];
}

void set_level_cell(size_t row, size_t column, char chr) {
    get_level_cell(row, column) = chr;
}
*/
#endif //LEVEL_H
