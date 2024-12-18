#include <iostream>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <cstring>
#include <ctime>
#include <ucontext.h>

using namespace std;

void signal_handler(int signal, siginfo_t *info, void *context) {
    cout << "Inside signal handler" << endl;
    pid_t sender_pid = info->si_pid;
    uid_t sender_uid = info->si_uid;

    struct passwd *pw = getpwuid(sender_uid);
    const char *sender_username = pw ? pw->pw_name : "unknown";

    cout << "Received a SIGUSR1 signal from process " << sender_pid << " executed by " << sender_uid << " (" << sender_username << ")" << endl;

    ucontext_t* uc = (ucontext_t*)context;

    cout << "State of the context: RIP = " << uc->uc_mcontext.gregs[REG_RIP]
         << ", RAX = " << uc->uc_mcontext.gregs[REG_RAX]
         << ", RBX = " << uc->uc_mcontext.gregs[REG_RBX] << endl;
}

int main() {
    pid_t pid = getpid();
    cout << "Process ID: " << pid << endl;

    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    cout << "Program is waiting for SIGUSR1 signal..." << endl;

    while (true) {
        sleep(10);
    }

    return 0;
}
