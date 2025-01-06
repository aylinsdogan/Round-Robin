# Round-Robin

## Overview

This C program simulates a task scheduler that processes tasks with various commands. It maintains two queues: one for tasks that are yet to be completed (`taskList`) and one for tasks that have been completed (`taskListCompleted`). The program supports several commands for task management, simulation of task execution, and reporting.

## Features
- **Add new tasks** to the scheduler.
- **Execute tasks** in time units.
- **Track system time** and **idle time** when no tasks are available.
- **Display completed tasks** with runtime details.
- **Export completed task details** to a file.
- **Clear completed tasks** from memory.

## Commands

### 1. `SNT` <task_id> <runtime>
   - **Description**: Adds a new task to the scheduler with a specified ID and runtime.
   - **Example**:
     ```
     SNT Task1 10
     ```

### 2. `S` <k>
   - **Description**: Simulates the execution of tasks for `k` time units.
   - **Example**:
     ```
     S 5
     ```

### 3. `DST`
   - **Description**: Displays the current system time.
   - **Example**:
     ```
     DST
     ```

### 4. `DTIT`
   - **Description**: Displays the total idle time (when no tasks are being executed).
   - **Example**:
     ```
     DTIT
     ```

### 5. `DIMRCT`
   - **Description**: Displays the most recently completed task along with its ID, initial runtime, and completion time.
   - **Example**:
     ```
     DIMRCT
     ```

### 6. `DCTQ` <filename>
   - **Description**: Exports completed task details to a file specified by `filename`.
   - **Example**:
     ```
     DCTQ completed_tasks.txt
     ```

### 7. `ECTS`
   - **Description**: Empties the completed tasks queue (cleans up memory).
   - **Example**:
     ```
     ECTS
     ```

### 8. `QUIT`
   - **Description**: Quits the program.
   - **Example**:
     ```
     QUIT
     ```
