┌───────────────────────────┐

│         main.cpp          │

│ - Interface GUI SFML 3    │

│ - Mode CVD1 (Lossless/O)  │

│ - Mode CVD2 (Lossy/P)     │

└─────────────┬─────────────┘

&#x20;             │

&#x20;             ▼

┌───────────────────────────┐      ┌──────────────────────────┐

│         Encoder           │      │       FileCVD            │

│ - Bit-Plane Mapping       │ <──> │ - Signature "CVD"        │

│ - 1 Bit == 1 Pixel        │      │ - Flux Binaire Séquentiel │

└─────────────┬─────────────┘      └──────────────────────────┘

&#x20;             │

&#x20;             ▼

┌───────────────────────────┐      ┌──────────────────────────┐

│      HybridDecimal        │      │       ZoomHandler        │

│ - Gestion des Chunks      │      │ - Antialiasing           │

│ - Stockage Arbitraire     │      │ - Rendu Bilinéaire       │

└───────────────────────────┘      └──────────────────────────┘



