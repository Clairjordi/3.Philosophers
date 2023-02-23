# Philosophers

Projet Ecole 42:

Utilisation des fonctions thread et mutex du langage C, imagé comme suit :
des philosophes sont autour d'une table et chacun à une fourchette. Ils peuvent manger, dormir ou penser mais ne peuvent pas le faire en même temps.
Pour pouvoir manger, ils empruntent la fourchette de leur voisin, mange un temps que l'on aura donné en paramètre, puis repose les 2 fourchettes
et ensuite dort. Si i la du temps disponible entre manger et dormir alors il pense.
Si le temps de manger et de dormir dépassent le temps de mort alors le philosophe meurt et le programme s'arrète.

./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat] - seul paramètre optionnel,
                                                                                                                          demande à ce que les philosophes 
                                                                                                                          ne mangent que certain nombre de 
                                                                                                                          fois avant de terminer le 
                                                                                                                          programme.
compétences acquises : 
- utilisations de thread
- utilisation de mutex
