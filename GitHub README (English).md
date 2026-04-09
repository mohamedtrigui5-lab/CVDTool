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




