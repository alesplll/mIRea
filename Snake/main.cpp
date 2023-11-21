/// make run
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <random>

using namespace std;
using namespace sf;
#define FIELD_CELL_TYPE_NONE 0
#define FIELD_CELL_TYPE_APPLE -1
#define FIELD_CELL_TYPE_TRAP -2
#define SNAKE_DIRECTION_UP 0
#define SNAKE_DIRECTION_RIGHT 1
#define SNAKE_DIRECTION_DOWN 2
#define SNAKE_DIRECTION_LEFT 3
#define MENU_ITEM_START "START"
#define MENU_ITEM_RESUME "RESUME"
#define MENU_ITEM_QUIT "QUIT"
#define MENU_MAIN 0
#define LIVES 3

const int field_size_x = 14;
const int field_size_y = 12;
const int cell_size = 64;
const int score_bar_height = 0;
const int window_width = field_size_x * cell_size;
const int window_height = field_size_y * cell_size + score_bar_height;
struct GameState
{
    int field[field_size_y][field_size_x];
    int snake_position_x;
    int snake_position_y;
    int head_position_x;
    int head_position_y;
    int enemy_position_x;
    int enemy_position_y;
    int snake_length = 0;
    int snake_direction = SNAKE_DIRECTION_RIGHT;
    int score = 0;
    int count = 0;
    int record = 0;
};
GameState game_state;
vector<GameState> game_last_states;
bool rollback = false;
int lives = 0;
int emove = 0;
bool game_started = false;
bool game_over = false;
int game_over_timeout = 0;
bool game_paused = true;
int current_menu = MENU_MAIN;
int current_main_menu_item_index = 0;
Texture snake_texture;
Sprite snake;
Texture head_texture;
Sprite head;
Texture trap_texture;
Sprite trap;
Texture none_texture;
Sprite none;
Texture apple_texture;
Sprite apple;
Texture life_texture;
Sprite life;
Texture enemy_texture;
Sprite enemy;
Texture enemy2_texture;
Sprite enemy2;
Texture enemy3_texture;
Sprite enemy3;
Font font_score;
Text text_score;
Text text_record;
Text text_title;
Font font_game_over;
Text text_game_over;
Font font_menu;
vector<Text> text_main_menu_items;
vector<string> main_menu_items = {MENU_ITEM_START, MENU_ITEM_QUIT};

int get_random_empty_cell()
{
    int empty_cell_count = 0;
    for (int j = 0; j < field_size_y; j++)
    { // Считает количество пустых клеток
        for (int i = 0; i < field_size_x; i++)
        {
            if (game_state.field[j][i] == FIELD_CELL_TYPE_NONE)
            {
                empty_cell_count++;
            }
        }
    }
    int target_empty_cell_index = rand() % empty_cell_count;
    int empty_cell_index = 0;
    for (int j = 0; j < field_size_y; j++)
    {
        for (int i = 0; i < field_size_x; i++)
        {
            if (game_state.field[j][i] == FIELD_CELL_TYPE_NONE)
            {
                if (empty_cell_index == target_empty_cell_index)
                {
                    return j * field_size_x + i;
                }
                empty_cell_index++;
            }
        }
    }
    return -1;
}

int get_random_empty_cell_trap()
{
    int empty_cell_count = 0;
    for (int j = 2; j < field_size_y; j++)
    {
        for (int i = 0; i < field_size_x; i++)
        {
            if (game_state.field[j][i] == FIELD_CELL_TYPE_NONE)
            {
                empty_cell_count++;
            }
        }
    }
    int target_empty_cell_index = rand() % empty_cell_count;
    int empty_cell_index = 0;
    for (int j = 2; j < field_size_y; j++)
    {
        for (int i = 0; i < field_size_x; i++)
        {
            if (game_state.field[j][i] == FIELD_CELL_TYPE_NONE)
            {
                if (empty_cell_index == target_empty_cell_index)
                {
                    return j * field_size_x + i;
                }
                empty_cell_index++;
            }
        }
    }
    return -1;
}

void add_apple()
{
    int apple_pos = get_random_empty_cell();
    if (apple_pos != -1)
    {
        if (apple_pos / field_size_x < 2)
            game_state.field[2][apple_pos % field_size_x] = FIELD_CELL_TYPE_APPLE;
        else
            game_state.field[apple_pos / field_size_x][apple_pos % field_size_x] = FIELD_CELL_TYPE_APPLE;
    }
}

void add_trap()
{
    int trap_pos = get_random_empty_cell_trap();
    if (trap_pos != -2)
    {
        if (trap_pos / field_size_x < 2)
            game_state.field[2][trap_pos % field_size_x] = FIELD_CELL_TYPE_TRAP;
        else
            game_state.field[trap_pos / field_size_x][trap_pos % field_size_x] = FIELD_CELL_TYPE_TRAP;
    }
}

void clear_field()
{
    for (int j = 0; j < field_size_y; j++)
    {
        for (int i = 0; i < field_size_x; i++)
        {
            if (j >= 2)
                game_state.field[j][i] = FIELD_CELL_TYPE_NONE;
        }
    }
    for (int i = 0; i < game_state.snake_length; i++)
    {
        game_state.field[game_state.snake_position_y][game_state.snake_position_x - i] = game_state.snake_length - i;
    }
    add_apple();
    add_trap();
}

void init_game()
{
    srand(time(NULL));
    clear_field();
    snake_texture.loadFromFile("/home/glooma/Code/C++/mirea/Snake/images/snake.png");
    snake.setTexture(snake_texture);
    head_texture.loadFromFile("/home/glooma/Code/C++/mirea/Snake/images/head.png");
    head.setTexture(head_texture);
    none_texture.loadFromFile("/home/glooma/Code/C++/mirea/Snake/images/none.png");
    none.setTexture(none_texture);
    trap_texture.loadFromFile("/home/glooma/Code/C++/mirea/Snake/images/trap.png");
    trap.setTexture(trap_texture);
    apple_texture.loadFromFile("/home/glooma/Code/C++/mirea/Snake/images/apple.png");
    apple.setTexture(apple_texture);
    life_texture.loadFromFile("/home/glooma/Code/C++/mirea/Snake/images/life.png");
    life.setTexture(life_texture);
    enemy_texture.loadFromFile("/home/glooma/Code/C++/mirea/Snake/images/enemy.png");
    enemy.setTexture(enemy_texture);
    enemy2_texture.loadFromFile("/home/glooma/Code/C++/mirea/Snake/images/enemy.png");
    enemy2.setTexture(enemy_texture);
    enemy3_texture.loadFromFile("/home/glooma/Code/C++/mirea/Snake/images/enemy.png");
    enemy3.setTexture(enemy_texture);
    font_score.loadFromFile("/home/glooma/Code/C++/mirea/Snake/images/score.ttf");
    text_score.setFont(font_score);
    text_score.setCharacterSize(36);
    text_score.setFillColor(Color::Black);
    text_record.setFont(font_score);
    text_record.setCharacterSize(36);
    text_record.setFillColor(Color::Black);
    font_game_over.loadFromFile("/home/glooma/Code/C++/mirea/Snake/images/gameover.ttf");
    text_game_over.setFont(font_game_over);
    text_game_over.setString("GAME OVER");
    text_game_over.setCharacterSize(90);
    text_game_over.setFillColor(Color::Red);
    text_game_over.setPosition((window_width - text_game_over.getLocalBounds().width) / 2, (window_height - text_game_over.getLocalBounds().height + score_bar_height) / 2);
    font_menu.loadFromFile("/home/glooma/Code/C++/mirea/Snake/images/menu.ttf");
    for (int i = 0; i < main_menu_items.size(); i++)
    {
        text_main_menu_items.emplace_back(Text());
        text_main_menu_items.back().setString(main_menu_items.at(i));
        text_main_menu_items.back().setFont(font_menu);
        text_main_menu_items.back().setCharacterSize(40);
    }
}

void start_game()
{
    game_state.snake_position_x = field_size_x / 2;
    game_state.snake_position_y = field_size_y / 2;
    game_state.snake_length = 4;
    game_state.snake_direction = SNAKE_DIRECTION_RIGHT;
    game_state.score = 0;
    game_started = true;
    game_over = false;
    game_paused = false;
    lives = LIVES;
    clear_field();
}

void finish_game()
{
    game_over = true;
    game_paused = true;
    game_over_timeout = 20;
    current_main_menu_item_index = 0;
}

void snake_died()
{
    lives--;
    if (lives > 0)
    {
        rollback = true;
    }
    else
    {
        finish_game();
    }
}

void draw_field(RenderWindow &window)
{
    for (int j = 0; j < field_size_y; j++)
    {
        for (int i = 0; i < field_size_x; i++)
        {
            if (j >= 2)
                switch (game_state.field[j][i])
                {
                case FIELD_CELL_TYPE_NONE:
                    none.setPosition(float(i * cell_size), float(j * cell_size + score_bar_height));
                    window.draw(none);
                    break;
                case FIELD_CELL_TYPE_APPLE:
                    apple.setPosition(float(i * cell_size), float(j * cell_size + score_bar_height));
                    window.draw(apple);
                    break;
                case FIELD_CELL_TYPE_TRAP:
                    trap.setPosition(float(i * cell_size), float(j * cell_size + score_bar_height));
                    window.draw(trap);
                    break;
                default:
                    if (game_state.field[j][i] == game_state.snake_length)
                    {
                        float offset_x = head.getLocalBounds().width / 2;
                        float offset_y = head.getLocalBounds().height / 2;
                        head.setPosition(float(i * cell_size + offset_x), float(j * cell_size + score_bar_height + offset_y));
                        game_state.head_position_x = i * cell_size + offset_x;
                        game_state.head_position_y = j * cell_size + score_bar_height + offset_y;
                        head.setOrigin(offset_x, offset_y);

                        switch (game_state.snake_direction)
                        {
                        case SNAKE_DIRECTION_UP:
                            head.setRotation(0);
                            break;
                        case SNAKE_DIRECTION_RIGHT:
                            head.setRotation(90);
                            break;
                        case SNAKE_DIRECTION_DOWN:
                            head.setRotation(180);
                            break;
                        case SNAKE_DIRECTION_LEFT:
                            head.setRotation(-90);
                            break;
                        }
                        window.draw(head);
                    }
                    else
                    {
                        snake.setPosition(float(i * cell_size), float(j * cell_size + score_bar_height));
                        window.draw(snake);
                    }
                }
        }
    }
}

void draw_score_bar(RenderWindow &window)
{
    window.draw(text_title);

    text_score.setString("Points: " + to_string(game_state.score));
    text_score.setPosition(window_width - text_score.getLocalBounds().width - 20, 10);
    window.draw(text_score);

    for (int i = 0; i < lives; i++)
    {
        life.setPosition((window_width - LIVES * 48) / 2 + i * 48, (score_bar_height - 48) / 2 + 32);
        window.draw(life);
    }
}

void draw_record_bar(RenderWindow &window)
{
    window.draw(text_title);

    text_record.setString("Record: " + to_string(game_state.record));
    text_record.setPosition(window_width - text_record.getLocalBounds().width - 970, 10);
    window.draw(text_record);
}

void draw_main_menu(RenderWindow &window)
{
    float const menu_padding_horizontal = 200;
    float const menu_padding_vertical = 30;
    float const menu_item_interval = 20;

    float menu_item_max_width = 0;
    float current_menu_item_offset_y = -20;
    for (int i = 0; i < text_main_menu_items.size(); i++)
    {
        if (main_menu_items.at(i) == MENU_ITEM_START)
        {
            if (!game_over && game_started)
            {
                text_main_menu_items.at(i).setString(MENU_ITEM_RESUME);
            }
            else
            {
                text_main_menu_items.at(i).setString(MENU_ITEM_START);
            }
        }
        text_main_menu_items.at(i).setPosition(0, current_menu_item_offset_y);
        text_main_menu_items.at(i).setFillColor(
            current_main_menu_item_index == i ? Color(224, 224, 224) : Color(128, 128, 128));
        current_menu_item_offset_y += text_main_menu_items.at(i).getLocalBounds().height + menu_item_interval;
        menu_item_max_width = max(menu_item_max_width, text_main_menu_items.at(i).getLocalBounds().width);
    }

    float const menu_width = menu_item_max_width + menu_padding_horizontal * 2;
    float const menu_height = current_menu_item_offset_y - menu_item_interval + menu_padding_vertical * 2;

    float const menu_position_x = (window_width - menu_width) / 2;
    float const menu_position_y = (window_height - menu_height) / 2 - 150;

    RectangleShape menu_rect(Vector2f(menu_width, menu_height));
    menu_rect.setPosition(menu_position_x, menu_position_y);
    menu_rect.setFillColor(Color(0, 0, 0, 224));
    window.draw(menu_rect);

    for (int i = 0; i < text_main_menu_items.size(); i++)
    {
        text_main_menu_items.at(i).move(menu_position_x + menu_padding_horizontal,
                                        menu_position_y + menu_padding_vertical);
        window.draw(text_main_menu_items.at(i));
    }
}

void grow_snake()
{
    for (int j = 0; j < field_size_y; j++)
    {
        for (int i = 0; i < field_size_x; i++)
        {
            if (game_state.field[j][i] > FIELD_CELL_TYPE_NONE)
            {
                game_state.field[j][i]++;
            }
        }
    }
}

void degrow_snake()
{
    for (int j = 0; j < field_size_y; j++)
    {
        for (int i = 0; i < field_size_x; i++)
        {
            if (game_state.field[j][i] > FIELD_CELL_TYPE_NONE)
            {
                game_state.field[j][i]--;
            }
        }
    }
}

void make_move()
{
    game_last_states.push_back(game_state);
    if (game_last_states.size() > 10)
    {
        game_last_states.erase(game_last_states.begin());
    }
    switch (game_state.snake_direction)
    {
    case SNAKE_DIRECTION_UP:
        game_state.snake_position_y--;
        if (game_state.snake_position_y < 2)
        {
            game_state.snake_position_y = field_size_y - 1;
        }
        break;
    case SNAKE_DIRECTION_RIGHT:
        game_state.snake_position_x++;
        if (game_state.snake_position_x > field_size_x - 1)
        {
            game_state.snake_position_x = 0;
        }
        break;
    case SNAKE_DIRECTION_DOWN:
        game_state.snake_position_y++;
        if (game_state.snake_position_y > field_size_y - 1)
        {
            game_state.snake_position_y = 2;
        }
        break;
    case SNAKE_DIRECTION_LEFT:
        game_state.snake_position_x--;
        if (game_state.snake_position_x < 0)
        {
            game_state.snake_position_x = field_size_x - 1;
        }
        break;
    }

    if (game_state.field[game_state.snake_position_y][game_state.snake_position_x] != FIELD_CELL_TYPE_NONE)
    {
        switch (game_state.field[game_state.snake_position_y][game_state.snake_position_x])
        {
        case FIELD_CELL_TYPE_APPLE:

            game_state.snake_length++;
            game_state.score++;
            grow_snake();
            add_apple();
            game_state.count += 1;
            if (game_state.score > game_state.record)
            {
                game_state.record = game_state.score;
            }
            if (game_state.count % 2 == 0)
            {
                add_trap();
            }

            break;
        case FIELD_CELL_TYPE_TRAP:

            game_state.snake_length--;
            game_state.score--;
            if (game_state.score == -4)
            {
                lives = 1;
                snake_died();
            }
            degrow_snake();
            add_trap();
            break;

        default:
            if (game_state.field[game_state.snake_position_y][game_state.snake_position_x] > 1)
            {

                snake_died();
            }
        }
    }

    if (!game_over && !rollback)
    {
        for (int j = 0; j < field_size_y; j++)
        {
            for (int i = 0; i < field_size_x; i++)
            {
                if (game_state.field[j][i] > FIELD_CELL_TYPE_NONE)
                {
                    game_state.field[j][i]--;
                }
            }
        }
        game_state.field[game_state.snake_position_y][game_state.snake_position_x] = game_state.snake_length;
    }
}

int main()
{
    init_game();
    RenderWindow window(VideoMode(window_width, window_height), "Snake", Style::Close);
    vector<int> snake_direction_queue;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                if (game_paused)
                {
                    if (game_over_timeout == 0)
                    {
                        if (current_menu == MENU_MAIN)
                        {
                            switch (event.key.code)
                            {
                            case Keyboard::Up:
                                current_main_menu_item_index--;
                                if (current_main_menu_item_index < 0)
                                {
                                    current_main_menu_item_index = text_main_menu_items.size() - 1;
                                }
                                break;
                            case Keyboard::Down:
                                current_main_menu_item_index++;
                                if (current_main_menu_item_index > text_main_menu_items.size() - 1)
                                {
                                    current_main_menu_item_index = 0;
                                }
                                break;
                            case Keyboard::Enter:

                                if (main_menu_items.at(current_main_menu_item_index) == MENU_ITEM_START)
                                {
                                    if (!game_over && game_started)
                                    {
                                        game_paused = false;
                                    }
                                    else
                                    {
                                        start_game();
                                    }
                                }

                                if (main_menu_items.at(current_main_menu_item_index) == MENU_ITEM_QUIT)
                                {
                                    window.close();
                                }
                                break;
                            case Keyboard::Escape:

                                if (!game_over && game_started)
                                {
                                    game_paused = false;
                                }
                                break;
                            }
                        }
                    }
                    else
                    {
                        game_over_timeout = 0;
                    }
                }
                else
                {
                    int snake_direction_last = snake_direction_queue.empty() ? game_state.snake_direction
                                                                             : snake_direction_queue.at(0);
                    switch (event.key.code)
                    {
                    case Keyboard::Up:
                        if (snake_direction_last != SNAKE_DIRECTION_UP &&
                            snake_direction_last != SNAKE_DIRECTION_DOWN)
                        {
                            if (snake_direction_queue.size() < 2)
                            {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_UP);
                            }
                        }
                        break;
                    case Keyboard::Right:
                        if (snake_direction_last != SNAKE_DIRECTION_RIGHT &&
                            snake_direction_last != SNAKE_DIRECTION_LEFT)
                        {
                            if (snake_direction_queue.size() < 2)
                            {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_RIGHT);
                            }
                        }
                        break;
                    case Keyboard::Down:
                        if (snake_direction_last != SNAKE_DIRECTION_DOWN &&
                            snake_direction_last != SNAKE_DIRECTION_UP)
                        {
                            if (snake_direction_queue.size() < 2)
                            {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_DOWN);
                            }
                        }
                        break;
                    case Keyboard::Left:
                        if (snake_direction_last != SNAKE_DIRECTION_LEFT &&
                            snake_direction_last != SNAKE_DIRECTION_RIGHT)
                        {
                            if (snake_direction_queue.size() < 2)
                            {
                                snake_direction_queue.insert(snake_direction_queue.begin(), SNAKE_DIRECTION_LEFT);
                            }
                        }
                        break;
                    case Keyboard::Escape:
                        game_paused = true;
                        break;
                    }
                }
            }
        }

        if (!snake_direction_queue.empty())
        {
            game_state.snake_direction = snake_direction_queue.back();
            snake_direction_queue.pop_back();
        }
        if (!game_paused)
        {
            if (!rollback)
            {
                make_move();
            }
            else
            {
                if (!game_last_states.empty())
                {
                    game_state = game_last_states.back();
                    game_last_states.pop_back();
                }
                else
                {
                    rollback = false;
                }
            }
        }
        window.clear(Color(38, 84, 124));
        draw_field(window);
        draw_score_bar(window);
        draw_record_bar(window);
        if (game_over)
        {
            window.draw(text_game_over);
            if (game_over_timeout > 0)
            {
                game_over_timeout--;
            }
        }
        if (game_paused && game_over_timeout == 0)
        {
            switch (current_menu)
            {
            case MENU_MAIN:
                draw_main_menu(window);
                break;
            }
        }
        window.display();
        sleep(milliseconds(100 - game_state.score * 2));
    }

    return 0;
}