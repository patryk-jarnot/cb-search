import nscsearch

# nsrcsearch.identify("AAAAA", "QWERAAAAAAAQWER")

import unittest
import os


class TestIdentification(unittest.TestCase):


    def test_identify_homopolymer_return_result_vector(self):

        fragments = nscsearch.identify("PPPPPPPPP", "QWERTNMPVQWERTNMPVQWERTNMQVPPPPPPPPPQWERTNMPVQWERTNMPVQWERTNMPV", 10, 2)

        self.assertEqual(fragments[0].begin, 28)
        self.assertEqual(fragments[0].end, 36)

    def test_window_similarity_scores(self):

        fragments = nscsearch.window_similarity_scores("PPPPPPPPP", "QWERTNMPVQWERTNMPVQWERTNMQVPPPPPPPPPQWERTNMPVQWERTNMPVQWERTNMPV")

        self.assertIsInstance(fragments[0], float)


if __name__ == '__main__':
    unittest.main()