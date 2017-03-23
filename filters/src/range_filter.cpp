#include "range_filter.h"

RangeFilter::RangeFilter(const float &range_min, const float &range_max) : range_max_(range_max), range_min_(range_min)
{
  type_ = "Range Filter";
}

std::vector<float> RangeFilter::update(const std::vector<float> &scan)
{
  std::vector<float> filtered_scan = scan;
  for (float &f: filtered_scan)
  {
    f = std::min(f, range_max_);
    f = std::max(f, range_min_);
  }
  return filtered_scan;
}
