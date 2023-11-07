# 2324_ESE3745_LESNE_LIENART

## Introduction
Le but de la série de TP est d'asservir une MCC en commandant un pont en H grâce à des PWM générées par une STM32.


## TP1 :
### Console UART
Dans un soucis de gain de temps pour l'implantation d'une fonctionnalité sans rapport avec la commande de moteurs, nous avons récupéré le shell écrit par Mr. Papazoglou. 

### Génération de PWM
Pour la génération des PWM nous utilisons le **Timer 1** pour générer des PWM sur ses **channels 1 & 2** (avec leurs compléménetaires). Les broches de la carte sur lesquels sont routés ces **channels** mènent aux transisors contrôlant les ponts U et V.

## TP2 :
Le codeur incrémental du moteur a 1024 points, puisque le mode encodeur du timer de la STM32 compte tous les fronts montants (le signe dépend du sens de rotation), le timer comptera 4096 ticks par tour du moteur. La fonction de transfert du capteur de vitesse sera donc w = (cnt/4096)/Dt.
La constante de temps du moteur est de 98ms donc nous allons asservir le moteur à toutes les 10ms (= 100Hz).
Avec le tachymètre inclus au moteur, on mesure une vitesse de 556 tr/min. Tandis qu'avec l'encodeur on mesure 0,723 rad/s = 9.03 tr/s = 542 tr/min 
Le timer utilisé en mode encodeur doit avoir le champ "Enodeur mode" à la valeur "Encodeur mode Ti1 and Ti2" pr être capable de prendre en compte le sens du moteur
![Mesure du temps de réponse du moteur à une consigne indicielle.](tps_reponse.png)

## TP3 :
On utilise des structures pour stocker les valeurs précédentes et les constantes


## TP4:
Nous n'avions pas de pseudo code pour la fonction de PID et puisque nous avons voulu écrire des structures afin de stocker toutes les variables, nous avons perdu beaucoup de temps et n'avons pas pu finir l'asservissement.