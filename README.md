<a name="readme-top"></a>
<div align="center">
  <!-- Logo -->
  <a href="https://github.com/dpetrosy/Fractal">
  <img src="README_files/logo.png" alt="Logo" width="80" height="80">
  </a>

  <!-- Project Name -->
  <h1>Fractal Project</h1>

  <!-- Badges -->
  <p>
    <img src="https://img.shields.io/github/repo-size/dpetrosy/Fractal?style=for-the-badge&logo=github">
    <img src="https://img.shields.io/github/languages/count/dpetrosy/Fractal?style=for-the-badge&logo=" />
    <img src="https://img.shields.io/github/languages/top/dpetrosy/Fractal?style=for-the-badge" />
    <img src="https://img.shields.io/github/last-commit/dpetrosy/Fractal?style=for-the-badge" />
  </p>

  <h3>
    <a href="#-about-project">📜 About Project</a>
      <span> · </span>
    <a href="#-fractals-list">📑 Fractals List</a>
      <span> · </span>
	  <a href="#-controls">🎮 Controls</a>
      <span> · </span>
    <a href="#-usage">👨‍💻 Usage</a>
      <span> · </span>
    <a href="#-screenshots">🌄 Screenshots</a>
  </h3>
</div>

---

## 📜 About Project

A fractal is a fragmented geometrical figure that infinitely repeats at smaller scales. \
So this project generates beautiful fractals from the complex numbers of an iterative mathematical construct. \
For graphics, I used **SFML** library and **NVIDIA CUDA Toolkit** for parallel computing. \
Project builds by **CMake** build system, so if you do not have CUDA Toolkit or your platform doesn't have
CUDA support, CMake will build this project without CUDA support and computing will be done through CPU threads. \
By default, there will be 40 parallel threads, the color is rgb(21, 0, 0) and the window size is 800px.

> [!NOTE]  
> If you want to change color, threads count, window size, or other defaults, change them in helpers.hpp file.
