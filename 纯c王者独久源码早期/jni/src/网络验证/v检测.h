
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>

int isVpnConnected() {
    const char *vpn_interfaces[] = {
        "tun0", "tun1", "tun2", "ppp0", "pptp0",
        "tun11", "tun12", "tun13", "ppp1", "pptp1",
        "tun21", "tun22", "tun23",
        // VPN 接口名称
    };
    int num_vpn_interfaces = sizeof(vpn_interfaces) / sizeof(vpn_interfaces[0]);
    struct ifreq *ifr = NULL;
    struct ifconf ifc;
    ifc.ifc_len = 0;
    ifc.ifc_buf = NULL;
    
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
    if (sockfd < 0) {
        perror("socket");
        return -1;
    }
    
    if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0) {
        perror("ioctl");
        close(sockfd);
        return -1;
    }

    ifc.ifc_buf = (caddr_t)malloc(ifc.ifc_len);
    if (!ifc.ifc_buf) {
        perror("malloc");
        close(sockfd);
        return -1;
    }

    if (ioctl(sockfd, SIOCGIFCONF, &ifc) < 0) {
        perror("ioctl");
        close(sockfd);
        free(ifc.ifc_buf);
        return -1;
    }

    ifr = (struct ifreq *)ifc.ifc_buf;

    for (int i = 0; i < ifc.ifc_len / sizeof(struct ifreq); ++i) {
        if (ifr[i].ifr_addr.sa_family == AF_INET) {
            char name[IFNAMSIZ];
            strncpy(name, ifr[i].ifr_name, IFNAMSIZ);
            for (int j = 0; j < num_vpn_interfaces; ++j) {
                if (strcmp(name, vpn_interfaces[j]) == 0) {
exit(0);  
                   // printf("VPN interface detected: %s\n", name);
                    close(sockfd);
                    free(ifc.ifc_buf);
                    return 1;
                }
            }
        }
    }

    close(sockfd);
    free(ifc.ifc_buf);
    return 0;
}