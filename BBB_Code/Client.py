import socket
import cv2
import pickle
import struct
import serial
import socket

from struct import *

from face_detect import face_detect

HOST = "192.168.7.1"  # The server's hostname or IP address
PORT = 65433  # The port used by the server

if __name__=="__main__":
    # your code here