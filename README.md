Branche "main"
--------------

Cette branche contient la version complète du jeu PONG à quatre joueurs, combinant à la fois l'interface web de contrôle et le code de contrôle des composants du plateau de jeu. Assurez-vous d'avoir configuré et testé les branches "web" et "contrôle" avant de travailler sur cette branche.

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

1.  Assurez-vous que l'ESP32 est correctement connecté à l'alimentation, aux composants du plateau de jeu et au réseau Wi-Fi.
2.  Suivez les instructions de la branche "web" pour vous connecter à l'interface web à l'aide d'un QR code.
3.  Choisissez votre gardien sur la page d'accueil.
4.  Sur la page de contrôle du gardien, utilisez les commandes à l'écran pour activer et déplacer la surface de rebond de votre gardien.
5.  Jouez au jeu en essayant de ne pas prendre de but. Chaque fois qu'un joueur encaisse un but, il perd une vie.
6.  Le premier joueur à perdre toutes ses vies perd la partie.

Pour le fonctionnement multi-tâche : https://www.aranacorp.com/fr/programme-multitache-avec-esp32-et-freertos/
Pour le fonctionnement multi-coeurs : https://randomnerdtutorials.com/esp32-dual-core-arduino-ide/
