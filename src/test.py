#!/usr/bin/python
"""
Author: Jake Mathai
Purpose: LRU driver code
"""

from lru import LRU

cache = LRU(100)
cache.set(1, 'abcd')
cache.set('abcd', 2)
cache.print()
print(cache.get('abcd'))
print(cache.get(1))
