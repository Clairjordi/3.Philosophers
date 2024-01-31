# Philosophers

School Project 42 :

Use of the thread and mutex functions of the C language, imaged as follows:
philosophers are around a table and each has a fork. They can eat, sleep or think but cannot do it at the same time.
To be able to eat, they borrow their neighbor's fork, eat for a time that we have given as a parameter, then put the 2 forks back
and then sleeps. If there is time available between eating and sleeping then he thinks.
If the time of eating and sleeping exceeds the time of death then the philosopher dies and the program stops.

## For launch
```./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]```
number_of_times_each_philosopher_must_eat : only optional parameter, requires that philosophers only eat a certain number of times before completing the program.

![Screenshot from 2023-02-24 16-27-01](https://user-images.githubusercontent.com/88725985/221221450-bb1f857a-83f2-41ea-804f-413ccaa913ac.png)
![Screenshot from 2023-02-24 16-32-23](https://user-images.githubusercontent.com/88725985/221221461-b8e476d6-b52a-4d1a-8519-113ee622e0fe.png)
