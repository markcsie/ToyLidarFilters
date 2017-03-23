set(FILTERS_SRC
  src/range_filter
  src/temporal_median_filter

  include/range_filter
  include/temporal_median_filter
)

add_library(ToyLidarFilters ${FILTERS_SRC})
target_include_directories (ToyLidarFilters PUBLIC include)
