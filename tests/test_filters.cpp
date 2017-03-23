#include <iostream>
#include <memory>
#include <limits>

#include "range_filter.h"
#include "temporal_median_filter.h"

// LIDAR
//const size_t N_MIN = 200;
//const size_t N_MAX = 1000;
//const size_t N = 5;

// range filter
const float RANGE_MIN = 0.03;
const float RANGE_MAX = 50;

// temporal median filter
const unsigned int D = 3;

void printScan(const std::vector<float> &scan)
{
  std::cout << "[";
  for (const float &f : scan)
  {
    std::cout << f << " ";
  }
  std::cout << "]" << std::endl;
}

bool testFilter(const std::shared_ptr<Filter> &filter, const std::vector<std::vector<float>> &test_scan, const std::vector<std::vector<float>> &result_scan)
{
  std::cout << "Test " << filter->getType() << std::endl;
  for (size_t i = 0; i < test_scan.size(); ++i)
  {
    std::cout << "Input: ";
    printScan(test_scan[i]);
    std::vector<float> filtered_scan = filter->update(test_scan[i]);
    std::cout << "Filtered: ";
    printScan(filtered_scan);
    if (filtered_scan != result_scan[i])
    {
      std::cerr << "incorrect filtering for " << filter->getType() << std::endl;
      return false;
    }
  }
  std::cout << filter->getType() << " passed" << std::endl;
  return true;
}

int main()
{
  // testcases
  std::vector<std::vector<std::vector<float>>> scans_tests;
  std::vector<std::vector<std::vector<float>>> range_results;
  std::vector<std::vector<std::vector<float>>> median_results;

  // 1
  std::vector<std::vector<float>> scans_test = {
    {0, 1, 2, 1, 3},
    {1, 5, 7, 1, 3},
    {2, 3, 4, 1, 0},
    {3, 3, 3, 1, 3},
    {10, 2, 4, 0, 0},
  };

  std::vector<std::vector<float>> range_result = {
    {0.03, 1, 2, 1, 3},
    {1, 5, 7, 1, 3},
    {2, 3, 4, 1, 0.03},
    {3, 3, 3, 1, 3},
    {10, 2, 4, 0.03, 0.03},
  };
  std::vector<std::vector<float>> median_result = {
    {0, 1, 2, 1, 3},
    {0.5, 3, 4.5, 1, 3},
    {1, 3, 4, 1, 3},
    {1.5, 3, 3.5, 1, 3},
    {2.5, 3, 4, 1, 1.5},
  };
  scans_tests.push_back(scans_test);
  range_results.push_back(range_result);
  median_results.push_back(median_result);
  // 2
  scans_test = {
    {0, 20, 40, 60, 80},
    {100, 50, 0, -50, -100},
    {std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max(), 0, 1, 1},
  };
  range_result = {
    {0.03, 20, 40, 50, 50},
    {50, 50, 0.03, 0.03, 0.03},
    {0.03, 50, 0.03, 1, 1},
  };
  median_result = {
    {0, 20, 40, 60, 80},
    {50, 35, 20, 5, -10},
    {0, 50, 0, 1, 1},
  };
  scans_tests.push_back(scans_test);
  range_results.push_back(range_result);
  median_results.push_back(median_result);
  // 3
  scans_test = {
    {1, 1, 25},
    {2, 5, 20},
    {3, 10, 15},
    {4, 15, 10},
    {5, 20, 5},
    {6, 25, 1},
    {7, 20, 5},
    {8, 15, 10},
    {9, 10, 15},
    {10, 5, 20},
    {11, 1, 25},
  };
  range_result = {
    {1, 1, 25},
    {2, 5, 20},
    {3, 10, 15},
    {4, 15, 10},
    {5, 20, 5},
    {6, 25, 1},
    {7, 20, 5},
    {8, 15, 10},
    {9, 10, 15},
    {10, 5, 20},
    {11, 1, 25},
  };
  median_result = {
    {1, 1, 25},
    {1.5, 3, 22.5},
    {2, 5, 20},
    {2.5, 7.5, 17.5},
    {3.5, 12.5, 12.5},
    {4.5, 17.5, 7.5},
    {5.5, 20, 5},
    {6.5, 20, 5},
    {7.5, 17.5, 7.5},
    {8.5, 12.5, 12.5},
    {9.5, 7.5, 17.5},
  };
  scans_tests.push_back(scans_test);
  range_results.push_back(range_result);
  median_results.push_back(median_result);
  // testcases

  // test filters
  std::shared_ptr<Filter> range_filter = std::make_shared<RangeFilter>(RangeFilter(RANGE_MIN, RANGE_MAX));
  std::shared_ptr<Filter> temporal_median_filter = std::make_shared<TemporalMedianFilter>(TemporalMedianFilter(D));
  for (size_t i = 0; i < scans_tests.size(); ++i)
  {
    if (testFilter(range_filter, scans_tests[i], range_results[i]) &&
        testFilter(temporal_median_filter, scans_tests[i], median_results[i]))
    {
      std::cout << "Test " << i + 1 << " passed" << std::endl;
    }
    else
    {
      std::cerr << "Test " << i + 1 << " not passed" << std::endl;
    }
    std::static_pointer_cast<TemporalMedianFilter>(temporal_median_filter)->clear();
  }
  return EXIT_SUCCESS;
}
