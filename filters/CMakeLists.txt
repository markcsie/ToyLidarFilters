set(FILTERS_SRC
  src/filter
  src/range_filter
  src/temporal_median_filter
)

add_library(LidarFilters ${FILTERS_SRC})
target_include_directories (LidarFilters PUBLIC include)
