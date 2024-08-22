import socket

# 创建一个 UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 设置服务器地址和端口
server_address = ('127.0.0.1', 6666)
message = b'123456'

# 发送数据
sock.sendto(message, server_address)

# 接收数据
data, server = sock.recvfrom(4096)
print("Received {!r}".format(data))

# 关闭 socket
sock.close()

