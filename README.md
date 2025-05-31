# 🧠 Projet TFE – OS embarqué 

## 🎯 Objectif général

Développer un **système d’exploitation embarqué minimaliste** pour microcontrôleur ATmega, comprenant :
- un **noyau en C pur sans bibliothèque externe**,
- un **langage fonctionnel interprété** (type Lisp/Scala),
- une **interface REPL** via UART,
- un **système de fichiers simplifié** (EEPROM ou RAM),
- une **event loop asynchrone** pour gérer du pseudo-multitâche.
- un **HAL** maison
---

## ⚙️ Spécifications techniques

### 🖥️ Plateforme matérielle

- **Microcontrôleur** : ATmega328P (option : ATmega1284P)
- **Architecture** : 8 bits AVR RISC @ 16 MHz
- **Mémoire** :
  - Flash : 32KB (328P) / 128KB (1284P)
  - SRAM : 2KB (328P) / 16KB (1284P)
  - EEPROM : 1KB (328P) / 4KB (1284P)
- **Périphériques** : UART, GPIO, Timers, Interruptions

---

## 🧱 Architecture logicielle

### 🔧 Noyau (C pur, bas niveau)

- Initialisation matérielle (UART, timers, EEPROM)
- Gestion mémoire manuelle (type `malloc`/`free`)
- Pas de lib externe ni d’OS hôte
- Interface système exposée au langage

---

### 🧩 HAL maison (abstraction bas niveau)

- Développement d’un **HAL minimale maison** pour manipuler les périphériques
- Organisation modulaire :
  - `uart.c/h`, `timer.c/h`, `gpio.c/h`, etc.
- Inspirée de `libopencm3`, mais spécifique AVR
- Accès direct aux registres via `#define` et `volatile`
- Objectif : **clarifier le code noyau** et **isoler la logique matérielle**
- Repose uniquement sur la **documentation technique officielle (datasheet)**

---

### 🔁 Event Loop multitâche (style Node.js)

- **Boucle centrale** coopérative et asynchrone
- **Callback** côté user
- Gestion :
  - Timers (`setTimeout`, `setInterval`)
  - Événements IO (UART, GPIO)
  - Queue d’événements FIFO
- Primitives exposées dans le langage (exemple):
  - `emit(event, value)`
  - `on(event, handler)`
  - `setTimeout(fn, delay)`
  - `setInterval(fn, delay)`

---

### 🧠 Langage interprété (fonctionnel)

- Syntaxe minimaliste type Lisp
- Évaluation stricte
- Fonctions : `lambda`, `let`, `if`, `print`, etc.
- Structures de base : listes, paires
- Intégré à l’event loop
- Utilisable comme shell via REPL

---

### 💻 Interface utilisateur (REPL série)

- Interface UART
- Lecture de code ligne par ligne
- Exécution directe ou chargement de scripts
- Réponses et logs via série

---

### 📦 Système de fichiers

- Stockage simple sur EEPROM ou RAM
- Modèle clé/valeur ou séquentiel simple
- Commandes : `save`, `load`, `delete`, etc.
- Scripts interprétables directement

---

## 🔒 Sécurité / Isolation

- Pas de distinction kernel/user : monde plat
- Isolation logique des "pseudo-processus"
- Gestion mémoire surveillée manuellement

---


## 🎓 Intérêt pédagogique

- Projet bas niveau, **100 % fait main**
- Réalisation complète d’un OS embarqué cohérent
- Introduction à la conception de langages
- Intégration d’un modèle d’exécution moderne (event loop)
- Apprentissage approfondi de l'architecture matérielle AVR
- Mise en œuvre d'un HAL "from scratch" : lecture, abstraction, encapsulation des registres

## 🧰 🔤💡 Optionnel : Mode Standalone (Clavier + Écran LCD)

### 🧾 Objectif

Permettre à l’utilisateur d’interagir **sans PC**, uniquement via :
- un **clavier PS/2** ,
- un **écran LCD HD44780** (16x2 ou 20x4 caractères).