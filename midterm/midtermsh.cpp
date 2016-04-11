#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;


int main(int argc, char* argv[]) {
    while(true) {
        write(STDOUT_FILENO, "\n$", 2);
        vector<vector<string> >* vec = new vector<vector<string> >();
        string s = "";
        ssize_t count = 0;
        char *buf;
        const size_t BUF_SIZE = 1024;
        buf = new char[1024];
        int target = STDIN_FILENO;
	bool b = false;
        while (count = read(target, buf, BUF_SIZE)) {
	    b = true;
            if (buf[count - 1] == '\n') {
                if (count == 1) {
                    return 0;
                }
                s.append(buf);
                break;
            } else {
                s.append(buf);
            }
        }
	if (!b) return 0;
        vec->push_back(vector<string>());
        unsigned j = 0;
        int **pipes = new int*[vec->size()];
        for (unsigned i = 0; i < s.length(); i++) {
            if (s[i] == ' ' || i == s.length() - 1) {
                vec->back().push_back(s.substr(j, i - j));
                j = i + 1;
            } else if (s[i] == '|') {
                vec->push_back(vector<string>());
                j = ++i + 1;
            }
        }
        pid_t* id = new pid_t[vec->size()];
        for (unsigned i = 0; i < vec->size(); i++) {
            pipes[i] = new int[2];
            pipe2(pipes[i],O_CLOEXEC);
        }
        const char **arg = new const char*[vec->size()];
        const char ***args = new const char **[vec->size()];
        for (unsigned i = 0; i < vec->size(); i++) {
            arg[i] = vec[0][i][0].c_str();
            args[i] = new const char*[vec[0][i].size()];
            for (j = 0; j < vec[0][i].size(); j++) {
                args[i][j] = vec[0][i][j].c_str();
            }
        }
        for (unsigned i = 0; i < vec->size(); i++) {
            id[i] = fork();
            if (id[i] == 0) {
                if (i != 0) {
                    dup2(pipes[i - 1][0], STDIN_FILENO);
                }
                if (i != vec->size() - 1) {
                    dup2(pipes[i][1], STDOUT_FILENO);
                }
                _exit(execvp(arg[i], const_cast<char *const *>(args[i])));
            }
        }
        for (unsigned i = 0; i < vec->size(); i++) {
            close(pipes[i][1]);
            close(pipes[i][0]);
        }
        for (unsigned i = 0; i < vec->size(); i++) {
            waitpid(-1, 0, 0);
        }

    }
}