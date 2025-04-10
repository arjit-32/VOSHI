# VOSHI - A Stylish Minimal Shell

VOSHI stands for Visual Operating System Handling Interface. To sum up its

> A lightweight, interactive shell with emoji-powered prompts, Git awareness, custom dashboard at your fingertips. 

---

## ✨ Features

- 🚀 Aesthetic, color-coded Powerline-style prompt
- 📁 Git branch display inside the prompt
- 🧠 **Built-in `v` dashboard** shows:
  - System uptime, memory, disk stats  
  - Current weather  
  - Latest from Hacker News & TechCrunch  
- 📁 Supports classic shell operations: `cd`, `exit`, external commands  
- 🎨 **ASCII splash** and emoji-enhanced UX  

---

## 🔗 Download
📦 Download the latest .deb package via []().

---

## 📦 Installation

### Option 1: Install the `.deb` package (Debian/Ubuntu)
```bash
sudo dpkg -i voshi_1.0.0_amd64.deb
```

⚠️ If there are missing dependencies, run:
```bash
sudo apt --fix-broken install
```

### Option 2: Build from source
```bash
git clone https://github.com/yourusername/voshi.git
cd voshi
make
```

## 🧑‍💻 Usage
Start voshi by simply running:

```bash
voshi
```

🔧 Built-in Commands
| Command     | Description                                     |
|-------------|-------------------------------------------------|
| `cd <dir>`  | Change the current working directory to `<dir>`. |
| `exit`      | Terminate the VOSHI shell.                      |
| `v`         | Launch the interactive VOSHI dashboard.         |
| `<command>` | Execute any standard system command.            |


## 🛠️ Dependencies
Make sure these are installed for full dashboard features:

```bash
sudo apt install figlet curl jq neofetch
```

# How It Works 🔧
- `fork()` command is creating a new child process ( exact copy of parent). Both run independently, can use `wait` to get a bit deterministic.
- `execvp` command replaces current process with new program, essentially changing the program.
- `cd` is not a system command
- `perror` is used for system calls related erros
- Singal Handling: A interrupt that is sent to running process by kernel, ex - CTRL+Z which generates `SIGINT`. Can make custom signal handler using `signal` function.

## Other Info 🤝
- Inspired by [Indradhanush Gupta's great guide](https://igupta.in/blog/writing-a-unix-shell-part-2/)
- Feel free to open issues or submit PRs.
- Future plans: A Playground for it to see it run in the browser.

---



