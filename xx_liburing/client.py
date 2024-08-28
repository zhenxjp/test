import socket
import time

# 创建一个 UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# 设置服务器地址和端口
server_address = ('127.0.0.1', 8888)

data = 0
idx = 0
ok = 0
while True:
    # 发送递增的数据
    idx +=1
    data += 1
    send_str = str(data) + "xxxyyy"
    send_data = (send_str).encode()
    
    # 发送数据
    sock.sendto(send_data, server_address)
    
    # 接收数据
    received_data, server = sock.recvfrom(4096)
    
    # 检查发送和接收是否一致
    if received_data.decode() == send_str:
        ok += 1
        print(f"ok 发送的数据是：{send_str}，接收的数据是：{received_data.decode()},idx:{idx}，发送数据长度为：{len(send_data)}")

    else:
        print(f"发送和接收不一致，发送的数据是：{send_str}，接收的数据是：{received_data.decode()},idx:{idx}，发送数据长度为：{len(send_data)}")
        break
    
    # 睡眠 100 毫秒
    # time.sleep(0.1)

# 关闭 socket（实际上不会执行到这里，因为是死循环）
sock.close()