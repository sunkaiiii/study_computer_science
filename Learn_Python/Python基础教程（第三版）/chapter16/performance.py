import cProfile # 性能分析
from doctest_example import product
cProfile.run('product(1,2)')