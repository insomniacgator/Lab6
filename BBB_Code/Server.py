import socket
import pickle
import cv2 
import struct

HOST = "192.168.7.1" # ip address of host pc
PORT = 65433  # Port to listen on (non-privileged ports are > 1023)

if __name__=="__main__":
    # your code here