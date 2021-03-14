import socket
import optparse

HOST = '127.0.0.1'  # Standard loopback interface address (localhost)
PORT = 3333


def prepare_sock(port):
    udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    # not bblocking
    # udp_sock.setblocking(0)
    udp_sock.bind((HOST, 0))
    udp_sock.connect((HOST, port))
    return udp_sock


if __name__ == '__main__':
    parser = optparse.OptionParser()
    parser.add_option('-p', '--port', dest='port', default=PORT,
                      type='int', help='The port to send to')
    opts, args = parser.parse_args()
    udp_sock = prepare_sock(opts.port)
    udp_sock.send(str.encode('I am a Python client.'))
    udp_sock.settimeout(1.0)
    buf = udp_sock.recv(100)
    # print("Received: ", buf)
    print(buf.decode("utf-8"))
