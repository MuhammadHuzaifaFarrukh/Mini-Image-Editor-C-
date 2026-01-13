# Mini Image Editor 🎨

A robust C++ command-line application for processing and editing **PGM (Grayscale)** and **PPM (RGB)** images. This project demonstrates core Object-Oriented Programming (OOP) principles while providing a functional tool for image manipulation in both **Text (ASCII)** and **Binary** formats.

---

## 🖼️ Visual Samples
Here are some examples of the filters applied using this editor:

| Original (Grayscale) | Posterized Filter | Thresholding |
| :---: | :---: | :---: |
| ![Grayscale](./test/some%20sample%20outputs/grayscale.png) | ![Posterized](./test/some%20sample%20outputs/posterized.png) | ![Threshold](./test/some%20sample%20outputs/threshold.png) |

---

## 🚀 Key Features

### 🖼️ Supported Formats
* **PPM (Portable Pixmap):** Full-color RGB images (P3 for Text, P6 for Binary).
* **PGM (Portable Graymap):** Grayscale images (P2 for Text, P5 for Binary).

### 🛠️ Image Operations
| Category | Included Filters & Transformations |
| :--- | :--- |
| **Geometry** | Resize (Stretch/Compress), Flip Horizontal/Vertical, Rotate Clockwise (90°), and Region Cropping. |
| **Enhancements** | Brighten, Darken, Invert Colors, and Auto-Contrast adjustment. |
| **Advanced** | Box Blur, Sharpening, Thresholding (Black/White), and Posterization (Color Level Reduction). |
| **Utilities** | Horizontal Image Merging, Customizable Borders/Frames, and PPM to PGM Grayscale conversion. |

---

## 🏗️ Technical Architecture

This project is built using a modular OOP approach to ensure code reusability and clean memory management:

* **Inheritance:** The `Coloured` class inherits from `Gray_Scale_Image`, extending its functionality from 1-channel to 3-channel data.
* **Polymorphism:** Uses `virtual` functions for `read()`, `write()`, and `convert_to_grayscale()` to handle different pixel structures dynamically.
* **Memory Management:** Implements custom destructors to prevent memory leaks when manipulating large pixel arrays.
* **Encapsulation:** Protects internal image data (width, height, pixel pointer) while providing public interfaces for manipulation.

---

## 📥 Getting Started

### Prerequisites
* A C++ compiler (e.g., `g++`)
* Terminal/Command Prompt with ANSI color support (recommended for the UI).

### How to Run :
* All files must be in the same folder or you may give their paths for each file
* You can include all the .cpp files in the main.cpp or you may just write every single .cpp file in the command
* Read each image to perform operation on 
