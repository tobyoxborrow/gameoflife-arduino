#include "LedControl.h"

// "DIN" data in pin
#define DIN_PIN 12
// "CLK" clock pin
#define CLK_PIN 11
// "CS" pin
#define CS_PIN 10
// grid dimensions. should not be larger than 8x8
#define MAX_Y 8
#define MAX_X 8
// time to wait between turns
#define TURN_DELAY 800
// how many turns per game before starting a new game
// you can also use the reset button on the board
#define TURNS_MAX 60
// how many turns to wait if there are no changes before starting a new game
#define NO_CHANGES_RESET 4

int TURNS = 0;      // counter for turns
int NO_CHANGES = 0; // counter for turns without changes

// game state. 0 is dead cell, 1 is live cell
boolean grid[MAX_Y][MAX_X] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
};

LedControl lc = LedControl(DIN_PIN, CS_PIN, CLK_PIN, 1);


void setup() {
  // seed random from unused analog pin
  randomSeed(analogRead(0));

  // initialise the LED matrix
  lc.shutdown(0, false);
  lc.setIntensity(0, 0);
  lc.clearDisplay(0);

  reset_grid();
  display_grid();

  //Serial.begin(9600);
  //debug_grid();
}

void loop() {  
  delay(TURN_DELAY);
  
  play_gol();

  TURNS++;

  // reset the grid if no changes have occured recently
  // for when the game enters a static stable state
  if (NO_CHANGES > NO_CHANGES_RESET) {
    reset_grid();
  }
  // reset the grid if the loop has been running a long time
  // for when the game cycles between a few stable states
  if (TURNS > TURNS_MAX) {
    reset_grid();
  }
  
  display_grid();
}

// play game of life
void play_gol() {
  /*
    1. Any live cell with fewer than two neighbours dies, as if by loneliness.
    2. Any live cell with more than three neighbours dies, as if by overcrowding.
    3. Any live cell with two or three neighbours lives, unchanged, to the next generation.
    4. Any dead cell with exactly three neighbours comes to life.
    */

  boolean new_grid[MAX_Y][MAX_X] = {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
  };

  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      int neighboughs = count_neighboughs(y, x);
      if (grid[y][x] == 1) {
        if ((neighboughs == 2) || (neighboughs == 3)) {
          new_grid[y][x] = 1;
        } else {
          new_grid[y][x] = 0;
        }
      } else {
        if (neighboughs == 3) {
          new_grid[y][x] = 1;
        } else {
          new_grid[y][x] = 0;
        }
      }
    }
  }

  // update the current grid from the new grid and count how many changes occured
  int changes = 0;
  for (int y = 0; y < MAX_Y; y++) {
    for (int x = 0; x < MAX_X; x++) {
      if (new_grid[y][x] != grid[y][x]) {
        changes++;
      }
      grid[y][x] = new_grid[y][x];
    }
  }

  // update global counter when no changes occured
  if (changes == 0) {
    NO_CHANGES++;
  }
}

// count the number of neighbough live cells for a given cell
int count_neighboughs(int y, int x) {
  int count = 0;

  // -- Row above us ---
  if (y > 0) {
    // above left
    if (x > 0) {
      count += grid[y-1][x-1];
    }
    // above
    count += grid[y-1][x];
    // above right
    if ((x + 1) < 8) {
      count += grid[y-1][x+1];
    }
  }
  
  // -- Same row -------
  // left
  if (x > 0) {
    count += grid[y][x-1];
  }
  // right
  if ((x + 1) < 8) {
    count += grid[y][x+1];
  }

  // -- Row below us ---
  if ((y + 1) < 8) {
    // below left
    if (x > 0) {
      count += grid[y+1][x-1];
    }
    // below
    count += grid[y+1][x];
    // below right
    if ((x + 1) < 8) {
      count += grid[y+1][x+1];
    }
  }
  
  return count;
}

// reset the grid
// we could set it all to zero then flip some bits on
// but that leads to some predictable games I see quite frequently
// instead, keep previous game state and flip some bits on
void reset_grid() {
  NO_CHANGES = 0;
  TURNS = 0;
  
  for (int y = 0; y < MAX_Y; y++) {
    for (int x = 0; x < MAX_X; x++) {
      if (random(0, MAX_X) <= 1) {
        grid[y][x] = 1;
      }
    }
  }
}

// display the current grid to the LED matrix
void display_grid() {
  for (int y = 0; y < MAX_Y; y++) {
    for (int x = 0; x < MAX_X; x++) {
      lc.setLed(0, y, x, grid[y][x]);
    }
  }
}

/*
// dump the state of the current grid to the serial connection
void debug_grid() {
  for (int y = 0; y < MAX_Y; y++) {
    Serial.print("y(");
    Serial.print(y);
    Serial.print("): ");

    for (int x = 0; x < MAX_X; x++) {
      Serial.print(grid[y][x]);
      Serial.print(", ");
    }

    Serial.println("");
  }
  Serial.println("");
}
*/
