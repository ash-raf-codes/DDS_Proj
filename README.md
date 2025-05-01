# Deadline-Driven Scheduler (DDS) – ECE 455 Project

This project demonstrates a **Deadline-Driven Scheduler (DDS)** implemented using **FreeRTOS** for real-time embedded systems. Tasks with hard deadlines are dynamically scheduled using the **Earliest Deadline First (EDF)** algorithm, and task state is monitored throughout execution.

> **Platform**: STM32 with FreeRTOS on Lab Machines

---

## 🧩 System Components

### 🔁 Scheduler (DD_Scheduler)
- Central EDF-based scheduler with maximum priority.
- Manages three linked lists: `activeTaskList`, `completedTaskList`, and `overdueTaskList`.
- Receives and processes messages via a message queue to manage task lifecycle events (`create`, `delete`, etc.).

### 🧪 User Tasks
- Three simulated tasks (`vUserTask1`, `vUserTask2`, `vUserTask3`) using busy loops to represent execution time.
- Tasks self-report completion via `delete_dd_task()`.

### ⏱ Task Generators
- Three generators trigger periodic task creation based on preconfigured execution times and periods.
- Each generator calculates deadlines and communicates with the scheduler.

### 🖥 Monitor Task
- Periodically logs the system state (active, completed, and overdue tasks) without interrupting scheduling.
- Triggered every 500ms by a FreeRTOS software timer.

---

## 📋 Benchmarks

Three test configurations are provided:

1. **Benchmark 1** – Balanced timing (82% CPU utilization)  
2. **Benchmark 2** – Tight timing (101% CPU utilization, some missed deadlines)  
3. **Benchmark 3** – Equal periods (tight scheduling, tests EDF limits)

Benchmarks are defined in `main_DDS.c` using the `Bench_Choice` macro.

---

## 📈 Performance Summary

- Scheduler meets deadlines under moderate utilization.
- Test Bench 2 demonstrates system limits with a small number of overdue tasks.
- EDF algorithm effectively handles task prioritization and preemption.

---

## 📌 Features

- Earliest Deadline First (EDF) task scheduling
- Custom task creation/deletion APIs
- Linked-list-based task tracking
- Console-based task trace output
- Real-time system monitor with minimal overhead

---

## 🚧 Limitations

- No dynamic memory deallocation (possible memory leak over long runs)
- No formal admission control (schedulability test)
- Limited fault tolerance and error handling
- Static benchmarking only

---

## 📚 References

- ECE 455 Lab Manual – University of Victoria
- FreeRTOS.org – Official RTOS Documentation

---
