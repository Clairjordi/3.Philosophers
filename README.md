# Philosophers

Projet Ecole 42:

Utilisation des fonctions thread et mutex du langage C, imagé comme suit :
des philosophes sont autour d'une table et chacun à une fourchette. Ils peuvent manger, dormir ou penser mais ne peuvent pas le faire en même temps.
Pour pouvoir manger, ils empruntent la fourchette de leur voisin, mange un temps que l'on aura donné en paramètre, puis repose les 2 fourchettes
et ensuite dort. Si i la du temps disponible entre manger et dormir alors il pense.
Si le temps de manger et de dormir dépassent le temps de mort alors le philosophe meurt et le programme s'arrète.

./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat] - seul paramètre optionnel,        demande à ce que les philosophes ne mangent qu'un certain nombre de fois avant de terminer le programme.

![Screenshot from 2023-02-24 16-27-01](https://user-images.githubusercontent.com/88725985/221221450-bb1f857a-83f2-41ea-804f-413ccaa913ac.png)
![Screenshot from 2023-02-24 16-32-23](https://user-images.githubusercontent.com/88725985/221221461-b8e476d6-b52a-4d1a-8519-113ee622e0fe.png)
