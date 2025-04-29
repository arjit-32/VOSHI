# VOSHI - A Stylish Minimal Shell

A lightweight, interactive shell with emoji-powered prompts, Git awareness, custom dashboard.

It was built as an academic exercise to understand operating systems.

> VOSHI stands for Visual Operating System Handling Interface or something else, who knows :)

---

## ✨ Features

✅ Aestheticand color-coded prompt <br>
✅ Git branch display inside the prompt <br>
✅ Built-in `v` dashboard shows News, System Info and Weather <br>
✅ Supports classic shell operations: `cd`, `exit`, external commands <br>
✅ History using (↑) <br>

---

## 🔗 Download
Download the latest .deb package via [VOSHI website](https://arjit-32.github.io/VOSHI/).

---

## 📦 Installation

### Option 1: Install the `.deb` package (Debian/Ubuntu)
```bash
sudo dpkg -i voshi_1.0.0_amd64.deb
```

If there are missing dependencies, run:
```bash
sudo apt --fix-broken install
```

### Option 2: Build from source
```bash
git clone https://github.com/yourusername/voshi.git
cd voshi
make
```
---

## 🧑‍💻 Usage
Start voshi by simply running:

```bash
voshi
```

Built-in Commands:
| Command     | Description                                     |
|-------------|-------------------------------------------------|
| `cd <dir>`  | Change the current working directory to `<dir>`. |
| `exit`      | Terminate the VOSHI shell.                      |
| `v`         | Launch the interactive VOSHI dashboard.         |
| `<command>` | Execute any standard system command.            |


*Note - If you wish to make voshi appear in your VSCode terminal options -* <br>
*1. Open Command Palette(Ctl+Shift+P) → Preferences: Open User Settings (JSON) <br>
2. Add the following snippet under your terminal profiles (adjust the path if needed):* <br>
```json
"terminal.integrated.profiles.linux": {
  "Voshi": {
    "path": "/usr/local/bin/voshi"
  }
},
"terminal.integrated.defaultProfile.linux": "Voshi"
```


---
## 🛠️ Dependencies
Make sure these are installed for full dashboard features:

```bash
sudo apt install figlet curl jq neofetch
```
---
# 🔧 How It Works 
- `fork()` command is creating a new child process ( exact copy of parent). Both run independently, can use `wait` to get a bit deterministic.
- `execvp` command replaces current process with new program, essentially changing the program.
- `cd` is not a system command
- `perror` is used for system calls related erros
- Singal Handling: A interrupt that is sent to running process by kernel, ex - CTRL+Z which generates `SIGINT`. Can make custom signal handler using `signal` function.

## 🤝 Other Info 
- Inspired by [Indradhanush Gupta's blogs](https://igupta.in/blog/writing-a-unix-shell-part-2/)
- Built this shell to better understand how operating systems work, learned a lot about processes, forking, wait(), and signal handling.
- If you find any mistakes (which there definitely might be), feel free to open an issue. Thanks!
- Future plans: A Playground for it to see it run in the browser.

---



