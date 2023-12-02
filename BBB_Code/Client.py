import socket
import cv2
import pickle
import struct
import serial
import Adafruit_BBIO.UART as UART
import socket
import numpy as np
import face_detect
from struct import *
from face_detect import face_detect

UART.setup("UART4")
ser = serial.Serial("/dev/ttyO4", timeout=None, baudrate=115200) # open serial port
ser.close()
ser.open()

def draw_face_boxes(frame, faces):
    # draw bounding boxes for all faces in frame
    if faces is None:
        return frame
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
    return frame

HOST = "192.168.7.1"  # The server's hostname or IP address
PORT = 65433  # The port used by the server

if __name__=="__main__":
    # your code here
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((HOST, PORT))
    print("socket connected")

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
    

    try:

        while True:
            #hello
            # receive frame from client
            # frame_bytes = client_socket.recv(1024)
            # use res instead of 1024. multiply 560X480

            #use struct to get unpack, get first item (size)
            size = struct.unpack('!I', recvall(client_socket, 4))[0]
            #print(size)
            # use size to loop socket
            data = recvall(client_socket, size)


            #print(frame_bytes)
            # convert bytes to numpy array
            frame = pickle.loads(data)
            #downsized_frame = frame.reshape((100, 100))
            #print(frame)

            # Here we should do face detection on the beagle board
            face_cascade_path = 'haarcascade_frontalface_default.xml'
            faceCascade = cv2.CascadeClassifier(face_cascade_path)

            faces = face_detect(frame, faceCascade)
            new_frame = draw_face_boxes(frame, faces)

            print(faces)

            # Then use serial to send the coordinate information to the Tiva
            if ser.isOpen():
                result = None
                #print("Serial is open")

                for (x, y, w, h) in faces:

                    array = [x, y, w, h]

                    data_string = ",".join(map(str, array))
                    #ser.write(len(data_string).to_bytes(1, byteorder='big'))
                    #print(len(data_string))
                    x = x.astype(np.uint8)
                    y = y.astype(np.uint8)
                    w = w.astype(np.uint8)
                    h = h.astype(np.uint8)
                    ser.write(x.tobytes())
                    ser.write(y.tobytes())
                    ser.write(w.tobytes())
                    ser.write(h.tobytes())
            

    except KeyboardInterrupt:
        client_socket.close()
        ser.close()
        
