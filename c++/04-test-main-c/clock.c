/*
    TODO
        * warning C4028: formal parameter 1 different from declaration
        the two event_new
*/
#ifndef _WIN32
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/types.h>
#include <sys/socket.h>
#endif
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include <event2/event.h>
// #include <event2/util.h>

#define DEFAULT_PORT 3333

static char g_clock[128];

static struct timeval TIMER_TV = {1, 0};

static void gettimeofday_cb(int nothing, short int which, void *ev)
{
    time_t rawtime;
    time(&rawtime);

    struct tm local_snapshot;
#if (defined(__MINGW32__) || defined(__MINGW64__))
    memcpy(&local_snapshot, localtime(&rawtime), sizeof(tm));
#elif (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
    localtime_s(&local_snapshot, &rawtime);
#else
    localtime_r(&rawtime, &local_snapshot); // POSIX
#endif

    strftime(g_clock, sizeof(g_clock), "%d/%m/%YT%T", &local_snapshot);

    evtimer_add(ev, &TIMER_TV);
}

static void udp_cb(const int sock, short int which, void *arg)
{
    struct sockaddr_in server_sin;
    socklen_t server_sz = sizeof(server_sin);
    struct event_base *base = arg;
    char buf[1024];

    /* Recv the data, store the address of the sender in server_sin */
    int size = recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr *) &server_sin, &server_sz);
    if (size == -1) {
        perror("recvfrom()");
        event_base_loopbreak(base);
    }
    buf[size] = '\0';

    printf("[udp_cb] client said: %s\n", buf);

    /* Copy the time into buf; note, endianess unspecified! */
    memcpy(buf, g_clock, strlen(g_clock));

    /* Send the data back to the client */
    if (sendto(sock, buf, (int)strlen(buf), 0, (struct sockaddr *) &server_sin, server_sz) == -1 ) {
        perror("sendto()");
        event_base_loopbreak(base);
    }
}

bool server()
{
    g_clock[0] = '\0';

#ifndef _WIN32
    int sock;
#else
    SOCKET sock;
#endif

#ifdef _WIN32
    WSADATA wsa_data;
    WSAStartup(0x0201, &wsa_data);
#endif

    struct event_base *base;
    struct event *timer_event, *udp_event;
    struct sockaddr_in sin;

    int port = DEFAULT_PORT;

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin))) {
        perror("bind()");
        // exit(EXIT_FAILURE);
        return false;
    }

    printf("Clock server started at %d ...\n", port);

    /* Initialize libevent */
    //  DEPRECATED: replaced with event_base_new
    //event_init();
    base = event_base_new();

    /* Add the clock event */
    timer_event = evtimer_new(base, &gettimeofday_cb, event_self_cbarg());
    evtimer_add(timer_event, &TIMER_TV);

    /* Add the UDP event */
    udp_event = event_new(base, sock, EV_READ|EV_PERSIST, udp_cb, event_self_cbarg());
    event_add(udp_event, 0);

    /* Enter the event loop; does not return. */
    event_base_dispatch(base);

    event_free(udp_event);
    event_free(timer_event);
    event_base_free(base);

#ifndef _WIN32
    close(sock);
#else
    closesocket(sock);
#endif

#ifdef _WIN32
    WSACleanup();
#endif

    return true;
}
