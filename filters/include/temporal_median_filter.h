#ifndef TEMPORAL_MEDIAN_FILTER_H
#define TEMPORAL_MEDIAN_FILTER_H

#include "filter.h"

#include <set>
#include <queue>

class TemporalMedianFilter : public Filter
{
public:
  TemporalMedianFilter(const unsigned int &window_size);
  ~TemporalMedianFilter()
  {
  }

  virtual std::vector<float> update(const std::vector<float> &scan);
  void clear();

protected:
  unsigned int window_size_;
  std::vector<std::multiset<float>> sorted_set_vector_;
  std::vector<std::queue<float>> queue_vector_;

};

#endif // TEMPORAL_MEDIAN_FILTER_H
