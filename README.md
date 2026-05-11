# Robot Chariot — Programmation Arduino

> Mini-projet étape par étape pour apprendre à programmer en Arduino — 2025/2026

---

## 📖 Présentation du projet

Dans le cadre d'une unité de conditionnement industriel, ce projet vise à concevoir et programmer un **système de convoyage automatisé** (robot chariot) permettant de déplacer des pièces entre deux postes :

- **Point A** — poste de montage opérateur
- **Point B** — magasin de stockage

Un affichage indique en permanence la position et l'état du chariot tout au long du cycle.

---

## 🎯 Fonctionnalités du robot

- ✅ Déplacement automatique entre le point A et le point B
- ✅ Affichage de l'état du robot sur un **afficheur LCD**
- ✅ Signalisation de la position par un **signal sonore** (buzzer)

---

## 🔌 Architecture matérielle

### Principe de fonctionnement

Le chariot se déplace entre A et B. Les positions sont détectées par deux **capteurs TOR fin de course** :

| Signal | Description | Type |
|--------|-------------|------|
| `fcg`  | Fin de course au **point A** (gauche) | Entrée |
| `fcd`  | Fin de course au **point B** (droite) | Entrée |
| `dcy`  | Bouton **départ cycle** | Entrée |
| `ledav` | LED simulation **moteur avant** | Sortie |
| `ledar` | LED simulation **moteur arrière** | Sortie |

> En phase de simulation (TinkerCad / Proteus), les fins de course sont remplacés par des **boutons poussoirs**, et les moteurs par des **LEDs**.

---

## 🗂️ Versions du projet

### V1 — Cycle d'un aller-retour

**Objectif :** Réaliser un unique cycle de convoyage A → B → A.

**Comportement attendu :**
- Le chariot démarre en position initiale au **point A**
- Une impulsion sur `dcy` déclenche la **marche avant** (`ledav = 1`, `ledar = 0`)
- À l'arrivée au **point B** (`fcd = 1`), le chariot s'immobilise **4 secondes** (chargement)
- Le chariot repart en **marche arrière** (`ledav = 0`, `ledar = 1`)
- À l'arrivée au **point A** (`fcg = 1`), le chariot s'immobilise

**Affichage moniteur série :** état courant du chariot (position initiale, marche avant, marche arrière, point B)

**Diagramme d'états SysML :**

```
              [dcy = 1]
Immobile A ────────────────► Avance
(ledav=0, ledar=0)            (ledav=1, ledar=0)
     ▲                               │
     │                          [fcd = 1]
     │                               ▼
     │                        Immobile B
     │                        └─ Attendre 4s
     │                               │
     │                          [fcg = 0]
     │                               ▼
     │                            Recule
     │                        (ledav=0, ledar=1)
     │                               │
     └───────────────────────── [fcg = 1, fcd = 0]
```

---

### V2 — Répétition de cycles

**Objectif :** Effectuer **3 allers-retours** consécutifs après une impulsion sur `dcy`.

**Comportement attendu :**
- Déclenchement par une impulsion sur `DCY` depuis le point A
- 3 allers-retours complets entre A et B
- **4 secondes d'immobilisation** à chaque extrémité (chargement en B, déchargement en A)
- Affichage sur le moniteur série : état du chariot + **nombre d'allers-retours effectués**

---

### V3.1 — Intégration de signal sonore

**Objectif :** Ajouter des bips sonores via un **buzzer Piezo**.

**Comportement attendu :**

| Signal sonore | Déclencheur | Fréquence | Nombre de bips | Cadence |
|---------------|-------------|-----------|----------------|---------|
| `SON_AB`      | Arrivée en A ou B | 440 Hz | 2 bips | 1 Hz |
| `SON_FCY`     | Fin de cycle complet | 880 Hz | 3 bips | 1 Hz |

**Fonctions Arduino utilisées :**
```cpp
tone(broche, fréquence);   // Émet un son
noTone(broche);            // Arrête le son
```

---

### V3.2 — Refactorisation avec fonctions

**Objectif :** Améliorer la **lisibilité et la maintenabilité** du code en créant des fonctions dédiées aux sons.

**Fonctions à créer :**
```cpp
//======= Fonction SON_AB =======
void son_AB() {
  // 2 bips à 440 Hz, cadence 1 Hz
}

//======= Fonction SON_FCY =======
void son_FCY() {
  // 3 bips à 880 Hz, cadence 1 Hz
}
```

- Les fonctions sont placées en **fin de programme**
- Elles sont **appelées** aux moments appropriés dans la boucle principale
- Des commentaires séparateurs `//=======` délimitent visuellement chaque fonction

---

### V4 — Maquette du prototype physique

Une fois la maquette numérique validée, le projet est réalisé sur les **mallettes pédagogiques**.

#### V5.1 — Détection sans contact des points A et B

- Remplacement des fins de course par **2 capteurs à ultrasons** (arrêt à 10 cm des points A et B)
  
### V5.2 — Détection sans contact des points A et B avec un seul capteur ultrasson

- Ajout d'un **servomoteur** pour orienter le capteur à 180° selon le sens de déplacement (un seul capteur suffisant)
- Distance de détection : **15 cm**

#### V6 Déplacement sécurisé (zones sombres)

- Une **LED de visualisation** s'allume automatiquement lorsque la luminosité ambiante est insuffisante
- Son intensité est **inversement proportionnelle** à la lumière présente (plage : 0–300 lux)
- Extension : remplacement de la LED par une **lampe 12V** (montage à proposer)

#### Motorisation

- Ajout d'un **moteur continu** pour les déplacements bidirectionnels
- Ajout d'un **moteur par roue** pour faciliter l'évitement d'obstacles
- `ledav` et `ledar` **clignotent** pendant les phases de déplacement

---

## 🛠️ Outils & environnement

| Outil | Usage |
|-------|-------|
| [Arduino IDE](https://www.arduino.cc/en/software) | Programmation de la carte Arduino Uno |
| [Proteus](https://www.labcenter.com/) | Simulation de la maquette numérique |
| [TinkerCad](https://www.tinkercad.com/) | Simulation alternative en ligne |

---


## 📝 Consignes de rendu

Le travail est à remettre sous forme d'un **dossier zippé** déposé sur Teams, comprenant :

- Un **compte rendu** des activités réalisées (en suivant le plan du document Word fourni)
- Les projets Proteus renommés par version :
  - `V1` — 1 cycle de convoyage
  - `V2` — 3 cycles de convoyages
  - `V3.1` — Intégration de sons
  - `V3.2` — Création de fonctions
  - `V5.1` — Détection sans contact des points A et B
  - `V5.2` — Détection sans contact des points A et B avec un seul capteur ultrasson
  - `V6` — Déplacement sécurisé (zones sombres)

---

Projet réalisé par @Gwel  — 2025/2026
