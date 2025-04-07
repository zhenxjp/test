import socket

# 定义服务器地址和端口
HOST = '127.0.0.1'  
PORT = 8888  
BUFFER_SIZE = 1024

while True:
    try:
        # 创建socket对象
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # 设置socket选项，允许地址重用
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        # 绑定地址和端口
        server_socket.bind((HOST, PORT))
        # 开始监听
        server_socket.listen(5)
        print(f"Server is listening on port {PORT}...")

        while True:
            # 接受客户端连接
            client_socket, client_address = server_socket.accept()
            print(f"Accepted connection from {client_address}")
            try:
                while True:
                    # 接收客户端数据
                    data = client_socket.recv(BUFFER_SIZE)
                    if not data:
                        break
                    #打印收到的长度
                    print(f"Received {len(data)} bytes from {client_address}")
            except Exception as e:
                print(f"Error receiving data: {e}")
            finally:
                # 关闭客户端连接
                client_socket.close()
                print(f"Connection with {client_address} closed.")
    except Exception as e:
        print(f"Error occurred: {e}")
        # 关闭服务器socket（如果已创建）
        if'server_socket' in locals():
            server_socket.close()
        # 等待一段时间后重新尝试监听
        import time
        time.sleep(5)