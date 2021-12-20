#!/usr/bin/python
"""
Author: Jake Mathai
Purpose: LRU class wrapper
"""

import ctypes

lib = ctypes.cdll.LoadLibrary('/src/liblru.so')

lib.create.argtypes = [ctypes.c_ulonglong]
lib.create.restype = ctypes.c_void_p
lib.get.argtypes = [ctypes.c_void_p]
lib.get.restype = ctypes.c_void_p
lib.set.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_void_p]
lib.set.restype = ctypes.c_void_p
lib.print.argtypes = [ctypes.c_void_p]
lib.print.restype = ctypes.c_void_p
lib.size.argtypes = [ctypes.c_void_p]
lib.size.restype = ctypes.c_ulonglong

class LRU:

    def __init__(self, max_size):
        self.max_size = max_size
        self.cache = lib.create(max_size)

    def get(self, key):
        return lib.get(self.cache, key)
    
    def set(self, key, value):
        return lib.set(self.cache, key, value)

    def print(self):
        lib.print(self.cache)

    def size(self):
        return lib.size(self.cache)
