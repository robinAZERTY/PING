# PING - Jeu de plateau interactif

**Repo obsolète, une deuxième version du jeu est en cours de développement sur [https://github.com/2PING2/PING2](https://github.com/2PING2/PING2)**

Ce projet est un jeu de plateau interactif appelé PING, conçu pour être joué entre 1 et 4 joueurs. Le jeu est similaire au jeu Pong, mais avec la particularité d'avoir 4 joueurs et de se jouer en présentiel.

## Objectif du jeu

Le but du jeu est de faire entrer la balle dans le but d'un adversaire tout en protégeant son propre but. Le joueur qui réussit à éviter de prendre un but gagne la partie. Chaque joueur dispose d'un gardien contrôlé à l'aide d'un contrôleur (téléphone) pour activer et translater sa surface de rebond.

## Fonctionnalités

- Chaque partie commence avec un joueur choisi aléatoirement qui place la balle devant son gardien pour commencer le jeu.
- Les joueurs contrôlent leurs gardiens à l'aide de l'interface web accessible sur un ESP32 via une connexion Wi-Fi.
- Les commandes de contrôle sont communiquées via une communication UART entre les deux ESP32.
- Le jeu gère le déroulement de la partie, compte les points et arrête la partie lorsque l'un des joueurs n'a plus de vie.
- Les joueurs perdent une vie chaque fois qu'ils prennent un but.
- Le premier joueur à perdre toutes ses vies perd la partie.

## Architecture du projet

Le projet est divisé en trois branches principales :

1. **web** : Cette branche contient le développement de l'interface web exclusive stockée sur l'ESP32. L'application web comporte au moins deux pages : une page d'accueil où les joueurs peuvent choisir leur gardien et une page de contrôle où ils peuvent contrôler leur gardien. La connexion à l'interface web se fait via un QR code.
2. **contrôle** : Cette branche est dédiée au contrôle de tous les composants du plateau de jeu. Elle gère les positions des gardiens à l'aide de DRV8825 et des end-stops, la détection de la présence de la balle dans les buts et l'activation des solénoïdes linéaires pour frapper la balle. En plus de cela, elle gère le déroulement du jeu, compte les points et arrête la partie lorsque l'un des joueurs n'a plus de vie.
3. **main** : Cette branche contient la version complète du jeu. Elle intègre les fonctionnalités de contrôle des gardiens via l'interface web (ESP32 web) et la communication des commandes via UART entre les deux ESP32. C'est la branche principale du projet qui rassemble toutes les fonctionnalités.

## Environnement de développement

Le projet utilise PlatformIO sous VSCode comme environnement de développement. Il est recommandé d'utiliser cet environnement pour faciliter la compilation et le téléchargement du code sur les ESP32.

## Configuration

Avant de pouvoir exécuter le jeu, assurez-vous d'avoir correctement configuré les deux ESP32 pour la communication UART et la connexion Wi-Fi. Reportez-vous aux README.md des branches "web" et "contrôle" pour obtenir des informations détaillées sur la configuration de chaque branche.

## Auteurs

Ce projet a été développé par robin, simon, thomas et franck.

Nous espérons que vous apprécierez jouer à PING !
