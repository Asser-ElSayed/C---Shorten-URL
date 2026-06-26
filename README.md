

---

```markdown
# 🔗 URL Shortener

A C++ command-line application that generates readable, compact short URLs from long ones — and resolves them back instantly. Backed by persistent file storage and an in-memory hash map for fast lookups.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Workflow](#workflow)
- [Generation Engine](#generation-engine)
- [Architecture](#architecture)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Data Persistence](#data-persistence)

---

## Overview

The URL Shortener takes a long URL as input and produces a human-readable, compact short link using a hybrid linguistic + Base62 encoding algorithm. Short links can be resolved back to the original URL instantly via an in-memory map loaded at startup.

---

## ✨ Features

| Feature | Description |
|---|---|
| **URL Shortening** | Generates slug-based short links with an unpredictable Base62 suffix |
| **URL Resolution** | Resolves short links back to the original URL in O(1) time |
| **Input Validation** | Enforces URL format rules before processing |
| **Duplicate Detection** | Prevents storing the same long URL twice |
| **Persistent Storage** | All mappings saved to `data.txt` and survive restarts |
| **In-Memory Speed** | All lookups use `std::unordered_map` loaded at startup |

---

## 🔄 Workflow

```
[System Startup]
└── Initialization
    ├── Open data.txt from the file system
    ├── Load all existing mappings into RAM (std::unordered_map)
    └── Retrieve the Global Counter (last ID used) to maintain sequence

[Main Menu]
├── Option A: Shorten a New URL
│   ├── Input Validation
│   │   ├── Must begin with http:// or https://
│   │   ├── Must contain a domain period (.)
│   │   ├── Must contain no whitespace characters
│   │   └── On failure → display error, return to menu
│   ├── Duplicate Check
│   │   ├── Scan map values for the same long URL
│   │   └── On duplicate → display error, return to menu
│   ├── Generation Engine  (see below)
│   └── Persistence & Output
│       ├── Append new mapping to data.txt
│       ├── Insert into the in-memory map
│       └── Display the shortened URL to the user
│
└── Option B: Resolve a Short Link
    ├── Format Integrity Check
    │   ├── Must contain the required separator (-)
    │   ├── Must be within a reasonable length range
    │   └── On malformed input → display error, return to menu
    └── Map Lookup (RAM)
        ├── Search map keys for the provided short link
        ├── On miss → display 404 error, return to menu
        └── On hit  → display the original long URL

[System Exit]
└── Final Save
    ├── Confirm global counter and latest mappings are written to data.txt
    └── Clear RAM and terminate
```

---

## ⚙️ Generation Engine

Short links are produced in four steps:

1. **Linguistic Slug** — Strip vowels and process the URL's domain/path into a concise, readable slug.
2. **Unpredictable Suffix** — Increment the global counter, then multiply by a prime salt to produce a non-sequential number.
3. **Base62 Encoding** — Convert the salted number into a compact alphanumeric string (`[0-9A-Za-z]`).
4. **Concatenation** — Join the slug and suffix: `<slug>-<base62>`.

**Example:**
```
Input:   https://www.example.com/some/long/path
Slug:    xmpl-pth
Suffix:  k3Z
Output:  xmpl-pth-k3Z
```

---

## 🏗️ Architecture

```
url-shortener/
├── main.cpp               # Entry point and menu loop
├── validator.hpp/.cpp     # URL and short-link format validation
├── generator.hpp/.cpp     # Slug + Base62 generation engine
├── repository.hpp/.cpp    # File I/O and in-memory map management
└── data.txt               # Persistent mapping store
```

| Component | Responsibility |
|---|---|
| `validator` | Format checks for both long URLs and short links |
| `generator` | Linguistic slug + salted Base62 suffix production |
| `repository` | `std::unordered_map` wrapper + `data.txt` read/write |

---

## 🚀 Getting Started

### Prerequisites

- C++17 or later
- CMake 3.15+
- MSVC 2019 / GCC / Clang

### Build

```bash
git clone https://github.com/your-username/url-shortener.git
cd url-shortener
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

### Run

```bash
./url-shortener
```

---

## 💻 Usage

```
============================================================
            URL Shortener — Main Menu
============================================================
  [A]  Shorten a new URL
  [B]  Resolve a short link
  [Q]  Quit
------------------------------------------------------------
Choice: A

Enter long URL: https://www.example.com/some/very/long/path
✔  Short link:  xmpl-pth-k3Z

------------------------------------------------------------
Choice: B

Enter short link: xmpl-pth-k3Z
✔  Original URL: https://www.example.com/some/very/long/path
```

---

## 💾 Data Persistence

All mappings are stored in `data.txt` as pipe-delimited records:

```
xmpl-pth-k3Z|https://www.example.com/some/very/long/path
gh-rls-7Qw|https://github.com/user/repo/releases/latest
```

The global counter (last used ID) is stored on the first line and updated on every write. On startup, the entire file is loaded into `std::unordered_map<std::string, std::string>` for O(1) resolution.

---

## 👥 Team

| Name | Role |
|---|---|
| Asser | Core engine & validation |
| Youssef Waleed | Repository & persistence layer |
| Mohamed Badie | Menu, UX & integration |
```

---

Structured to match the Job Scheduler README style — tree-based workflow, feature table, architecture table, and a usage block. Swap out the team roles and example output as needed.
