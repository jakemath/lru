#!/usr/bin/python
"""
Author: Jake Mathai
Purpose: LRU class wrapper
"""

import ctypes

lib = ctypes.cdll.LoadLibrary('/src/liblru.so')

lib.create.argtypes = [ctypes.c_ulonglong]
lib.create.restype = ctypes.c_void_p
lib.get.argtypes = [ctypes.py_object]
lib.get.restype = ctypes.py_object
lib.set.argtypes = [ctypes.c_void_p, ctypes.py_object, ctypes.py_object]
lib.set.restype = None
lib.size.argtypes = [ctypes.c_void_p]
lib.size.restype = ctypes.c_ulonglong

class LRU:

    def __init__(self, max_size):
        self.max_size = max_size
        self.cache = lib.create(max_size)

    def get(self, key):
        return lib.get(self.cache, ctypes.py_object(key))
    
    def set(self, key, value):
        lib.set(self.cache, ctypes.py_object(key), ctypes.py_object(value))

    def size(self):
        return lib.size(self.cache)
