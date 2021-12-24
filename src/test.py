#!/usr/bin/python
"""
Author: Jake Mathai
Purpose: LRU driver code
"""

from lru import LRU

cache = LRU(100)
cache.set(1, 5)
cache.set("abc", 1)
print(cache.get(1))
print(cache.get('abc'))
print(cache.get(2))
