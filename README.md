# 2324_ESE3745_LESNE_LIENART



TP2 :
Le codeur incrémental du moteur a 1024 points, puisque le mode encodeur du timer de la STM32 compte tous les fronts montants (le signe dépend du sens de rotation), le timer comptera 4096 ticks par tour du moteur. La fonction de transfert du capteur de vitesse sera donc w = (cnt/4096)/Dt.
La constante de temps du moteur est de 98ms donc nous allons asservir le moteur à toutes les 10ms (= 100Hz).
Avec le tachymètre inclus au moteur, on mesure une vitesse de 556 tr/min. Tandis qu'avec l'encodeur on mesure 0,723 rad/s = 9.03 tr/s = 542 tr/min 
Le timer utilisé en mode encodeur doit avoir le champ "Enodeur mode" à la valeur "Encodeur mode Ti1 and Ti2" pr être capable de prendre en compte le sens du moteur

TP3 :
On utilise des structures pour stocker les valeurs précédentes et les constantes