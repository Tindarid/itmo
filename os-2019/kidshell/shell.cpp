#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <map>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

std::map<string, string> env;

std::pair<string, string> resolve_var(const string& var) {
    size_t pos = var.find("=");
    string value = "";
    if (pos != string::npos) {
        value = var.substr(pos + 1);
    }
    return {var.substr(0, pos), value};
}

void export_var(const string& var) {
    auto entry = resolve_var(var);
    auto it = env.find(entry.first);
    if (it != env.end()) {
        it->second = entry.second;
    } else {
        env.insert(entry);
    }
}

void unset_var(const string& var) {
    auto it = env.find(var);
    if (it != env.end()) {
        env.erase(it);
    }
}

void set_env(char* envp[]) {
    while(*envp) {
        env.insert(resolve_var(*envp++));
    }
}

vector<string> get_env() {
    vector<string> res;
    for (auto&& e : env) {
        res.push_back(e.first + "=" + e.second);
    }
    return res;
}

void print_env() {
    for (auto&& e : get_env()) {
        cout << e << endl;
    }
}

void resolve_error() {
    int err = errno;
    cout << "Error: " << strerror(err) << endl;
}

vector<string> parse(const string& command) {
    vector<string> ans;
    std::stringstream ss(command);
    while (!ss.eof()) {
        string temp;
        ss >> temp;
        ans.push_back(temp);
    }
    return ans;
}

char** fill_args(const vector<string>& args) {
    size_t n = args.size();
    char** new_args = new char*[n + 1];
    for (size_t i = 0; i < n; ++i) {
        new_args[i] = const_cast<char*>(args[i].c_str());
    }
    new_args[n] = NULL;
    return new_args;
}

void execute(const vector<string>& args) {
    char** c_args = fill_args(args);
    vector<string> temp = get_env();
    char** e_args = fill_args(temp);
    if (execve(c_args[0], c_args, e_args) == -1) {
        resolve_error();
        delete[] c_args;
        delete[] e_args;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[], char *envp[]) {
    set_env(envp);
    while (true) {
        cout << "[" << getlogin() << "] ";
        string command;
        getline(cin, command);
        if (cin.eof()) {
            cout << "exit" << endl;
            break;
        }
        if (command.length() == 0) {
            continue;
        }
        vector<string> args = parse(command);
        size_t n = args.size();
        if (n == 1 && args[0] == "") {
            continue;
        }
        if (args[0] == "exit") {
            break;
        }
        if (args[0] == "unset") {
            for (size_t i = 1; i < n; ++i) {
                unset_var(args[i]);
            }
        } else if (args[0] == "export") {
            if (n == 1) {
                cout << "Usage: man export" << endl;
            } else if (args[1] == "-p" && n == 2) {
                print_env();
            } else {
                for (size_t i = 1; i < args.size(); ++i) {
                    export_var(args[i]);
                }
            }
        } else {
            const pid_t pid = fork();
            if (pid == -1) {
                resolve_error();
            } else if (!pid) {
                execute(args);
            } else {
                int wstatus;
                if (wait(&wstatus) == -1) {
                    resolve_error();
                } else {
                    cout << "Program exited with code " << WEXITSTATUS(wstatus) << endl;
                }
            }
        }
    }
}

