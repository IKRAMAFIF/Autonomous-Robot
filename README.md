## 🧠 Introduction

Le projet **CATRONIC** consiste à développer un **robot autonome** capable de jouer au **chat et à la souris** avec d’autres robots du même type.  
Les robots évoluent sur une **table sans bordures**, ils doivent donc être capables de **détecter les bords** afin d’éviter toute chute.

Le robot repose sur un **microcontrôleur STM32** et applique des **principes de systèmes temps réel** pour gérer la communication entre ses composants matériels et logiciels.  
Il dispose de deux modes de fonctionnement :  

- **Mode Chat 🐱**   
- **Mode Souris 🐭**  

---

## 🧩 Architecture du système global

### 🧭 Diagramme fonctionnel
![Diagramme d'architecture](Images/diagramme_architecture.jpg)

### 🧠 Description générale

Le robot **CATRONIC** est un système embarqué autonome conçu pour simuler un jeu de **chat et de souris** entre plusieurs robots identiques.  
Chaque robot interagit avec son environnement grâce à un ensemble de capteurs et d’actionneurs coordonnés par un **microcontrôleur STM32G431CBU6**.  

L’architecture du système est organisée autour de cinq sous-ensembles principaux :  
1. **L’alimentation**,  
2. **La commande (microcontrôleur et logiciel embarqué)**,  
3. **L’acquisition (capteurs)**,  
4. **Le déplacement (moteurs et drivers)**,  
5. **L’interface utilisateur**.  

---

#### 🔋 Sous-système d’alimentation
Le robot est alimenté par une **batterie NiMH de 7.2 V – 1.3 Ah**, fournissant l’énergie à l’ensemble du système.  
Deux régulateurs assurent la distribution des tensions :  
- **MP1475S (5 V)** : alimentation du **LIDAR**.  
- **BU33SD5WG-TR (3.3 V)** : alimentation du **STM32**, de l’**accéléromètre ADXL343** et des **capteurs mécaniques MITV**.  

Cette architecture garantit une alimentation stable et adaptée à chaque composant, tout en protégeant les circuits sensibles contre les variations de tension.

---

#### 🧩 Sous-système de commande
Le cœur du système repose sur un **STM32G431CBU6** (ARM Cortex-M4).  
Il exécute un programme développé sous **STM32CubeIDE**, basé sur un **noyau temps réel FreeRTOS**.  
Le RTOS permet une gestion multitâche efficace entre les différents sous-systèmes :  
- lecture et traitement des capteurs,  
- gestion des moteurs,  
- analyse des données du LIDAR,  
- sélection du mode de fonctionnement (Chat ou Souris),  
- communication UART pour le débogage.  

Cette structure logicielle garantit une **réactivité élevée**, une **synchronisation précise** et un comportement stable même lors des déplacements rapides.

---

#### 📡 Sous-système d’acquisition
Le robot perçoit son environnement à l’aide de plusieurs capteurs complémentaires :  

- **LIDAR YDLIDAR X2 :** permet de balayer l’environnement sur 360° et de localiser les autres robots ou obstacles.  
  Les données sont transmises au microcontrôleur via **UART avec DMA** et traitées en temps réel.  

- **Accéléromètre ADXL343 :** détecte les **chocs, inclinaisons et vibrations**.  
  Il sert à repérer les collisions avec d’autres robots et a également été utilisé comme **arrêt d’urgence** lors des essais.  

- **Capteurs mécaniques Würth MITV** : ces **capteurs à levier mécanique** sont positionnés à l’avant du robot.  
  Lorsqu’un levier entre en contact avec le bord de la table, il déclenche un signal digital envoyé au STM32.  
  Ce signal interrompt la tâche de déplacement et inverse la direction du robot pour éviter toute chute.  
  Ce type de capteur est robuste, précis et réagit instantanément au contact, ce qui en fait une solution efficace pour la **détection de bordures** sur une table sans limites physiques.  

---

#### ⚙️ Sous-système de déplacement
Le mouvement est assuré par **deux moteurs DC**, chacun piloté par un **driver ZXBM5210-SP-13**.  
Les moteurs sont commandés par des signaux **PWM** générés par le STM32, permettant d’ajuster la **vitesse** et la **direction**.  
Cette configuration différentielle offre la possibilité :  
- d’avancer ou reculer,  
- de pivoter sur place,  
- et de modifier la trajectoire selon les données des capteurs.  

L’intégration à FreeRTOS assure des réactions immédiates aux événements tels qu’un bord détecté ou une collision.

---

#### 🧰 Interface utilisateur
L’interface du robot comprend :  
- un **interrupteur général** d’alimentation,  
- un **bouton de démarrage**,  
- une **LED d’état** indiquant le mode de fonctionnement,  
- un **connecteur SWD** pour la programmation et le débogage via ST-Link.  

Cette interface simple permet une utilisation rapide et un suivi visuel du fonctionnement du robot.

---

#### 🧠 Fonctionnement global
Lors de la mise sous tension, le **STM32** initialise tous les périphériques (UART, I²C, PWM, GPIO) et lance le **noyau FreeRTOS**.  
Les tâches s’exécutent en parallèle :  
- les **capteurs mécaniques MITV** détectent physiquement les bords,  
- le **LIDAR** balaie la zone et transmet les positions d’obstacles,  
- l’**accéléromètre** surveille les collisions,  
- et la logique logicielle choisit la réaction selon le mode actif.  

En **mode Chat 🐱**, le robot analyse la position de son adversaire et se dirige vers lui.  
En **mode Souris 🐭**, il cherche au contraire à maintenir la plus grande distance possible tout en évitant les bords.  

Cette coordination entre capteurs, actionneurs et logiciel embarqué confère au robot **autonomie**, **réactivité** et **stabilité**.

---

✅ **En résumé**, le robot **CATRONIC** illustre un système embarqué complet combinant :
- **conception électronique et routage PCB**,  
- **programmation multitâche en temps réel**,  
- **intégration de capteurs mécaniques et numériques**,  
- et **prise de décision autonome**.  

Il représente une réalisation complète de la robotique embarquée : perception, décision et action.


