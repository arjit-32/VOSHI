#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <linux/limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
#define YELLOW "\033[1;33m"
#define MAGENTA "\033[1;35m"
#define RED "\033[1;31m"
#define WHITE "\033[1;37m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

// Icons & Symbols
#define FOLDER_ICON "\U0001F4C1 "   // 📁
#define PROMPT_ICON "\U0001F680 "   // 🚀
#define COMPUTER_ICON "\U0001F4BB " // 💻
#define BRANCH_ICON "\U0001F33F "   // 🌿

// Get the current Git branch (if inside a Git repo)
char *get_git_branch() {
    static char branch[100];
    FILE *fp = popen("git rev-parse --abbrev-ref HEAD 2>/dev/null", "r");
    if (fp == NULL) return "";
    if (fgets(branch, sizeof(branch), fp) != NULL) {
        branch[strcspn(branch, "\n")] = '\0'; // Remove newline
        pclose(fp);
        return branch;
    }
    pclose(fp);
    return "";
}

// Construct the aesthetic Powerline-style prompt
char *get_prompt() {
    static char prompt[PATH_MAX + 300];
    char cwd[PATH_MAX];
    char *git_branch = get_git_branch();

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd failed");
        return NULL;
    }

    // Define background colors
    #define BG_DARKGRAY  "\033[48;5;236m"
    #define BG_BLUE      "\033[48;5;24m"
    #define BG_MAGENTA   "\033[48;5;90m"

    snprintf(prompt, sizeof(prompt),
        "\n" BOLD YELLOW BG_DARKGRAY " \u256d\u2500[" RESET GREEN COMPUTER_ICON " %s@voshi " RESET BG_DARKGRAY "]"
        " \u2500[" RESET BG_BLUE FOLDER_ICON " %s " RESET BG_DARKGRAY "]",
        getenv("USER"), cwd);

    if (strlen(git_branch) > 0) {
        snprintf(prompt + strlen(prompt), sizeof(prompt) - strlen(prompt),
            " \u2500[" RESET BG_MAGENTA BRANCH_ICON " %s " RESET BG_DARKGRAY "]", git_branch);
    }

    snprintf(prompt + strlen(prompt), sizeof(prompt) - strlen(prompt),
        "\n" BG_DARKGRAY " \u2570\u2500\u279c " RESET " ");

    return prompt;
}


// Function to show a simple loading animation
void show_loading(const char *message, int duration) {
    const char spinner[] = "|/-\\";
    printf("%s ", message);
    fflush(stdout);
    
    for (int i = 0; i < duration; i++) {
        printf("%c\b", spinner[i % 4]); // Rotate spinner
        fflush(stdout);
        usleep(200000); // 200ms delay
    }
    printf("✅\n"); // Mark as done
}

void show_dashboard() {
    system("clear");
    printf(GREEN BOLD "\U0001F4CA  voshi Dashboard\n" RESET);
    printf("============================================\n");

    // System Info
    printf(CYAN BOLD "\n\U0001F4BB System Info:\n" RESET);
    system("uptime -p | sed 's/^/   ⏳ Uptime: /'");
    system("free -h | awk '/^Mem/ {print \"   🏋️ RAM: \"$3\" / \"$2}'");
    system("df -h --output=avail / | tail -n1 | sed 's/^/   💾 Disk Space: /'");

    // Weather
    printf(BLUE BOLD "\n\U0001F321  Weather:\n" RESET);
    show_loading("Fetching weather...", 5);
    system("curl -s wttr.in/Dehradun?format=3 | sed 's/^/   🌍 /'");

    // Tech News (Fixed Faster Hacker News Fetching)
    printf(MAGENTA BOLD "\n\U0001F4F0  Tech News (Hacker News):\n" RESET);
    show_loading("Fetching latest headlines...", 8);
    system("curl -s \"https://hacker-news.firebaseio.com/v0/topstories.json\" | jq -r '.[0:5] | map(\"https://hacker-news.firebaseio.com/v0/item/\"+tostring+\".json\") | join(\" \")' | xargs curl -s | jq -r '. | \"   🔹 \" + .title + \"\n      🔗 \" + .url + \"\n\"'");

    // TechCrunch News (Fixed `grep` issue)
    printf(YELLOW BOLD "\n\U0001F426  TechCrunch Latest News:\n" RESET);
    show_loading("Fetching latest articles...", 6);
    system("curl -k -s -A \"Mozilla/5.0\" https://techcrunch.com/feed/ | grep -oP '(?<=<title>).*?(?=</title>)' | tail -n +3 | head -5 | sed 's/^/   📰 /'");

    printf("\nPress ENTER to return to voshi...\n");
    getchar();
    system("clear");
}


// SIGINT handler (Ctrl+C)
void sigint_handler(int signo) {
    if (signo == SIGINT) {
        printf("\n\n" RED "Use \"exit\" to quit voshi.\n" RESET);
        fflush(stdout);
    }
}

// Main loop
void loop() {
    char *input;
    char *args[100];
    int quit = 0;

    using_history();

    do {
        input = readline(get_prompt());
        if (!input) {
            printf("\nExiting voshi...\n");
            exit(0);
        }

        if (strlen(input) == 0) {
            free(input);
            continue;
        }

        add_history(input);

        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL && i < 99) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0) {
            quit = 1;
        } else if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, RED "cd: missing argument\n" RESET);
            } else if (chdir(args[1]) != 0) {
                perror("cd failed");
            }
        } else if (strcmp(args[0], "v") == 0) {
            show_dashboard();
        } else {
            pid_t pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
                fprintf(stderr, RED "voshi: command not found: %s\n" RESET, args[0]);
                exit(1);
            } else {
                wait(NULL);
            }
        }

        free(input);
    } while (!quit);
}

// Display system info
void show_system_info() {
    system("clear");
    printf(GREEN "\U0001F680 Welcome to voshi!\n" RESET);
    printf(CYAN "\U0001F4BB System Info:\n" RESET);
    system("neofetch --off 2>/dev/null || uname -a");
    printf("\n");
}

// Main function
int main() {
    signal(SIGINT, sigint_handler);
    show_system_info();
    loop();
    return 0;
}