<div align="center">
  <img 
    src="https://github.com/user-attachments/assets/bf786fab-8f65-4a58-9f10-e4a0fcb2583f" 
    alt="Philosophers Problem"
    width="800"
  />
</div>



# Philosophers 42 (The Dining Philosophers Problem)

This project is a solution to the famous "Dining Philosophers" problem, created as part of the 42 school curriculum. The challenge focuses on concurrency, process synchronization, and avoiding deadlocks — essential topics in systems programming.

## 🧠 About the Problem

Five philosophers sit around a table, each alternating between thinking and eating. Between each philosopher is a fork. To eat, a philosopher needs both forks to their left and right. The problem is to design a protocol so that no philosopher starves (livelock) or the program deadlocks.

## 🚀 Project Overview

- **Language:** C
- **Build System:** Makefile
- **Concurrency:** pthreads (POSIX threads)
- **Synchronization:** Mutexes for forks, and additional mutexes for synchronized printing and death detection.

## 📦 Files

- `philo.c` - Main program logic and initialization.
- `philo.h` - Header file with struct and function declarations.
- `actions.c` - Philosopher routines (eat, think, sleep).
- `utils.c` - Utility functions (time, error handling).
- `Makefile` - Build automation.

## 🛠️ Installation and Usage

1. **Clone the repository:**
   ```sh
   git clone https://github.com/elel-m-b/the_dining_philosophers_problem_solution.git
   cd the_dining_philosophers_problem_solution
   ```

2. **Compile the project:**
   ```sh
   make
   ```

3. **Run the program:**
   ```sh
   ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
   ```
   - Example:
     ```sh
     ./philo 5 800 200 200
     ```
   - Arguments:
     - `number_of_philosophers` — Number of philosophers and forks.
     - `time_to_die` — Time (ms) a philosopher can go without eating before dying.
     - `time_to_eat` — Time (ms) it takes to eat.
     - `time_to_sleep` — Time (ms) to sleep.
     - `number_of_times_each_philosopher_must_eat` (optional) — Simulation ends when each philosopher has eaten this many times.

## 📝 Rules & Constraints

- Each philosopher must take the fork to their left and right before eating.
- Philosophers must avoid deadlock and starvation.
- No philosopher should print messages at the same time as another.
- The simulation stops if a philosopher dies.

