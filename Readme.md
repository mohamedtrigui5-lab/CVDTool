# CVD-BitMatrix™ (formerly CVD Tool)
### High-Performance Bit-Plane Layered Image Compression (CVD1 & CVD2)

## 🚀 L'Invention : Bit-Plane Layered Sequencing
CVD-BitMatrix™ (Color-Vector-Decimal) est un projet de recherche introduisant un **processus d'encodage révolutionnaire**. La technologie réside dans la décomposition séquentielle d'une image en couches binaires (Bit-Planes) affectées à des signatures colorimétriques uniques. 

Contrairement aux formats classiques (JPG/PNG), cette approche permet d'allier la précision du raster à la flexibilité du vectoriel, tout en atteignant des ratios de compression dépassant **1000:1**, indépendamment de l'architecture cible (CPU, GPU ou consoles anciennes).

---

## 📊 Performances Records (Observées)
Basé sur des tests réels (Images HD/AI), CVD-BitMatrix™ surclasse les standards actuels dans des scénarios spécifiques :


| Format | Type | Gain de compression | Taille PNG | Taille CVD-BitMatrix | Ratio |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **CVD1** | **Lossless** | Jusqu'à 85% | 17 Ko | **2.1 Ko** | ~8:1 |
| **CVD2** | **Lossy** | Jusqu'à 99.9% | 13 000 Ko | **12 Ko** | **1084:1** |

- **Ratio Record :** Réduction de la taille par **1084x** (Mode CVD2).
- **Vitesse :** Encodage et décodage optimisés grâce à l'accès direct aux bits (Complexité O(N)).

---

## ✨ Caractéristiques Clés (Key Features)
- **Extreme Compression :** Ratios dépassant 1000:1 pour les résolutions HD, 8K et 16K.
- **Bit-Plane Mapping :** Chaque couleur est stockée comme un flux binaire continu (1 bit = 1 pixel).
- **HybridDecimal Engine :** Gestion haute performance des flux binaires massivement longs.
- **Vector-like Zoom :** Support natif du Zoom dynamique avec lissage bilinéaire (Antialiasing).

---

## 🧠 L'Algorithme : "Bit-Plane Layering"
Le concept repose sur la transformation d'une image en un flux binaire pur où **1 bit = 1 pixel**.

### 1. Encodage (Mapping Binaire)
- **Extraction de Palette :** Analyse des couleurs uniques (avec tolérance configurable pour le mode CVD2).
- **Séquençage Binaire :** Pour chaque couleur, un flux de bits est généré où le (N)-ième bit correspond au (N)-ième pixel de l'image (balayage horizontal).
    - `1` : Le pixel possède cette couleur.
    - `0` : Le pixel ne possède pas cette couleur.
- **Optimisation Sparse :** Seules les couches de couleurs actives sont stockées ; le "silence binaire" (zones vides) est ignoré.

### 2. Décodage (Reconstruction Vectorielle)
- Le décodeur lit le flux binaire de gauche à droite.
- Il **"invente" la position du pixel** mathématiquement à partir de l'index du bit :  
  `x = index % Width` ; `y = index / Width`.
- **Résultat :** Une reconstruction fidèle sans aucun besoin de sauvegarder des masques de coordonnées complexes.

---

## 📈 Visualisation du Flux
```text
[Séquençage par Couleurs]
┌───────────────────────────────────────────┐
│ Couleur A (32 bits)                       │
│ [10001101... bitstream de taille WH]      │ <-- 1 bit par pixel
├───────────────────────────────────────────┤
│ Couleur B (32 bits)                       │
│ [01110010... bitstream de taille WH]      │
└───────────────────────────────────────────┘
          |
          v
[Fichier Final .CVD]
- Signature (3 octets)
- Résolution (4+4 octets)
- Blocs de données compressés (Entropy Coding)
