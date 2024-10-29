# PHILOSPHERS 42
## This is the philo project from 42 PARIS

It consists in tackling the concept of threads in C and understanding concurrent programming, focusing on multithreading.

The program runs with:
`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]`
◦ number_of_philosophers: The number of philosophers and also the number of forks.  
◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.  
◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.  
◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.  
◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.  

Essentially, I create a thread per philospher (and one for an observer) and they run simultaniously, using mutexes to make sure there are no data races. The philosophers will perform their actions (eating, sleeping, thinking) in tandem with eachother.  
The project is an introduction to these concepts.  
