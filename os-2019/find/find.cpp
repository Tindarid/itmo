#include <stdio.h>
#include <vector>
#include <string>
#include <queue>
#include <stdexcept>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

using std::string;

enum size_intent {no, lower, equal, greater};

struct intent {
    bool wants_inum = false;      ino_t inum;
    bool wants_name = false;      string name;
    size_intent wants_size = no;  off_t size;
    bool wants_nlinks = false;    nlink_t nlinks;
    bool wants_exec = false;      string exec_path;
    bool good = false;            string data; 
};

std::pair<string, size_t> convert(const string& str) {
    try {
        return {"good", std::stoull(str)};
    } catch (std::invalid_argument &) {
        return {" is not a number", 0};
    } catch (std::out_of_range &) {
        return {" is too big", 0};
    }
}

intent parse_args(int argc, char *argv[]) {
    intent res;
    if (argc <= 1 || (argc - 2) % 2 != 0) {
        res.data = "Incorrect number of arguments";
        return res;
    }
    string incorrect = "Incorrect value: ";
    string for_flag = " for flag ";
    for (int i = 2; i < argc; i += 2) {
        string flag(argv[i]);
        string value(argv[i + 1]);
        if (flag == "-name") {
            res.wants_name = true;
            res.name = value;
            continue;
        }
        if (flag == "-exec") {
            res.wants_exec = true;
            res.exec_path = value;
            continue;
        }
        if (flag == "-inum") {
            res.wants_inum = true;
        } else if (flag == "-nlinks") {
            res.wants_nlinks = true;
        } else if (flag == "-size") {
            if (value.length() <= 1) {
                res.data = incorrect + value + for_flag + flag;
                return res;
            }
            switch (value[0]) {
                case '-':
                    res.wants_size = lower;
                    break;
                case '=':
                    res.wants_size = equal;
                    break;
                case '+':
                    res.wants_size = greater;
                    break;
                default:
                    res.data = incorrect + value + for_flag + flag;
                    return res;
            }
            value = value.substr(1);
        } else {
            res.data = "Incorrect option: " + flag;
            return res;
        }
        auto temp = convert(value);
        if (temp.first == "good") {
            if (flag == "-inum") {
                res.inum = temp.second;
            } else if (flag == "-nlinks") {
                res.nlinks = temp.second;
            } else {
                res.size = temp.second;
            } 
        } else {
            res.data = incorrect + value + temp.first + for_flag + flag;
            return res;
        }
    }
    res.data = argv[1];
    res.good = true;
    return res;
}

void print_usage() {
    printf("Usage: find [path] [options]\n");
    printf("Description: finds list of files, which satisfy predicate\n");
    printf("Options list:\n");
    printf("-size   [[-=+]number] : size in bytes (lower, equal, greater)\n");
    printf("-nlinks [number]      : number of links allowed\n");
    printf("-inum   [number]      : number of inode\n");
    printf("-name   [string]      : name of file\n");
    printf("-exec   [path]        : path of executable, which will get output\n");
}

void fill_queue(std::queue<std::pair<string, string>> &q, string d) {
    if (d.back() != '/') {
        d += "/";
    }
    auto data = d.data();
    DIR* dir = opendir(data);
    if (dir == NULL) {
        perror(data);
        return;
    }
    while (true) {
        errno = 0;
        dirent* next = readdir(dir);
        if (next == NULL) {
            if (errno != 0) {
                perror("");
            }
            break;
        }
        string path(next->d_name);
        if (path == "." || path == "..") {
            continue;
        }
        q.push({d + path, path});
    }
    if (closedir(dir) != 0) {
        perror("");
    }
}

bool check(const struct stat& sb, const intent& user, const string& name) {
    bool flag = true;
    if (user.wants_inum) {
        flag &= sb.st_ino == user.inum;
    }
    if (user.wants_name) {
        flag &= name == user.name;
    }
    if (user.wants_nlinks) {
        flag &= sb.st_nlink == user.nlinks;
    }
    switch (user.wants_size) {
        case lower:
            flag &= (sb.st_size < user.size);
            break;
        case equal:
            flag &= (sb.st_size == user.size);
            break;
        case greater:
            flag &= (sb.st_size > user.size);
            break;
        default:
            break;
    }
    return flag;
}

std::vector<string> bfs(const intent& user) {
    std::vector<string> res;
    std::queue<std::pair<string, string>> q;
    q.push({user.data, user.data});
    struct stat sb;
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        auto path = cur.first;
        auto name = cur.second;
        auto data = path.data();
        if (lstat(data, &sb) == -1) {
            perror(data);
            continue;
        }
        if (check(sb, user, name)) {
            res.push_back(path);
        }
        if ((sb.st_mode & S_IFMT) == S_IFDIR) {
            fill_queue(q, path);
        }
    }
    return res;
}

void exec(const string& executable, const std::vector<string>& args) {
    size_t n = args.size();
    char** c_args = new char*[n + 2];
    c_args[0] = const_cast<char*>(executable.c_str());
    for (size_t i = 1; i <= n; ++i) {
        c_args[i] = const_cast<char*>(args[i - 1].c_str());
    }
    c_args[n + 1] = NULL;
    if (execve(c_args[0], c_args, {NULL}) == -1) {
        perror(("While executing " + executable).data());
        delete[] c_args;
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    intent user = parse_args(argc, argv);
    if (!user.good) {
        printf("%s\n", user.data.data());
        print_usage();
        exit(EXIT_FAILURE);
    }
    auto list = bfs(user);
    if (user.wants_exec) {
        exec(user.exec_path, list);
    } else {
        for (auto&& entry : list) {
            printf("%s\n", entry.data());
        }
    }
    exit(EXIT_SUCCESS);
}
