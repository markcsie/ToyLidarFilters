#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <string>

class Filter
{
public:
  virtual std::vector<float> update(const std::vector<float> &scan) = 0;
  virtual ~Filter()
  {
  }

  const std::string &getType() const
  {
    return type_;
  }

protected:
  std::string type_;
};

#endif // FILTER_H
