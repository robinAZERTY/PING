## V0.37

La branche "web" de ce projet met l'accent sur le développement d'une interface web pour le jeu PONG à quatre joueurs, qui est exclusivement stockée sur l'ESP32. L'objectif principal de cette version est de fournir une expérience de jeu interactive et conviviale via une interface web.

### Pages web

L'application comprend deux pages principales :

1. **Page d'accueil** : Sur cette page, les joueurs peuvent choisir leur gardien parmi les différentes options disponibles. Chaque joueur peut visualiser les gardiens disponibles, sélectionner celui de son choix et valider sa sélection. Une fois que tous les joueurs ont choisi leur gardien, le jeu peut commencer.

2. **Page de contrôle du gardien** : Après avoir choisi leur gardien, les joueurs sont redirigés vers cette page où ils peuvent contrôler leur gardien pendant le jeu. Les commandes de déplacement permettent aux joueurs de déplacer leur gardien verticalement pour intercepter la balle et la renvoyer vers les adversaires. Des indicateurs de score et de vie peuvent également être affichés pour chaque joueur.

### Connexion Wi-Fi et QR code

La connexion à l'ESP32 se fait via Wi-Fi. Les joueurs peuvent se connecter en scannant un QR code généré par l'ESP32 à l'aide de leur téléphone ou d'un autre appareil. Une fois connectés, ils sont redirigés vers la page d'accueil pour commencer le jeu.

### Configuration requise

Avant d'utiliser ce projet, assurez-vous de disposer des éléments suivants :

-   PlatformIO installé sur votre machine.
-   Un module ESP32 connecté et fonctionnel.

### Installation

Suivez ces étapes pour installer et exécuter le projet :

1.  Clonez ce dépôt GitHub sur votre machine locale.
2.  Ouvrez le projet dans PlatformIO.
3.  Connectez votre module ESP32 à votre ordinateur.
4.  Compilez et téléchargez le code sur votre ESP32 en utilisant PlatformIO.
5.  Effectuez une modification dans le fichier `WebAuthentication.cpp` pour résoudre un problème de compilation spécifique à l'ESP Async WebServer. Consultez la section "Correction d'un problème de compilation" ci-dessous pour plus de détails.
6.  Assurez-vous que votre ESP32 est correctement connecté à l'alimentation.

### Correction d'un problème de compilation

Pour résoudre un problème de compilation spécifique à l'ESP Async WebServer, suivez ces étapes supplémentaires :

1.  Dans le répertoire `.pio\libdeps\az-delivery-devkit-v4\ESP Async WebServer\src`, ouvrez le fichier `WebAuthentication.cpp`.
2.  Allez à la ligne 74 et remplacez les lignes suivantes :

    ```cpp
    mbedtls_md5_starts(&_ctx);
    mbedtls_md5_update(&_ctx, data, len);
    mbedtls_md5_finish(&_ctx, _buf);
    ```

    par les lignes suivantes :

    ```cpp
    mbedtls_md5_starts_ret(&_ctx);
    mbedtls_md5_update_ret(&_ctx, data, len);
    mbedtls_md5_finish_ret(&_ctx, _buf);
    ```

    Cela résout le problème de compilation lié à la bibliothèque ESP Async WebServer.

### Utilisation

Une fois que vous avez installé et configuré le projet, vous pouvez commencer à l'utiliser en suivant ces étapes :

1.  Assurez-vous que votre ESP32 est correctement connecté à l'alimentation.
2.  Scannez le QR code généré par l'ESP32 à l'aide de votre téléphone ou d'un autre appareil.
3.  Vous serez automatiquement redirigé vers la page d'accueil où vous pouvez choisir votre gardien parmi les options disponibles.
4.  Suivez les instructions à l'écran pour jouer au jeu PONG à quatre joueurs.

Profitez du jeu et amusez-vous bien !