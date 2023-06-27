Branche "contrôle"
------------------

Ce projet vise à contrôler les différents composants du plateau de jeu, y compris les positions des gardiens à l'aide de drv8825 et de capteurs de fin de course, la détection de la présence de la balle dans les buts, et l'activation des solénoïdes linéaires pour frapper la balle. En outre, ce projet gère le déroulement du jeu, compte les points et arrête la partie lorsqu'un joueur n'a plus de vie.

### Configuration requise

-   PlatformIO
-   ESP32
-   drv8825 (driver moteur pas à pas)
-   Capteurs de fin de course
-   Solénoïdes linéaires

### Installation

1.  Clonez ce dépôt GitHub sur votre machine locale.
2.  Ouvrez le projet dans PlatformIO.
3.  Connectez votre ESP32 à votre ordinateur.
4.  Compilez et téléchargez le code sur votre ESP32.
5.  Connectez les composants nécessaires à l'ESP32 selon le schéma de câblage fourni dans le dossier "docs".

### Utilisation

1.  Assurez-vous que l'ESP32 est correctement connecté à l'alimentation et aux composants du plateau de jeu.
2.  Les capteurs de fin de course doivent être configurés pour détecter les positions extrêmes des gardiens et arrêter leur mouvement.
3.  La détection de la présence de la balle dans les buts doit être configurée pour signaler un but lorsqu'elle est déclenchée.
4.  Les solénoïdes linéaires doivent être activés au bon moment pour frapper la balle.
5.  Le déroulement du jeu, le comptage des points et l'arrêt de la partie lorsque nécessaire doivent être gérés par le code.


### v0.32

- simplification des fonctions de detection de presence de la balle dans les buts (correction des bugs)
- convention/protocole de communication UART entre les 2 ESP32
- possibliité de gerer les joueurs actifs et inactifs via l'envoi de messages sur le UART
- distance max des axes modifiable pour chaque joueur

## v0.33
- remise en jeu automatique de tous les joueurs lors du début de partie