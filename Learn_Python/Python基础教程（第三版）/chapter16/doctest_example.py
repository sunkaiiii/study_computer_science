def square(x):
    # 供doctest使用
    '''
    计算平方并返回结果
    >>> square(2)
    4
    >>> square(3)
    9
    '''
    return x*x

def product(x,y):
    return x*y

if __name__ == '__main__':
    import doctest, doctest_example
    doctest.testmod(doctest_example)