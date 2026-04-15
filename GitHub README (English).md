---

⚠️ **Project Update – CVD-BitMatrix**

Hello everyone,

After several weeks of intensive research, testing, and iterations on CVD-BitMatrix, I would like to share an important update regarding the project.

During the initial release, some results were based on incorrect calculations and incomplete validation. These issues have since been carefully reviewed and analyzed.

Following deeper investigation, it appears that the performance levels initially observed cannot be reliably reproduced with the current approach. Further development has led to significantly different results, highlighting fundamental limitations in the current model.

As a result, I have decided to stop active development of this version of the project.

That said, this work remains a valuable research exploration into unconventional image compression techniques. It helped uncover important insights regarding matrix-based representations and their practical limits.

The repository will remain available for transparency and learning purposes.

I would like to thank everyone who provided feedback and support.

— Mohamed Trigui
---


** Project Status Update – CVD-BitMatrix**

After extensive research, testing, and multiple iterations, I have decided to stop active development of this project.

Initial results published earlier were based on incorrect calculations and assumptions, which have since been thoroughly reviewed and corrected.

Further investigation showed that achieving the previously claimed performance levels is not currently feasible with this approach.

This project has nevertheless been a valuable research exploration into unconventional image compression techniques, and it helped identify important limitations and challenges in this area.

The repository will remain available for transparency and educational purposes.

**Thank you for your support and interest.**

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
\# CVD-BitMatrix: Bit-Plane Layered Image Compression (CVD1 \& CVD2)



\## 🚀 Overview

CVD-BitMatrix (Color-Vector-Decimal) is a \*\*revolutionary image encoding algorithm\*\* that bridge the gap between raster and vector graphics. Instead of compressing pixel blocks (like JPG/PNG), CVD-BitMatrix decomposes images into \*\*sequential binary layers (Bit-Planes)\*\* for each unique color.



\### 📊 Performance Benchmarks (Real World)



| Format | Mode | Compression Gain | PNG Size | CVD-BitMatrix Size |

| :--- | :--- | :--- | :--- | :--- |

| \*\*CVD1\*\* | \*\*Lossless\*\* | \*\*Up to 85%\*\* | 17 KB | \*\*2 KB\*\* |

| \*\*CVD2\*\* | \*\*Lossy\*\* | \*\*Up to 99.9%\*\* | 13,000 KB | \*\*10 KB\*\* |



\## ✨ Key Features

\- \*\*Extreme Compression:\*\* Achieves ratios over 1000:1 on HD/AI-generated images.

\- \*\*Bit-Plane Mapping:\*\* Each color is stored as a continuous bitstream (1 bit = 1 pixel).

\- \*\*HybridDecimal Engine:\*\* Manages arbitrarily large binary streams for 8K/16K resolutions.

\- \*\*Vector-like Zoom:\*\* Native support for bilinear antialiasing during reconstruction.

\- \*\*High Speed:\*\* O(N) complexity with SIMD-ready architecture.



\## 🧠 The Algorithm

1\. \*\*Palette Extraction:\*\* Identifies unique colors (with configurable tolerance for CVD2).

2\. \*\*Binary Sequencing:\*\* For each color, a bitstream is generated where the N-th bit represents the N-th pixel of the image.

3\. \*\*Sparse Storage:\*\* Only active color layers are written to the `.cvd` file.

4\. \*\*On-the-fly Rendering:\*\* The decoder "invents" pixel positions from the bitstream index, allowing fast reconstruction and scaling.



\## 🛠 Requirements

\- C++17 or higher

\- SFML 3.0

\- Windows (Win32 API for File Dialogs)


### 🙏 Acknowledgments
This project was conceived and developed by Mohamed Trigui, with technical assistance from Gemini (Google) and ChatGPT (OpenAI) AI models for algorithmic optimization and debugging.




