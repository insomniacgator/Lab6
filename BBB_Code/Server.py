import socket
import pickle
import cv2 
import struct
import numpy as np

# server ip address and port
HOST = "192.168.7.1" # ip address of host pc
PORT = 65433  # Port to listen on (non-privileged ports are > 1023)

# Function to receive data from the server
def recvall(sock, count):
    buf = b''
    while count:
        new_buf = sock.recv(count)
        if not new_buf:
            return None
        buf += new_buf
        count -= len(new_buf)
    return buf

if __name__=="__main__":
    # your code here

    # server socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((HOST, PORT))
    server_socket.listen(5)
    print(f"Server listening on {HOST}:{PORT}")

    client_socket, client_address = server_socket.accept()
    print(f"Client connected: {client_address}")

    # Open webcam
    cam = cv2.VideoCapture(0, cv2.CAP_DSHOW)
    cam.set(cv2.CAP_PROP_FRAME_WIDTH, 480)
    cam.set(cv2.CAP_PROP_FRAME_HEIGHT, 560)

    frame_count = 0

    try:
        while True:
            # capture frame
            ret, frame = cam.read()

            frame_count += 1 # increment count

            if frame_count % 10 == 0:

                gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                downsampled = cv2.resize(gray, (240, 280))

                # encode frame
                data = pickle.dumps(downsampled)

                # get size from data len(data)
                size = len(data)
                #print(downsampled)
                # after use struct to pack the data, add the size with the actual data

                # send data
                client_socket.sendall(struct.pack('!I', size))
                client_socket.sendall(data)
                '''
                # (optional) receive again
                new_size = struct.unpack('!I', recvall(client_socket, 4))[0]
                print(new_size)
                # use size to loop socket
                new_data = recvall(client_socket, size)
                new_frame = pickle.loads(data)

                # Display the resulting frame
                cv2.imshow('frame',gray)
                if cv2.waitKey(1) & 0xFF == ord('q'):
                    break
                '''
                frame_count = 0

    except KeyboardInterrupt:
        client_socket.close()
        server_socket.close()
        cam.release()
        #cv2.destroyAllWindows()

    except ConnectionResetError:
        print("Client disconnected. Goodbye!")
        client_socket.close()
        server_socket.close()
        cam.release()
        #cv2.destroyAllWindows()