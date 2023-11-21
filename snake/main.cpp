#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <random>

using namespace std;
using namespace sf;

/// Field cell types
#define FIELD_CELL_TYPE_NONE 0
#define FIELD_CELL_TYPE_APPLE -1

/// Snake directions
#define SNAKE_DIRECTION_UP 0
#define SNAKE_DIRECTION_RIGHT 1
#define SNAKE_DIRECTION_DOWN 2
#define SNAKE_DIRECTION_LEFT 3

/// Menu items
#define MENU_ITEM_START "START"
#define MENU_ITEM_RESUME "RESUME"
#define MENU_ITEM_QUIT "QUIT"

/// Menu types
#define MENU_MAIN 0

/// Initial lives count
#define LIVES 5

/// Dimensions and sizes
const int field_size_x = 15;
const int field_size_y = 15;
const int cell_size = 59;
const int score_bar_height = -110;
const int score_bar_width = 180;
const int window_width = field_size_x * cell_size + score_bar_width + 10;
const int window_height = field_size_y * cell_size + score_bar_height + 10;

/// Game state structure
struct GameState
{
    int field[field_size_y][field_size_x];
    int snake_position_x;
    int snake_position_y;
    int head_position_x;
    int head_position_y;
    int snake_length = 0;
    int snake_direction = SNAKE_DIRECTION_RIGHT;
    int score = 0;
    int count = 0;
    int record = 0;
};
GameState game_state;

/// Vector to store game states for rollback
vector<GameState> game_last_states;

/// Flag for rollback state
bool rollback = false;

/// Initial lives count
int lives = 0;

/// Game flags
bool game_started = false;
bool game_over = false;
int game_over_timeout = 0;
bool game_paused = true;

/// Current menu type
int current_menu = MENU_MAIN;

/// Index of the selected item in the main menu
int current_main_menu_item_index = 0;

/// Textures and sprites for game elements
Texture logo_textures;
Sprite logo;
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

/// Fonts and text objects for displaying score, record, game over message, and menu items
Font font_score;
Text text_score;
Text text_record;
Text text_title;
Font font_game_over;
Text text_game_over;
Font font_menu;
vector<Text> text_main_menu_items;
vector<string> main_menu_items = {MENU_ITEM_START, MENU_ITEM_QUIT};

/// Function to get the index of a random empty cell in the game field
int get_random_empty_cell()
{
    /// Count the number of empty cells
    int empty_cell_count = 0;
    for (int j = 0; j < field_size_y; j++)
    {
        for (int i = 0; i < field_size_x; i++)
        {
            if (game_state.field[j][i] == FIELD_CELL_TYPE_NONE)
            {
                empty_cell_count++;
            }
        }
    }

    /// Generate a random target index within the range of empty cells
    int target_empty_cell_index = rand() % empty_cell_count;

    /// Find the cell with the selected index and return its linear index
    int empty_cell_index = 0;
    for (int j = 0; j < field_size_y; j++)
    {
        for (int i = 0; i < field_size_x; i++)
        {
            if (game_state.field[j][i] == FIELD_CELL_TYPE_NONE)
            {
                if (empty_cell_index == target_empty_cell_index)
                {
                    /// Convert 2D index to linear index
                    return j * field_size_x + i;
                }
                empty_cell_index++;
            }
        }
    }

    /// Return -1 if no empty cell is found (should not reach this point under normal conditions)
    return -1;
}

/// Function to add an apple to a random empty cell in the game field
void add_apple()
{
    /// Get the linear index of a random empty cell
    int apple_pos = get_random_empty_cell();

    /// Check if a valid empty cell is found
    if (apple_pos != -1)
    {
        /// Calculate the 2D index from the linear index
        int row = apple_pos / field_size_x;
        int col = apple_pos % field_size_x;

        /// Place the apple in the game field
        if (row < 2)
            game_state.field[2][col] = FIELD_CELL_TYPE_APPLE;
        else
            game_state.field[row][col] = FIELD_CELL_TYPE_APPLE;
    }
}

/// Function to clear the game field, place the snake, and add an apple
void clear_field()
{
    /// Clear the game field, excluding the top two rows
    for (int j = 0; j < field_size_y; j++)
    {
        for (int i = 0; i < field_size_x; i++)
        {
            if (j >= 2)
                game_state.field[j][i] = FIELD_CELL_TYPE_NONE;
        }
    }

    /// Place the snake on the field
    for (int i = 0; i < game_state.snake_length; i++)
    {
        /// Fill the cells with values representing the snake length
        game_state.field[game_state.snake_position_y][game_state.snake_position_x - i] = game_state.snake_length - i;
    }

    /// Add a new apple to the field
    add_apple();
}

/// Function to initialize the game state and load textures;
void init_game()
{
    /// Seed the random number generator with the current time
    srand(time(NULL));

    /// Clear the game field, place the snake, and add an apple
    clear_field();

    /// Load textures for various game elements
    logo_textures.loadFromFile("/home/glooma/Code/C++/mirea/snake/images/logo.png");
    logo.setTexture(logo_textures);

    snake_texture.loadFromFile("/home/glooma/Code/C++/mirea/snake/images/snake.png");
    snake.setTexture(snake_texture);

    head_texture.loadFromFile("/home/glooma/Code/C++/mirea/snake/images/head.png");
    head.setTexture(head_texture);

    none_texture.loadFromFile("/home/glooma/Code/C++/mirea/snake/images/none.png");
    none.setTexture(none_texture);

    apple_texture.loadFromFile("/home/glooma/Code/C++/mirea/snake/images/apple.png");
    apple.setTexture(apple_texture);

    life_texture.loadFromFile("/home/glooma/Code/C++/mirea/snake/images/life.png");
    life.setTexture(life_texture);

    /// Load font for score display
    font_score.loadFromFile("/home/glooma/Code/C++/mirea/snake/images/score.ttf");
    text_score.setFont(font_score);
    text_score.setCharacterSize(36);
    text_score.setFillColor(Color(255, 231, 173));

    /// Set up text object for displaying the record
    text_record.setFont(font_score);
    text_record.setCharacterSize(36);
    text_record.setFillColor(Color(255, 231, 173));

    /// Load font for the "Game Over" message
    font_game_over.loadFromFile("/home/glooma/Code/C++/mirea/snake/images/gameover.ttf");
    text_game_over.setFont(font_game_over);
    text_game_over.setString("GAME OVER");
    text_game_over.setCharacterSize(90);
    text_game_over.setFillColor(Color::Red);
    text_game_over.setPosition((window_width - text_game_over.getLocalBounds().width) / 2, (window_height - text_game_over.getLocalBounds().height + score_bar_height) / 2);

    /// Initialize menu items
    for (int i = 0; i < main_menu_items.size(); i++)
    {
        text_main_menu_items.emplace_back(Text());
        text_main_menu_items.back().setString(main_menu_items.at(i));
        text_main_menu_items.back().setFont(font_score);
        text_main_menu_items.back().setCharacterSize(40);
    }
}

/// Function to start a new game
void start_game()
{
    /// Set initial values for the game state
    game_state.snake_position_x = field_size_x / 2;
    game_state.snake_position_y = field_size_y / 2;
    game_state.snake_length = 3;
    game_state.snake_direction = SNAKE_DIRECTION_RIGHT;
    game_state.score = 0;

    /// Set game flags
    game_started = true;
    game_over = false;
    game_paused = false;

    /// Set initial lives count
    lives = LIVES;

    /// Clear the game field, place the snake, and add an apple
    clear_field();
}

/// Function to finish the current game
void finish_game()
{
    /// Set game flags to indicate game over and paused state
    game_over = true;
    game_paused = true;

    /// Set a timeout for the "Game Over" message display
    game_over_timeout = 20;

    /// Reset the current main menu item index
    current_main_menu_item_index = 0;
}

/// Function to handle the snake's death
void snake_died()
{
    /// Decrement the remaining lives
    lives--;

    /// Check if there are remaining lives
    if (lives > 0)
    {
        /// Set the rollback flag to true for reverting to the previous game state
        rollback = true;
    }
    else
    {
        /// If no lives left, finish the game
        finish_game();
    }
}

/// Function to draw the game field
void draw_field(RenderWindow &window)
{
    /// Loop through each cell in the game field
    for (int j = 0; j < field_size_y; j++)
    {
        for (int i = 0; i < field_size_x; i++)
        {
            /// Exclude the top two rows from drawing
            if (j >= 2)
            {
                /// Switch statement to draw different elements based on the cell type
                switch (game_state.field[j][i])
                {
                case FIELD_CELL_TYPE_NONE:
                    /// Draw an empty cell
                    none.setPosition(float(i * cell_size + score_bar_width), float(j * cell_size + score_bar_height));
                    window.draw(none);
                    break;
                case FIELD_CELL_TYPE_APPLE:
                    /// Draw an apple
                    apple.setPosition(float(i * cell_size + score_bar_width), float(j * cell_size + score_bar_height));
                    window.draw(apple);
                    break;
                default:
                    /// Check if the cell represents the snake's head
                    if (game_state.field[j][i] == game_state.snake_length)
                    {
                        /// Set position and orientation for the snake's head
                        float offset_x = head.getLocalBounds().width / 2;
                        float offset_y = head.getLocalBounds().height / 2;
                        head.setPosition(float(i * cell_size + offset_x + score_bar_width), float(j * cell_size + score_bar_height + offset_y));
                        game_state.head_position_x = i * cell_size + score_bar_width + offset_x;
                        game_state.head_position_y = j * cell_size + score_bar_height + offset_y;
                        head.setOrigin(offset_x, offset_y);

                        /// Set rotation based on the snake's direction
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
                        /// Draw the snake's head
                        window.draw(head);
                    }
                    else
                    {
                        /// Draw the snake's body
                        snake.setPosition(float(i * cell_size + score_bar_width), float(j * cell_size + score_bar_height));
                        window.draw(snake);
                    }
                }
            }
        }
    }

    /// Set the position and draw the game logo
    logo.setPosition(float(score_bar_width * 2 / 13), float(window_height - 180));
    window.draw(logo);
}

/// Function to draw the score bar (points and remaining lives)
void draw_score_bar(RenderWindow &window)
{
    /// Draw the game title
    window.draw(text_title);

    /// Set and draw the points (score) display
    text_score.setString("Points: " + to_string(game_state.score));
    text_score.setPosition(window_width - text_score.getLocalBounds().width - 930, 40);
    window.draw(text_score);

    /// Draw the remaining lives
    for (int i = 0; i < lives; i++)
    {
        /// Set the position and draw each life icon
        life.setPosition(60, window_height * 10 / 15 - LIVES * 59 + i * 70);
        window.draw(life);
    }
}

/// Function to draw the record bar
void draw_record_bar(RenderWindow &window)
{
    /// Draw the game title
    window.draw(text_title);

    /// Set and draw the record display
    text_record.setString("Record: " + to_string(game_state.record));
    text_record.setPosition(window_width - text_record.getLocalBounds().width - 920, 140);
    window.draw(text_record);
}

/// Function to draw the main menu
void draw_main_menu(RenderWindow &window)
{
    /// Constants for menu layout and appearance
    float const menu_padding_horizontal = 200;
    float const menu_padding_vertical = 30;
    float const menu_item_interval = 20;

    float menu_item_max_width = 0;
    float current_menu_item_offset_y = -20;

    /// Iterate through menu items
    for (int i = 0; i < text_main_menu_items.size(); i++)
    {
        /// Check if the menu item is "START" or "RESUME" based on game state
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

        /// Set position, color, and update offset
        text_main_menu_items.at(i).setPosition(0, current_menu_item_offset_y);
        text_main_menu_items.at(i).setFillColor(
            current_main_menu_item_index == i ? Color(224, 224, 224) : Color(128, 128, 128));
        current_menu_item_offset_y += text_main_menu_items.at(i).getLocalBounds().height + menu_item_interval;
        menu_item_max_width = max(menu_item_max_width, text_main_menu_items.at(i).getLocalBounds().width);
    }

    /// Calculate menu dimensions and position
    float const menu_width = menu_item_max_width + menu_padding_horizontal * 2;
    float const menu_height = current_menu_item_offset_y - menu_item_interval + menu_padding_vertical * 2;
    float const menu_position_x = (window_width - menu_width) / 2;
    float const menu_position_y = (window_height - menu_height) / 2 - 150;

    /// Create and draw the menu rectangle
    RectangleShape menu_rect(Vector2f(menu_width, menu_height));
    menu_rect.setPosition(menu_position_x, menu_position_y);
    menu_rect.setFillColor(Color(0, 0, 0, 224));
    window.draw(menu_rect);

    /// Adjust and draw each menu item
    for (int i = 0; i < text_main_menu_items.size(); i++)
    {
        text_main_menu_items.at(i).move(menu_position_x + menu_padding_horizontal,
                                        menu_position_y + menu_padding_vertical);
        window.draw(text_main_menu_items.at(i));
    }
}

/// Function to grow the snake
void grow_snake()
{
    /// Iterate through the game field and increment values for each snake body part
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

/// Function to perform a move in the game
void make_move()
{
    /// Save the current game state in the history
    game_last_states.push_back(game_state);

    /// Keep only the last 10 game states in the history
    if (game_last_states.size() > 10)
    {
        game_last_states.erase(game_last_states.begin());
    }

    /// Update the snake's position based on its direction
    switch (game_state.snake_direction)
    {
    case SNAKE_DIRECTION_UP:
        game_state.snake_position_y--;
        if (game_state.snake_position_y < 2)
        {
            snake_died();
        }
        break;
    case SNAKE_DIRECTION_RIGHT:
        game_state.snake_position_x++;
        if (game_state.snake_position_x > field_size_x - 1)
        {
            snake_died();
        }
        break;
    case SNAKE_DIRECTION_DOWN:
        game_state.snake_position_y++;
        if (game_state.snake_position_y > field_size_y - 1)
        {
            snake_died();
        }
        break;
    case SNAKE_DIRECTION_LEFT:
        game_state.snake_position_x--;
        if (game_state.snake_position_x < 0)
        {
            snake_died();
        }
        break;
    }

    /// Check the content of the target cell after the move
    if (game_state.field[game_state.snake_position_y][game_state.snake_position_x] != FIELD_CELL_TYPE_NONE)
    {
        switch (game_state.field[game_state.snake_position_y][game_state.snake_position_x])
        {
        case FIELD_CELL_TYPE_APPLE:
            /// If the snake eats an apple
            game_state.snake_length++;
            game_state.score++;
            grow_snake();
            add_apple();
            game_state.count += 1;

            /// Update the record if needed
            if (game_state.score > game_state.record)
            {
                game_state.record = game_state.score;
            }
            break;
        default:
            /// If the snake collides with itself or the wall
            if (game_state.field[game_state.snake_position_y][game_state.snake_position_x] > 1)
            {
                snake_died();
            }
        }
    }

    /// Update the game field after the move
    if (!game_over && !rollback)
    {
        /// Decrease the values of all cells indicating the snake's body
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

        /// Set the value of the cell at the snake's new position to its length
        game_state.field[game_state.snake_position_y][game_state.snake_position_x] = game_state.snake_length;
    }
}

int main()
{
    /// Initialize the game
    init_game();

    /// Create SFML window
    RenderWindow window(VideoMode(window_width, window_height), "Snake", Style::Close);

    /// Queue to store snake directions
    vector<int> snake_direction_queue;

    /// Main game loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            /// Handle window closure event
            if (event.type == Event::Closed)
                window.close();

            /// Handle key presses
            if (event.type == Event::KeyPressed)
            {
                /// Check if the game is paused
                if (game_paused)
                {
                    /// Process key presses during pause
                    if (game_over_timeout == 0)
                    {
                        if (current_menu == MENU_MAIN)
                        {
                            switch (event.key.code)
                            {
                            case Keyboard::Up:
                                /// Navigate up in the main menu
                                current_main_menu_item_index--;
                                if (current_main_menu_item_index < 0)
                                {
                                    current_main_menu_item_index = text_main_menu_items.size() - 1;
                                }
                                break;
                            case Keyboard::Down:
                                /// Navigate down in the main menu
                                current_main_menu_item_index++;
                                if (current_main_menu_item_index > text_main_menu_items.size() - 1)
                                {
                                    current_main_menu_item_index = 0;
                                }
                                break;
                            case Keyboard::Enter:
                                /// Handle Enter key press in the main menu
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
                                /// Resume the game during pause
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
                    /// Process key presses during the active game
                    int snake_direction_last = snake_direction_queue.empty() ? game_state.snake_direction : snake_direction_queue.at(0);
                    switch (event.key.code)
                    {
                    case Keyboard::Up:
                        /// Queue the up direction if valid
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
                        /// Queue the right direction if valid
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
                        /// Queue the down direction if valid
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
                        /// Queue the left direction if valid
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
                        /// Pause the game
                        game_paused = true;
                        break;
                    }
                }
            }
        }

        /// Set the snake direction based on the queue
        if (!snake_direction_queue.empty())
        {
            game_state.snake_direction = snake_direction_queue.back();
            snake_direction_queue.pop_back();
        }

        /// Process the game logic if not paused
        if (!game_paused)
        {
            if (!rollback)
            {
                /// Make a move in the game
                make_move();
            }
            else
            {
                /// Rollback to the previous game state
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

        /// Clear the window and draw the game elements
        window.clear(Color(38, 84, 124));
        draw_field(window);
        draw_score_bar(window);
        draw_record_bar(window);

        /// Display "Game Over" text if the game is over
        if (game_over)
        {
            window.draw(text_game_over);
            if (game_over_timeout > 0)
            {
                game_over_timeout--;
            }
        }

        /// Display the main menu if the game is paused and the timeout is zero
        if (game_paused && game_over_timeout == 0)
        {
            switch (current_menu)
            {
            case MENU_MAIN:
                draw_main_menu(window);
                break;
            }
        }

        /// Update the window
        window.display();

        /// Delay for a short duration based on the game score
        sleep(milliseconds(150 - game_state.score * 2));
    }

    return 0;
}
