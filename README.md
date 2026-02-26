*This project has been created as part of the 42 curriculum by tide-pau*

# Philosophers

## Description

- The Philosophers project is a simulation of the Dining Philosophers problem. It introduces the basic uses of threads and mutexes.
- This program creates multiple philosopher threads that compete for shared resources while avoiding data races, deadlocks and starvation.
- The goal is to correctly handle the synchronization of shared resources access and ensure precise time-based behaviour according to the project requirements.

## Instructions

### Compilation
- To compile the code you should go into the project folder location and open the terminal there.
- Then use the command `make` to compile the code.
- If you use `make re` you recompile the code deleting object files and creating them again along with the main program.
- You can also clean the folder of compiled files by using `make fclean`.
- If you only want to clean the object files just do `make clean`.

### Execution
- To execute the program you need to write in the terminal `./philo Time_to_die Time_to_eat Time_to_sleep (optional argument)Number of times a philosopher should eat`.
- The timers are all in `milliseconds`.

## Resources

- The resources that I used were few since the project subject already explains well what we need to do.
- The only points were I used external help were for how to use `threads` and `mutexes`, in these two cases i asked my colleagues how they work and what they do.
- I also used `chatgpt` for some logic questions.