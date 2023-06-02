Branche "web"
-------------

Ce projet vise à développer une interface web pour le jeu PONG à quatre joueurs, exclusivement stockée sur l'ESP32. L'application comportera au moins deux pages : une page d'accueil où les joueurs peuvent choisir leur gardien et une autre page où ils peuvent contrôler leur gardien. La connexion se fera par Wi-Fi, et les utilisateurs seront redirigés vers la première page après s'être connectés via un QR code.

### Configuration requise

-   PlatformIO
-   ESP32

### Installation

1.  Clonez ce dépôt GitHub sur votre machine locale.
2.  Ouvrez le projet dans PlatformIO.
3.  Connectez votre ESP32 à votre ordinateur.
4.  Compilez et téléchargez le code sur votre ESP32.

### Utilisation

1.  Assurez-vous que l'ESP32 est correctement connecté à l'alimentation et au réseau Wi-Fi.
2.  Scannez le QR code affiché sur l'ESP32 à l'aide de votre téléphone ou d'un autre appareil.
3.  Vous serez redirigé vers la page d'accueil où vous pouvez choisir votre gardien.
4.  Une fois que tous les joueurs ont choisi leur gardien, la partie commencera.
5.  Sur la page de contrôle du gardien, utilisez les commandes à l'écran pour activer et déplacer la surface de rebond de votre gardien.
6.  Le but du jeu est de ne pas prendre de but. Chaque fois qu'un joueur encaisse un but, il perd une vie.
7.  Le premier joueur à perdre toutes ses vies perd la partie.
