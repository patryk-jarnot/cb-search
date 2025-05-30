import nscsearch

# nsrcsearch.identify("AAAAA", "QWERAAAAAAAQWER")

import unittest
import os


class TestExamples(unittest.TestCase):

    def test_take_struct(self):
        item = nscsearch.example_result_t();
        item.begin = 5
        item.end = 10
        nscsearch.take_struct(item)


    def test_take_strings(self):
        fragments = nscsearch.take_strings("str1", "str2")


    def test_take_strings_return_vector_of_ints(self):

        fragments = nscsearch.take_strings_return_vector_of_ints("str1", "str2")

        self.assertEqual(fragments[0], 8)
        self.assertEqual(fragments[1], 1)
        # self.assertEqual(fragments[0].end, 9)


    def test_take_strings_return_vector_of_struct(self):

        fragments = nscsearch.take_strings_return_vector_of_struct("str1", "str2")

        self.assertEqual(fragments[0].begin, 5)
        self.assertEqual(fragments[0].end, 4)

if __name__ == '__main__':
    unittest.main()