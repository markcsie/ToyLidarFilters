#include "temporal_median_filter.h"

TemporalMedianFilter::TemporalMedianFilter(const unsigned int &window_size) : window_size_(window_size)
{
  type_ = "Temporal Median Filter";
}

std::vector<float> TemporalMedianFilter::update(const std::vector<float> &scan)
{
  if (sorted_set_vector_.size() == 0)
  {
    sorted_set_vector_.resize(scan.size());
    queue_vector_.resize(scan.size());
  }

  std::vector<float> filtered_scan(scan.size());
  for (size_t i = 0; i < scan.size(); ++i)
  {
    if (sorted_set_vector_[i].size() == window_size_ + 1)
    {
      sorted_set_vector_[i].erase(sorted_set_vector_[i].find(queue_vector_[i].front()));
      queue_vector_[i].pop();
    }
    queue_vector_[i].push(scan[i]);
    sorted_set_vector_[i].insert(scan[i]);

    std::multiset<float>::const_iterator iter_1 = sorted_set_vector_[i].cbegin();
    std::advance(iter_1, sorted_set_vector_[i].size() / 2);

    if (sorted_set_vector_[i].size() % 2 == 0)
    {
      const std::multiset<float>::const_iterator iter_2 = iter_1--;
      filtered_scan[i] = (*iter_1 + *iter_2) / 2;
    }
    else
    {
      filtered_scan[i] = *iter_1;
    }
  }
  return filtered_scan;
}

void TemporalMedianFilter::clear()
{
  sorted_set_vector_.clear();
  queue_vector_.clear();
}
