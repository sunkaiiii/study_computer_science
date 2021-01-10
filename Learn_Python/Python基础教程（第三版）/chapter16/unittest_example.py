import unittest, doctest_example

class ProductTestCase(unittest.TestCase):
    def test_integers(self):
        for x in range(-10,10):
            for y in range(-10,10):
                p = doctest_example.product(x,y)
                self.assertEqual(p,x*y,'Integer multiplication failed')
    
    def test_floats(self):
        for x in range(-10,10):
            for y in range(-10,10):
                x = x/10
                y = y/10
                p = doctest_example.product(x,y)
                self.assertEqual(p,x*y,'Float multiplication failed')

if __name__ == '__main__':
    unittest.main()