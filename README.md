# 🤖 CATRONIC

**Projet académique – ENSEA 2025/2026**

---

## 👩‍💻 Équipe de projet
- **AFIF Ikram**
- **AIT ALLA Hajar**
- **MENJLI Fakhri**


---
## 🧠 Introduction
Le projet **CATRONIC** consiste à développer un **robot autonome** capable de jouer au **chat et à la souris** avec d’autres robots du même type.  
Les robots évoluent sur une **table sans bordures**, ils doivent donc **détecter les bords** afin d’éviter toute chute.  

Le robot repose sur un **microcontrôleur STM32** et applique des **principes de système temps réel** pour gérer la communication entre ses composants matériels et logiciels.  
Il dispose de deux modes de fonctionnement :  

- **Mode Chat 🐱 :** le robot poursuit le robot adverse.  
- **Mode Souris 🐭 :** le robot fuit le robot adverse.  

L’alimentation est assurée par une **batterie NiMH 7.2 V**, et le robot intègre plusieurs capteurs tels qu’un **accéléromètre ADXL343**, un **LIDAR YDLIDAR X2**, et des **capteurs de bordure**.

---

## 🎯 Objectifs du projet
- Concevoir une carte électronique complète sous **KiCad**.  
- Programmer le **STM32** avec **FreeRTOS** pour la gestion multitâche.  
- Contrôler les **moteurs DC** à l’aide de drivers PWM.  
- Intégrer les **capteurs LIDAR, accéléromètre et capteurs fin de course**.  
- Assurer la **détection des collisions et bords de table**.  
- Mettre en œuvre une **communication UART et I²C** entre les périphériques.  

---

## ⚙️ Matériel et composants utilisés
| Composant | Référence | Fonction |
|------------|------------|-----------|
| Microcontrôleur | **STM32G431CBU6** | Gestion du système temps réel |
| Driver moteur | **ZXBM5210-SP-13** | Commande des moteurs DC (PWM) |
| Accéléromètre | **ADXL343BCCZ-RL** | Détection des chocs et inclinaisons |
| LIDAR | **YDLIDAR X2** | Détection des obstacles et adversaires |
| Régulateur 5 V | **MP1475S** | Alimentation du LIDAR |
| Régulateur 3.3 V | **BU33SD5WG-TR** | Alimentation du STM32 et capteurs |
| Batterie | **NiMH 7.2 V 1.3 Ah** | Source d’alimentation principale |
| Capteurs bordure | **GP2Y0A41SK0F** | Détection de table et vide |
| Connecteurs | **JST 2.54 mm** | Liaison entre modules |
| LEDs + Résistances | **0603** | Indication d’état et debug |

---
