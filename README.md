# Wordle-Solver-Project
Wordle Game & Solver in C

This project is a terminal-based implementation of the Wordle game written in C, including an automatic solver.

The program allows:
- A human player to play Wordle in the terminal
- An automated solver to guess the word using logical elimination based on feedback

The project demonstrates:
- Modular programming in C (multiple `.c` and `.h` files)
- Use of data structures
- String manipulation
- Algorithmic reasoning and complexity analysis

. Project Objective
The main objectives of this project are:
- Implement the Wordle game rules correctly
- Use feedback (GREEN, YELLOW, GRAY) to eliminate impossible words
- Design a simple but effective solver
- Practice clean C code organization and documentation


.Project Structure


wordle-c/

│── main.c        # Entry point (game loop)

│── wordle.h      # Wordle declarations

│── wordle.c      # Wordle game logic

│── solver.h      # Solver declarations

│── solver.c      # Solver implementation

│── words.txt     # Dictionary of valid 5-letter words

│── README.md     # Project documentation

.Compilation & Execution

Compile

gcc main.c wordle.c solver.c -o wordle

Run

./wordle

Make sure the file **`words.txt`** is in the same directory.



 .How to Play

1. The program selects a random 5-letter word.
2. You have **6 attempts** to guess it.
3. After each guess, feedback is displayed:

   * `[G]` → Correct letter, correct position
     
   * `[Y]` → Correct letter, wrong position
     
   * `[ ]` → Letter not in the word
     
4. Guess the word within 6 tries to win.
5. Sample Interaction (Human Player)
   
   === WORDLE GAME ===
   
Guess 1: arise

[G]a[Y]r[ ]i[ ]s

Guess 2: alarm

[G]a[G]l[G]a[ ]r

Guess 3: alamo

[G]a[G]l[G]a[G]o

You win!

6.Sample Output (Automatic Solver)

  --- Auto Solver ---
  
Attempt 1: arise

[Y]a[ ]r[ ]i[ ]s

Attempt 2: alamo

[G]a[G]l[G]a[G]o

Solver wins in 2 attempts!



.Solver Strategy

* Starts with a fixed good word (`arise`)
* Uses Wordle feedback to eliminate impossible words
* Keep only words that match all feedback constraints
* Chooses the next guess from remaining candidates
This approach efficiently reduces the search space



.Data Structures Used

* Arrays for word storage (fast and simple)
* Structs for dictionary abstraction
* Enums for feedback clarity

These choices ensure:

* Low memory overhead
* Easy filtering of candidate words
* Clear and readable code



.Complexity Analysis

* Dictionary loading: O(N)
* Feedback evaluation: O(WORD_LEN²)
* Solver filtering per attempt: O(N × WORD_LEN²)

Given typical dictionary sizes, performance is excellent


.Author:

Nour elhouda Ammiche

Nada Bencheikh

course: algorithm and data structures

Language: C

If you want help improving the solver feel free to ask :) 
