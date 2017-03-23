#ifndef RANGE_FILTER_H
#define RANGE_FILTER_H

#include "filter.h"

class RangeFilter : public Filter
{
public:
  RangeFilter(const float &range_min, const float &range_max);
  ~RangeFilter()
  {
  }

  virtual std::vector<float> update(const std::vector<float> &scan);

protected:
  float range_max_;
  float range_min_;
};

#endif // RANGE_FILTER_H
